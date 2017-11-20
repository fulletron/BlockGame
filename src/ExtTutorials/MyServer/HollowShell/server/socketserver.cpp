#include "socketserver.h"

#include "serversocket.h"

#include "buffer/buffer.h"

namespace GS {
namespace Server {

	SocketServer::SocketServer(
		unsigned long addressToListenOn,
		unsigned short portToListenOn,
		size_t maxFreeSockets,
		size_t maxFreeBuffers,
		size_t bufferSize,
		size_t numThreads,
		bool useSequenceNumbers,
		bool postZeroByteReads) :
	Allocator(bufferSize, maxFreeBuffers),
	m_numThreads(__calculateNumberOfThreads(numThreads)),
	m_listeningSocket(INVALID_SOCKET),
	m_iocp(0),
	m_address(addressToListenOn),
	m_port(portToListenOn),
	m_maxFreeSockets(maxFreeSockets),
	m_useSequenceNumbers(useSequenceNumbers),
	m_postZeroByteReads(postZeroByteReads)
{
}

void SocketServer::waitForShutdownToComplete()
{
	__initiateShutdown();

	// Example program has a wait here, with WaitForSingleObject

	__releaseSockets();
	__flush();

	m_thread->join();
	delete m_thread;
}

void SocketServer::stopAcceptingConnections()
{
	if (m_listeningSocket != INVALID_SOCKET)
	{
// MORE THAN LIKELY I WILL NOT USE EVENTS
//		m_acceptConnectionsEvent.Reset();

		if (0 != ::closesocket(m_listeningSocket))
		{
			DEBUG_OUT("stopAcceptingConnections ::closesocket failed.");
			//::WSAGetLastError()
		}

		m_listeningSocket = INVALID_SOCKET;

		//lint -e{1933} call to unqualified virtual function
		onStopAcceptingConnections();
	}
}

void SocketServer::startAcceptingConnections()
{
	if (m_listeningSocket == INVALID_SOCKET)
	{
		//lint -e{1933} call to unqualified virtual function
		onStartAcceptingConnections();

		//lint -e{1933} call to unqualified virtual function
		m_listeningSocket = __createListeningSocket(m_address, m_port);
	}
	if (m_listeningSocket == INVALID_SOCKET)
	{
		DEBUG_OUT_RED("created an INVALID_SOCKET for m_listeningSocket");
	}
}

void SocketServer::start()
{
	m_done = false;
	m_thread = new std::thread(&SocketServer::__run, this);
}

int SocketServer::__run()
{

//	try
//	{
		_VECTOR<GS::Server::WorkerThread*> workers;
		// ORIG :: vector<WorkerThread *> workers;

		workers.reserve(m_numThreads);
		size_t i = 0;
		for (i = 0; i < m_numThreads; ++i)
		{
			//lint -e{1933} call to unqualified virtual function
			WorkerThread *pThread = __createWorkerThread(&m_iocp);

			workers.push_back(pThread);

			// ORIG :: pThread->Start();
			// std::threads begin the moment they are constructed.

			//lint -e{429} custodial pointer neither freed nor returned
		}

		while (m_listeningSocket == INVALID_SOCKET)
		{
		}

		// ORIG :: Example used HANDLE events, I will be using a simple bool.
		//HANDLE handlesToWaitFor[2];
		//handlesToWaitFor[0] = m_shutdownEvent.GetEvent();
		//handlesToWaitFor[1] = m_acceptConnectionsEvent.GetEvent();

		//while (!m_shutdownEvent.Wait(0))
		while (!m_done)
		{
			// ORIG :: example uses HANDLE events, and has intelligent looking waiting. 
			// Doesn't appear to be necessary though (it would be better, but I don't fully
			// understand it).
			// accept connections
			//while (!m_shutdownEvent.Wait(0) && m_acceptConnectionsEvent.Wait(0))
			//{
			Buffer *pAddress = allocate();

			int addressSize = (int)pAddress->getSize();

			sockaddr * sp = reinterpret_cast<sockaddr*>(const_cast<BYTE*>(pAddress->getBuffer()));

			//lint -e{826} suspicious pointer conversion
			SOCKET acceptedSocket = ::WSAAccept(
				m_listeningSocket,
				sp,
				&addressSize,
				0,
				0);

			pAddress->use(addressSize);

			if (acceptedSocket != INVALID_SOCKET)
			{
				ServerSocket *pSocket = __allocateSocket(acceptedSocket);

				//lint -e{1933} call to unqualified virtual function
				onConnectionEstablished(pSocket, pAddress);

				// KYLE ::  NOT CONVINCED I SHOULD RELEASE HERE
				pSocket->release();
			}
			else if (acceptedSocket == INVALID_SOCKET)
			{
				int lastError = ::WSAGetLastError();

				DEBUG_OUT_RED("acceptedSocket was INVALID.");
				char * test = new char[256];
				_itoa_s(lastError, test, 256, 10);;

				DEBUG_OUT_RED(test);
			}
//			else if (m_acceptConnectionsEvent.Wait(0))
//			{
				//lint -e{1933} call to unqualified virtual function
//				OnError(_T("CSocketServer::Run() - WSAAccept:") + GetLastErrorMessage(::WSAGetLastError()));
//			}

			pAddress->release();
		}

		for (i = 0; i < m_numThreads; ++i)
		{
			workers[i]->initiateShutdown();
		}

		for (i = 0; i < m_numThreads; ++i)
		{
			workers[i]->joinThread();

			delete workers[i];

			workers[i] = 0;
		}
//	catch (const CException &e)
//	{
		//lint -e{1933} call to unqualified virtual function
//		OnError(_T("CSocketServer::Run() - Exception: ") + e.GetWhere() + _T(" - ") + e.GetMessage());
//	}
//	catch (...)
//	{
		//lint -e{1933} call to unqualified virtual function
//		OnError(_T("CSocketServer::Run() - Unexpected exception"));
//	}

	//lint -e{1933} call to unqualified virtual function
	onShutdownComplete();

	return 0;
}

ServerSocket *SocketServer::__allocateSocket(
	SOCKET theSocket)
{
	std::lock_guard<std::mutex> lock(m_listManipulationMutex);
	//CCriticalSection::Owner lock(m_listManipulationSection);

	ServerSocket *pSocket = 0;

	if (!m_freeList.empty())
	{
		pSocket = m_freeList.popNode();

		pSocket->attach(theSocket);

		pSocket->addRef();
	}
	else
	{
		pSocket = new ServerSocket(*this, theSocket, m_useSequenceNumbers);

		//lint -e{1933} call to unqualified virtual function
		onConnectionCreated(pSocket);
	}

	m_activeList.pushNode(pSocket);

	//lint -e{611} suspicious cast
	m_iocp.associateDevice(reinterpret_cast<HANDLE>(theSocket), (ULONG_PTR)pSocket);

	return pSocket;
}

WorkerThread * SocketServer::__createWorkerThread(GS::Server::CompletionPort *iocp)
{
	return new GS::Server::WorkerThread(this, iocp);
}

SOCKET SocketServer::__createListeningSocket(unsigned long address, unsigned short port)
{
	SOCKET s = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (s == INVALID_SOCKET)
	{
		DEBUG_OUT("__createListeningSocket, socket created was invalid");
		//::WSAGetLastError()
	}

	SocketWrapper listeningSocket(s);

	SocketWrapper::InternetAddress localAddress(address, port);

	listeningSocket.bind(localAddress);
	listeningSocket.listen(5);

	return listeningSocket.detatch();
}

size_t SocketServer::__calculateNumberOfThreads(size_t a_numThreads)
{
	if (a_numThreads == 0)
	{
		if (!m_systemInfo)
			::GetSystemInfo(m_systemInfo);
		return m_systemInfo->dwNumberOfProcessors * 2;
	}
	return a_numThreads;
}

void SocketServer::__releaseSockets()
{
	//std::lock_guard<std::mutex> lock(m_listManipulationMutex);

	while (m_activeList.head())
	{
		releaseSocket(m_activeList.head());
	}

	while (m_freeList.head())
	{
		__destroySocket(m_freeList.head());
	}

	if (m_freeList.count() + m_freeList.count() != 0)
	{
		DEBUG_OUT("DID NOT RELEASE ALL SOCKETS.");
	}
}

void SocketServer::releaseSocket(ServerSocket *pSocket)
{
	std::lock_guard<std::mutex> lock(m_listManipulationMutex);

	if (!pSocket)
	{
		DEBUG_OUT("pSocket is null");
	}

	pSocket->removeFromList();

	if (m_maxFreeSockets == 0 ||
		m_freeList.count() < m_maxFreeSockets)
	{
		m_freeList.pushNode(pSocket);
	}
	else
	{
		__destroySocket(pSocket);
	}
}

void SocketServer::__destroySocket(
	ServerSocket *pSocket)
{
	delete pSocket;

	//lint -e{1933} call to unqualified virtual function
	onConnectionDestroyed();
}

void SocketServer::__flush()
{
	std::lock_guard<std::mutex> lock(m_criticalSection);

	//allocatorFlush();
	/*
	while (!m_activeList.empty())
	{
		//lint -e{1933} call to unqualified virtual function
		onBufferReleased();

		__destroyBuffer(m_activeList.popNode());
	}

	while (!m_freeList.empty())
	{
		__destroyBuffer(m_freeList.popNode());
	}
	*/
}

void SocketServer::__initiateShutdown()
{
	// signal that the dispatch thread should shut down all worker threads and then exit

	stopAcceptingConnections();

	{
		std::lock_guard<std::mutex> lock(m_listManipulationMutex);

		ServerSocket * pSocket = m_activeList.head();

		while (pSocket)
		{
			ServerSocket * pNext = SocketList::next(pSocket);
			pSocket->abortiveClose();
			pSocket = pNext;
		}


		/*
		_VECTOR<Socket *>::iterator socket_iter;
		for (socket_iter = m_pActiveList.begin(); socket_iter < m_pActiveList.end(); socket_iter++)
		{
		(*socket_iter)->abortiveClose();
		}
		*/
	}

	m_done = true;


	//lint -e{1933} call to unqualified virtual function
	onShutdownInitiated();
}

void SocketServer::postIoOperation(ServerSocket * pSocket,
	Buffer * pBuffer,
	IO_Operation operation)
{
	pBuffer->setOperation(operation);
	pBuffer->addRef();

	pSocket->addRef();

	m_iocp.postStatus((ULONG_PTR)pSocket, 0, pBuffer);
}

void SocketServer::onConnectionError(
	//		ConnectionErrorSource source,
	ServerSocket *pSocket,
	Buffer *pBuffer,
	DWORD lastError)
{
	DEBUG_OUT("onConnectionError");
}

// [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
// filter reads, writes, stuff. Don't exactily understand this
// KYLE :: TODO

void SocketServer::writeCompleted(
	ServerSocket *pSocket)
{
	pSocket->writeCompleted();
}

void SocketServer::writeCompleted(
	ServerSocket * pSocket,
	Buffer * pBuffer)
{
	if (pBuffer->getUsed() != pBuffer->getWSABUF()->len)
	{
		DEBUG_OUT("AN ERROR HAS OCCURED IN writeCompleted");
	}
}


bool SocketServer::filterReadRequest(
	ServerSocket * /*pSocket*/,
	Buffer ** /*ppBuffer*/)
{
	// Normal processing here is to return a filtered buffer if we can filter in place or false if 
	// the filtered data will be returned via a call to PostFilteredReadRequest

	return true;
}

bool SocketServer::filterReadCompleted(
	ServerSocket * /*pSocket*/,
	Buffer ** /*ppBuffer*/)
{
	// Normal processing here is to return a filtered buffer if we can filter in place or false if 
	// the filtered data will be returned via a call to PostFilteredReadCompleted

	return true;
}

bool SocketServer::filterWriteRequest(
	ServerSocket * /*pSocket*/,
	Buffer ** /*ppBuffer*/)
{
	// Normal processing here is to return a filtered buffer if we can filter in place or false if 
	// the filtered data will be returned via a call to PostFilteredWriteRequest

	return true;
}

bool SocketServer::filterWriteCompleted(
	ServerSocket * /*pSocket*/,
	Buffer ** /*ppBuffer*/)
{
	// Normal processing here is to return a filtered buffer if we can filter in place or false if 
	// the filtered data will be returned via a call to PostFilteredWriteCompleted

	return true;
}

bool SocketServer::filterSocketShutdown(
	ServerSocket * /*pSocket*/,
	int /*how*/)
{
	return true;
}

bool SocketServer::filterSocketClose(
	ServerSocket * /*pSocket*/)
{
	return true;
}

void SocketServer::postFilteredReadRequest(
	ServerSocket *pSocket,
	Buffer *pBuffer)
{
	postIoOperation(pSocket, pBuffer, IO_Filtered_Read_Request);
}

void SocketServer::postFilteredReadCompleted(
	ServerSocket *pSocket,
	Buffer *pBuffer)
{
	pBuffer->setSequenceNumber(pSocket->getSequenceNumber(ServerSocket::FilteredReadSequenceNo));

	postIoOperation(pSocket, pBuffer, IO_Filtered_Read_Completed);
}

void SocketServer::postFilteredWriteRequest(
	ServerSocket *pSocket,
	Buffer *pBuffer)
{
	if (pSocket->writePending())
	{
		pBuffer->setSequenceNumber(pSocket->getSequenceNumber(ServerSocket::FilteredWriteSequenceNo));

		postIoOperation(pSocket, pBuffer, IO_Filtered_Write_Request);
	}
}

void SocketServer::postFilteredWriteCompleted(
	ServerSocket *pSocket,
	Buffer *pBuffer)
{
	postIoOperation(pSocket, pBuffer, IO_Filtered_Write_Completed);
}

SocketServer &SocketServer::getServer(
	ServerSocket *pSocket)
{
	return pSocket->m_server;
}

// ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


LPSYSTEM_INFO SocketServer::m_systemInfo = 0;

};
};