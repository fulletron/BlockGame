#ifndef __WORKERTHREAD_H__
#define __WORKERTHREAD_H__

#include "../definitions_types.h"
#include <thread>
#include <mutex>

namespace GS {
namespace Server {

class SocketServer;
class CompletionPort;

class ServerSocket;
class Buffer;

class WorkerThread
{
public:
	/*
	* Construct the worker thread with the correct server and completion port.
	* This starts the thread, spinning on the "run" function.
	*/
	WorkerThread(
		SocketServer *, 
		CompletionPort *);

	void initiateShutdown();
	void joinThread();

	virtual ~WorkerThread();

selective :

	SocketServer * m_pServer;
	CompletionPort * m_pIOCP;
	std::thread * m_pThread;

	/*
	* Main worker thread function.
	*/
	int __run();

	/*
	* 
	*/
	void __handleOperation(
		ServerSocket *pSocket,
		Buffer *pBuffer,
		DWORD dwIoSize,
		bool weClosedSocket);

	/*
	* calls WSARecv
	*/
	void __zeroByteRead(
		ServerSocket *pSocket,
		Buffer *pBuffer) const;

	/*
	* calls WSARecv
	*/
	void __read(
		ServerSocket *pSocket,
		Buffer *pBuffer) const;

	/*
	* calls WSASend
	*/
	void __write(
	ServerSocket *pSocket,
	Buffer *pBuffer) const;

	// No copies do not implement
	WorkerThread(const WorkerThread &rhs);
	WorkerThread &operator=(const WorkerThread &rhs);
};

};
};

#endif