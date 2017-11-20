#include "serversocket.h"

#include "socketserver.h"
#include "buffer/buffer.h"

namespace GS {
namespace Server {

ServerSocket::ServerSocket(
	SocketServer & server,
	SOCKET theSocket,
	bool useSequenceNumbers)
	: m_server(server),
	m_socket(theSocket),
	m_ref(1),
	m_outstandingWrites(0),
	m_readShutdown(false),
	m_writeShutdown(false),
	m_closing(false),
	m_clientClosed(false),
	m_pSequenceData(0)
{
	if (!isValid())
	{
		//throw CException(_T("CSocketServer::Socket::Socket()"), _T("Invalid socket"));
		DEBUG_OUT("invalid socket. ServerSocket constructor.");
	}

	if (useSequenceNumbers)
	{
		m_pSequenceData = new SequenceData(m_crit);
	}
}

ServerSocket::~ServerSocket()
{
	if (m_pSequenceData)
		delete m_pSequenceData;
	m_pSequenceData = 0;
}

void ServerSocket::attach(SOCKET theSocket)
{
	if (isValid())
	{
		DEBUG_OUT("Socket Already Attached");
		//throw CException(_T("CSocketServer::Socket::Attach()"), _T("Socket already attached"));
	}

	m_socket = theSocket;

	UserData::setUserData(0);

	m_readShutdown = false;
	m_writeShutdown = false;
	m_outstandingWrites = 0;
	m_closing = false;
	m_clientClosed = false;
}

void ServerSocket::addRef()
{
	::InterlockedIncrement(&m_ref);
}

void ServerSocket::release()
{
	if (0 == ::InterlockedDecrement(&m_ref))
	{
		if (isValid())
		{
			addRef();
			if (!m_closing)
			{
				m_closing = true;
				if (!m_server.onConnectionClosing(this))
				{
					abortiveClose();
				}
			}
			else
			{
				abortiveClose();
			}

			release();
			return;
		}
		m_server.releaseSocket(this);
	}
}

void ServerSocket::shutdown(int how) // = SD_BOTH
{
	//DEBUG_OUT("");
	if (m_server.filterSocketShutdown(this, how))
	{
		if (how == SD_RECEIVE || how == SD_BOTH)
		{
			m_readShutdown = true;
		}

		if (how == SD_SEND || how == SD_BOTH)
		{
			m_writeShutdown = true;
		}

		if (::InterlockedExchange(&m_outstandingWrites, m_outstandingWrites) > 0)
		{
			// Send side will be shut down when last pending write completes...

			if (how == SD_BOTH)
			{
				how = SD_RECEIVE;
			}
			else if (how == SD_SEND)
			{
				return;
			}
		}

		if (isValid())
		{
			if (0 != ::shutdown(m_socket, how))
			{
				//m_server.OnError(_T("CSocketServer::Server::Shutdown() - ") + GetLastErrorMessage(::WSAGetLastError()));
				DEBUG_OUT("SERVERSOCKET SHUTDOWN FAILED.");
			}
		}
	}
}

bool ServerSocket::isConnected(int how) const // = SD_BOTH
{
	if (how == SD_RECEIVE)
		return !m_readShutdown;
	if (how == SD_SEND)
		return !m_writeShutdown;
	if (how == SD_BOTH)
		return (!m_readShutdown && !m_writeShutdown);
	return false;
}

void ServerSocket::close()
{
	std::lock_guard<std::mutex> lock(m_crit);

	if (isValid())
	{
		if (m_server.filterSocketClose(this))
		{
			internalClose();
		}
	}
}

bool ServerSocket::writePending()
{
	if (m_writeShutdown)
	{
		DEBUG_OUT("Attempting to write after write shutdown");
		return false;
	}

	::InterlockedIncrement(&m_outstandingWrites);
	return true;
}

void ServerSocket::writeCompleted()
{
	if (::InterlockedDecrement(&m_outstandingWrites) == 0)
	{
		if (m_writeShutdown)
		{
			shutdown(SD_SEND);
		}
	}
}

void ServerSocket::abortiveClose()
{
	LINGER lingerStruct;

	lingerStruct.l_onoff = 1;
	lingerStruct.l_linger = 0;

	if (SOCKET_ERROR == ::setsockopt(m_socket, SOL_SOCKET, SO_LINGER, (char *)&lingerStruct, sizeof(lingerStruct)))
	{
		DEBUG_OUT("ServerSocket abortiveClose failed.");
		//m_server.OnError(_T("CSocketServer::Socket::AbortiveClose() - setsockopt(SO_LINGER) - ") + GetLastErrorMessage(::WSAGetLastError()));
	}

	internalClose();
}

void ServerSocket::onClientClose()
{
	if (0 == ::InterlockedExchange(&m_clientClosed, 1))
	{
		shutdown(SD_RECEIVE);
		m_server.onConnectionClientClose(this);
	}
}

void ServerSocket::onConnectionReset()
{
	std::lock_guard<std::mutex> lock(m_crit);

	if (isValid())
	{
		m_server.onConnectionReset(this);
		internalClose();
	}
}

void ServerSocket::internalClose()
{
	if (isValid())
	{
		std::lock_guard<std::mutex> lock(m_crit);

		if (0 != ::closesocket(m_socket))
		{
			//m_server.OnError(_T("CSocketServer::Socket::InternalClose() - closesocket - ") + GetLastErrorMessage(::WSAGetLastError()));
			DEBUG_OUT("ServerSocket::internalClose ::closesocket failed.");
		}

		m_socket = INVALID_SOCKET;

		m_readShutdown = true;
		m_writeShutdown = true;

		m_server.onConnectionClosed(this);
	}
}

bool ServerSocket::read( 
	Buffer * pBuffer,
	bool throwOnFailure)
{
	if (!isValid())
	{
		DEBUG_OUT("ServerSocket read failed, not a valid socket");
		if (throwOnFailure)
		{
			// Todo throw SocketClosedException();
			//throw CException(_T("CSocketServer::Socket::Read()"), _T("Socket is closed"));
		}
		else
		{
			return false;
		}
	}

	if (!pBuffer)
	{
		pBuffer = m_server.allocate();
	}
	else
	{
		pBuffer->addRef();
	}

	m_server.postIoOperation(this, pBuffer, m_server.m_postZeroByteReads ? SocketServer::IO_Operation::IO_Zero_Byte_Read_Request : SocketServer::IO_Operation::IO_Read_Request);

	pBuffer->release();

	return true;
}

bool ServerSocket::write(
	const char * pData,
	size_t dataLength,
	bool throwOnFailure)
{
	return write(reinterpret_cast<const BYTE *>(pData), dataLength, throwOnFailure);
}

bool ServerSocket::write(
	const BYTE * pData,
	size_t dataLength,
	bool throwOnFailure)
{
	if (!isValid())
	{
		if (throwOnFailure)
		{
			// Todo throw SocketClosedException();
//			throw CException(_T("CSocketServer::Socket::Write()"), _T("Socket is closed"));
		}
		else
		{
			return false;
		}
		DEBUG_OUT("ServerSocket::write failed, invalid serversocket.");
	}

	if (!writePending())
	{
		if (throwOnFailure)
		{
			// Todo throw SocketClosedException();
			//throw CException(_T("CSocketServer::Socket::Write()"), _T("Socket is shutdown"));
		}
		else
		{
			return false;
		}

		DEBUG_OUT("ServerSocket::write failed, serversocket is shutdown.");
	}

	Buffer * pBuffer = m_server.allocate();
	pBuffer->addData(pData, dataLength);
	pBuffer->setSequenceNumber(getSequenceNumber(WriteSequenceNo));
	m_server.postIoOperation(this, pBuffer, SocketServer::IO_Operation::IO_Write_Request);
	pBuffer->release();

	return true;
}

bool ServerSocket::write(
	Buffer * pBuffer,
	bool throwOnFailure)
{
	if (!isValid())
	{
		if (throwOnFailure)
		{
			// Todo throw SocketClosedException();
			//throw CException(_T("CSocketServer::Socket::Write()"), _T("Socket is closed"));
		}
		else
		{
			return false;
		}
		DEBUG_OUT("ServerSocket::write failed, socket is closed.");
	}

	if (!writePending())
	{
		if (throwOnFailure)
		{
			// Todo throw SocketClosedException();
			//throw CException(_T("CSocketServer::Socket::Write()"), _T("Socket is shutdown"));
		}
		else
		{
			return false;
		}
		DEBUG_OUT("ServerSocket::write failed, !writePending.");
	}

	pBuffer->setSequenceNumber(getSequenceNumber(WriteSequenceNo));

	m_server.postIoOperation(this, pBuffer, SocketServer::IO_Operation::IO_Write_Request);

	return true;
}

long ServerSocket::getSequenceNumber(
	SequenceType type)
{
	if (m_pSequenceData)
	{
		return m_pSequenceData->m_numbers[type]++;
	}

	return 0;
}

Buffer * ServerSocket::getNextBuffer(
	Buffer * pBuffer)
{
	if (m_pSequenceData)
	{
		if (pBuffer)
		{
			m_pSequenceData->m_outOfSequenceWrites.getNext(pBuffer);
		}
		else
		{
			m_pSequenceData->m_outOfSequenceWrites.processAndGetNext();
		}
	}
	return pBuffer;
}

bool ServerSocket::isValid()
{
// KYLE :: TODO :: THIS CAUSES CRASHES TOO OFTEN
// onConnectionError can snake its way here, causing 
// a single thread to attempt to double lock.

//	std::lock_guard<std::mutex> lock(m_crit);

	return (INVALID_SOCKET != m_socket);
}

void ServerSocket::onConnectionError(
	Buffer * pBuffer,
	DWORD lastError)
{
	if (WSAESHUTDOWN == lastError)
	{
		onClientClose();
	}
	else if (WSAECONNRESET == lastError || WSAECONNABORTED == lastError)
	{
		onConnectionReset();
	}
	else if (!isValid() && WSAENOTSOCK == lastError)
	{
		//swallow
	}
	else
	{
		m_server.onConnectionError(this,pBuffer,lastError);
	}
}

// Interior class SEQUENCEDATA
ServerSocket::SequenceData::SequenceData(
	std::mutex &section)
	: m_outOfSequenceWrites(section)
{
	memset(m_numbers, 0, sizeof(m_numbers));
}

void ServerSocket::SequenceData::reset()
{
	memset(m_numbers, 0, sizeof(m_numbers));

	m_outOfSequenceWrites.reset();
}

};
};