#ifndef __SOCKETSERVER_H__
#define __SOCKETSERVER_H__

#include "../definitions_types.h"
#include <thread>
#include <mutex>

#include "completionport.h"
#include "socketwrapper.h"
#include "workerthread.h"
#include "buffer/Allocator.h"
#include "useswinsock.h"

//#ifdef _WINDOWS_

namespace GS {
namespace Server {

/*
* The base server class.
*/
class SocketServer : public Allocator, public UsesWinsock {
public:
	friend class ServerSocket;
	friend class WorkerThread;

	static LPSYSTEM_INFO m_systemInfo;

	SocketServer(
		unsigned long addressToListenOn,
		unsigned short portToListenOn,
		size_t maxFreeSockets,
		size_t maxFreeBuffers,
		size_t bufferSize,
		size_t numThreads,
		bool useSequenceNumbers = true,
		bool postZeroByteReads = false);

	/*
	* Shutdown function.
	*/
	void waitForShutdownToComplete();

	/*
	* Shut off the listening socket
	*/
	void stopAcceptingConnections();

	/*
	* Create the listening socket
	*/
	void startAcceptingConnections();

	/*
	* The server thread begins.
	*/
	void start();

selective:
	const size_t m_numThreads;
	SOCKET m_listeningSocket;
	GS::Server::CompletionPort m_iocp;
	const unsigned long m_address;
	const unsigned short m_port;
	const size_t m_maxFreeSockets;
	const bool m_useSequenceNumbers;
	const bool m_postZeroByteReads;

	// These two apparently should be shared with the socket pool
	// these exist in the inherited class ALLOCATOR
	//const size_t m_bufferSize;
	//const size_t m_maxFreeBuffers;

	// The example project has a custom thread class, and the server inherits from it.
	// I will not be doing that. I think.
	std::thread * m_thread;

	// List of sockets, and the mutex that controls their manipulation.
	std::mutex m_listManipulationMutex;
	typedef GS::Server::TNodeList<ServerSocket> SocketList;
	SocketList m_activeList;
	SocketList m_freeList;

	// Mutex to control critical section.
	std::mutex m_criticalSection;

	// example server is turned off via HANDLE events? Mine will have a flag that is set.
	bool m_done;

selective:
	/*
	* Generic, needly existant function for InitiateShutdownA and InitiateShutdownW ?
	*/
	void __initiateShutdown();

	/*
	* Releases and destroys all sockets.
	*/
	void __releaseSockets();

	/*
	* Destroy the lists of sockets themselves
	*/
	void __flush();

	/*
	* If the number of threads is not specified (0),
	* return the system info's num of processors * 2.
	*/
	static size_t __calculateNumberOfThreads(size_t numThreads);

	/*
	* Release the data from a specified socket. KYLE :: NOT TRULY __
	*/
	void releaseSocket(ServerSocket *pSocket);

	/*
	* Delete the actual socket specified.
	*/
	void __destroySocket(ServerSocket *pSocket);

	/*
	* The function spun-up by the server m_thread.
	*/
	int __run();

	/*
	* Internal, actually creates the listening socket.
	*/
	SOCKET __createListeningSocket(unsigned long, unsigned short);

	/*
	* Creates a server slave worker thread
	*/
	WorkerThread * __createWorkerThread(CompletionPort *iocp);

	/*
	* Creates a new ServerSocket
	*/
	ServerSocket *SocketServer::__allocateSocket(
		SOCKET theSocket);

// filters to get into postIoOperation
selective:
	void postFilteredReadRequest(
		ServerSocket *pSocket,
		Buffer *pBuffer);

	void postFilteredReadCompleted(
		ServerSocket *pSocket,
		Buffer *pBuffer);

	void postFilteredWriteRequest(
		ServerSocket *pSocket,
		Buffer *pBuffer);

	void postFilteredWriteCompleted(
		ServerSocket *pSocket,
		Buffer *pBuffer);

// KYLE :: TODO :: I DONT UNDERSTAND THESE
selective:
	static void setServerDataPtr(
		ServerSocket *pSocket,
		void *pData);

	static void *getServerDataPtr(
		const ServerSocket *pSocket);

	static void writeCompleted(
		ServerSocket *pSocket);

	static SocketServer &getServer(
		ServerSocket *pSocket);

privatized:
	virtual void onThreadCreated(std::thread::id id) {}
	virtual void onThreadBeginProcessing() {}
	virtual void onThreadEndProcessing() {}
	virtual void onThreadDestroyed(std::thread::id id) {}

	// Interface for derived classes to receive state change notifications...

	virtual void onStartAcceptingConnections() {}
	virtual void onStopAcceptingConnections() {}
	virtual void onShutdownInitiated() {}
	virtual void onShutdownComplete() {}
	virtual void onConnectionCreated(ServerSocket * pSocket) {}

	virtual void onConnectionEstablished(
		ServerSocket *pSocket,
		Buffer *pAddress) = 0;

	virtual void onConnectionClientClose(
		ServerSocket *) {}

	virtual void onConnectionReset(
		ServerSocket *) {}

	virtual bool onConnectionClosing(
		ServerSocket *) {
		return false;
	}

	virtual void onConnectionClosed(
		ServerSocket *) {}

	virtual void onConnectionDestroyed() {}

	virtual void onBufferCreated() {}
	virtual void onBufferAllocated() {}
	virtual void onBufferReleased() {}
	virtual void onBufferDestroyed() {}
	virtual void onConnectionError(
//		ConnectionErrorSource source,
		ServerSocket *pSocket,
		Buffer *pBuffer,
		DWORD lastError);

//	virtual void onError(
//		const _tstring &message);

	virtual bool filterReadRequest(
		ServerSocket *pSocket,
		Buffer **ppBuffer);

	virtual bool filterReadCompleted(
		ServerSocket *pSocket,
		Buffer **ppBuffer);

	virtual bool filterWriteRequest(
		ServerSocket *pSocket,
		Buffer **ppBuffer);

	virtual bool filterWriteCompleted(
		ServerSocket *pSocket,
		Buffer **ppBuffer);

	virtual bool filterSocketShutdown(
		ServerSocket *pSocket,
		int how);

	virtual bool filterSocketClose(
		ServerSocket *pSocket);

	virtual void readCompleted(
		ServerSocket *pSocket,
		Buffer *pBuffer) = 0;

	/*
	* tells a specific socket a write has been completed.
	*/
	virtual void writeCompleted(
		ServerSocket *pSocket,
		Buffer *pBuffer);

	enum IO_Operation
	{
		IO_Zero_Byte_Read_Request,
		IO_Zero_Byte_Read_Completed,
		IO_Read_Request,
		IO_Read_Completed,
		IO_Write_Request,
		IO_Write_Completed,
		IO_Filtered_Read_Request,
		IO_Filtered_Read_Completed,
		IO_Filtered_Write_Request,
		IO_Filtered_Write_Completed
	};


	/*
	* post a completion packet to the IOCP with the socket and the buffer.
	*/
	void postIoOperation(
		ServerSocket * pSocket,
		Buffer * pBuffer,
		IO_Operation operation);

};

};
};

//#endif

#endif