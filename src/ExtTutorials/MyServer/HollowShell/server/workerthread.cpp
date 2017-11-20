#include "workerthread.h"

#include "socketserver.h"

#include "buffer/buffer.h"
#include "serversocket.h"

namespace GS {
namespace Server {

WorkerThread::WorkerThread(
	SocketServer * pServer,
	CompletionPort * pIOCP)
	: m_pServer(pServer),
	m_pIOCP(pIOCP)
{
	m_pThread = new std::thread(&WorkerThread::__run, this);
	std::thread::id id = m_pThread->get_id();
	m_pServer->onThreadCreated(id);
}

WorkerThread::~WorkerThread()
{
}

int WorkerThread::__run()
{
	//try
	{
		//lint -e{716} while(1)
		while (true)
		{
			// continually loop to service io completion packets

			DWORD dwIoSize = 0;
			ServerSocket *pSocket = 0;
			Buffer *pBuffer = 0;

			bool weClosedSocket = false;

			// This is blocking!
			m_pIOCP->getStatus((PDWORD_PTR)&pSocket, &dwIoSize, (OVERLAPPED**)&pBuffer);

			if (!pSocket)
			{
				// A completion key of 0 is posted to the iocp to request us to shut down...

				break;
			}

			m_pServer->onThreadBeginProcessing();

			//lint -e{1933} call to unqualified virtual function
			__handleOperation(pSocket, pBuffer, dwIoSize, weClosedSocket);

			m_pServer->onThreadEndProcessing();
		}
	}
	/*
	catch (const CException &e)
	{
		m_server.OnError(_T("CSocketServer::WorkerThread::Run() - Exception: ") + e.GetWhere() + _T(" - ") + e.GetMessage());
	}
	catch (...)
	{
		m_server.OnError(_T("CSocketServer::WorkerThread::Run() - Unexpected exception"));
	}
	*/

	// as an std::thread, this should return and be ready for a join call as a shutdown procedure
	return 0;
}

void WorkerThread::initiateShutdown()
{
	m_pIOCP->postStatus(0);
}

// this is if i can't inherit from std::thread
void WorkerThread::joinThread()
{
	m_pServer->onThreadDestroyed(m_pThread->get_id());
	m_pThread->join();
}

void WorkerThread::__handleOperation(
	ServerSocket *pSocket,
	Buffer *pBuffer,
	DWORD dwIoSize,
	bool weClosedSocket)
{
	if (pBuffer)
	{
		const SocketServer::IO_Operation operation = static_cast<SocketServer::IO_Operation>(pBuffer->getOperation());

		switch (operation)
		{
		case SocketServer::IO_Zero_Byte_Read_Request:
			__zeroByteRead(pSocket, pBuffer);
			pSocket->release();
			pBuffer->release();
			break;

		case SocketServer::IO_Zero_Byte_Read_Completed:
		case SocketServer::IO_Read_Request:
			if (m_pServer->filterReadRequest(pSocket, &pBuffer))
			{
				__read(pSocket, pBuffer);
			}

			pSocket->release();
			pBuffer->release();

			break;

		case SocketServer::IO_Filtered_Read_Request:
			__read(pSocket, pBuffer);

			pSocket->release();
			pBuffer->release();

			break;

		case SocketServer::IO_Read_Completed:

			//DEBUG_ONLY(Output(_T("  RX: ") + ToString(pBuffer->GetUsed()) + _T(" bytes") + _T(" Seq: ") + ToString(pBuffer->GetSequenceNumber()) + _T(" : ") + ToString(pBuffer) + _T("\n")));
			pBuffer->use(dwIoSize);
			if (m_pServer->filterReadCompleted(pSocket, &pBuffer))
			{
				if (0 != dwIoSize)
				{
					m_pServer->readCompleted(pSocket, pBuffer);
				}
			}

			if (0 == dwIoSize && !weClosedSocket)
			{
				// Client Connection Dropped?
				pSocket->onClientClose();
			}

			break;

		case SocketServer::IO_Filtered_Read_Completed:

			if (0 != pBuffer->getUsed())
			{
				m_pServer->readCompleted(pSocket, pBuffer);
			}
			pSocket->release();
			pBuffer->release();

			break;

		case SocketServer::IO_Write_Request:
			// DEBUG_ONLY(Output(_T("  TX: ") + ToString(pBuffer->GetUsed()) + _T(" bytes") + _T(" Seq: ") + ToString(pBuffer->GetSequenceNumber()) + _T(" : ") + ToString(pBuffer) + _T("\n")));
			if (m_pServer->filterWriteRequest(pSocket, &pBuffer))
			{
				__write(pSocket, pBuffer);
			}
			pSocket->release();
			pBuffer->release();
			break;

		case SocketServer::IO_Filtered_Write_Request:
			__write(pSocket, pBuffer);
			pSocket->release();
			pBuffer->release();
			break;

		case SocketServer::IO_Write_Completed:
			pBuffer->use(dwIoSize);
			if (m_pServer->filterWriteCompleted(pSocket, &pBuffer))
			{
				m_pServer->writeCompleted(pSocket, pBuffer);
				pSocket->writeCompleted();
			}

			pSocket->release();
			pBuffer->release();
			break;

		case SocketServer::IO_Filtered_Write_Completed:
			m_pServer->writeCompleted(pSocket, pBuffer);
			pSocket->writeCompleted();
			pSocket->release();
			pBuffer->release();
			break;

		default:
			DEBUG_OUT_RED("UNEXPECTED OPERATION.");
			break;
		}
	}
	else
	{
		DEBUG_OUT_RED("pBUFFER IS ZERO");
	}
}

void WorkerThread::__zeroByteRead(
	ServerSocket *pSocket,
	Buffer *pBuffer) const
{
	pSocket->addRef();

	pBuffer->setOperation(SocketServer::IO_Zero_Byte_Read_Completed);
	pBuffer->setupZeroByteRead();
	pBuffer->addRef();

	DWORD dwNumBytes = 0;
	DWORD dwFlags = 0;

	if (SOCKET_ERROR == ::WSARecv(
		pSocket->m_socket,
		pBuffer->getWSABUF(),
		1,
		&dwNumBytes,
		&dwFlags,
		pBuffer,
		NULL))
	{
		DWORD lastError = ::WSAGetLastError();

		if (ERROR_IO_PENDING != lastError)
		{
			pSocket->onConnectionError(/*ZeroByteReadError,*/ pBuffer, lastError);

			pSocket->release();
			pBuffer->release();
		}
	}
}

void WorkerThread::__read(
	ServerSocket *pSocket,
	Buffer *pBuffer) const
{
	pSocket->addRef();

	pBuffer->setOperation(SocketServer::IO_Read_Completed);
	pBuffer->setupRead();
	pBuffer->addRef();

	std::lock_guard<std::mutex> lock(pSocket->m_crit);

	pBuffer->setSequenceNumber(pSocket->getSequenceNumber(ServerSocket::ReadSequenceNo));

	DWORD dwNumBytes = 0;
	DWORD dwFlags = 0;

	if (SOCKET_ERROR == ::WSARecv(
		pSocket->m_socket,
		pBuffer->getWSABUF(),
		1,
		&dwNumBytes,
		&dwFlags,
		pBuffer,
		NULL))
	{
		DWORD lastError = ::WSAGetLastError();

		if (ERROR_IO_PENDING != lastError)
		{
			pSocket->onConnectionError(/*ReadError,*/ pBuffer, lastError);

			pSocket->release();
			pBuffer->release();
		}
	}
}

void WorkerThread::__write(
	ServerSocket *pSocket,
	Buffer *pBuffer) const
{
	pSocket->addRef();

	pBuffer->setOperation(SocketServer::IO_Write_Completed);
	pBuffer->setupWrite();
	pBuffer->addRef();

	pBuffer = pSocket->getNextBuffer(pBuffer);

	while (pBuffer)
	{
		//DEBUG_ONLY(Output(ToString(pSocket) + _T(" X TX: Seq: ") + ToString(pBuffer->GetSequenceNumber()) + _T(" bytes = ") + ToString(pBuffer->GetWSABUF()->len)));

		DWORD dwFlags = 0;
		DWORD dwSendNumBytes = 0;

		if (SOCKET_ERROR == ::WSASend(
			pSocket->m_socket,
			pBuffer->getWSABUF(),
			1,
			&dwSendNumBytes,
			dwFlags,
			pBuffer,
			NULL))
		{
			DWORD lastError = ::WSAGetLastError();

			if (ERROR_IO_PENDING != lastError)
			{
				pSocket->onConnectionError(/*WriteError,*/ pBuffer, lastError);

				pSocket->writeCompleted();  // this pending write will never complete...

				pSocket->release();
				pBuffer->release();
			}
		}

		pBuffer = pSocket->getNextBuffer();
	}
}

};
};