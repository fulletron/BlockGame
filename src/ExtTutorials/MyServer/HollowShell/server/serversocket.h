#ifndef __SERVERSOCKET_H__
#define __SERVERSOCKET_H__

#include "../definitions_types.h"
#include "buffer/nodelist.h"
#include "buffer/opaqueuserdata.h"
#include <mutex>
#include "buffer/inorderbufferlist.h"

namespace GS {
namespace Server {

class SocketServer;
class WorkerThread;
class Buffer;

class ServerSocket :
	public Node,
	public UserData,
	protected ServerData
{
public:
	friend class SocketServer;
	friend class WorkerThread;

	using UserData::setUserData;
	using UserData::getUserData;
	using UserData::setUserPtr;
	using UserData::getUserPtr;

	/*
	* postIoOperation read, with passed pBuffer.
	*/
	bool read(Buffer * pBuffer = 0,
		bool throwOnFailure = false);

	/*
	* postIoOperation write, with passed data
	*/
	bool write(const char * pData,
		size_t dataLength,
		bool throwOnFailure = false);

	/*
	* postIoOperation write, with passed data
	*/
	bool write(const BYTE * pData,
		size_t dataLength,
		bool throwOnFailure = false);

	/*
	* postIoOperation write, with passed buffer
	*/
	bool write(Buffer * pBuffer,
		bool throwOnFailure = false);

	void addRef();

	/*
	* abortiveClose() if valid, just release if invalid
	*/
	void release();

	/*
	* tells the server to shut this socket down.
	* calls m_server.filteredSocketShutdown
	* calls ::shutdown(m_socket, how)
	*/
	void shutdown(
		int how = SD_BOTH);

	/*
	* m_server.filter socket close, and internalClose()
	*/
	void close();

	/*
	* calls ::setsockopt on the SOCKET, and internalClose()
	*/
	void abortiveClose();

	bool isConnected(int how = SD_BOTH) const;

privatized:
	ServerSocket(
		SocketServer & server,
		SOCKET socket,
		bool useSequenceNumbers);

	~ServerSocket();

	/*
	* sets m_socket to theSocket, and initializes a few variables.
	*/
	void attach(SOCKET theSocket);

	void * getServerDataPtr() const
	{
		return ServerData::getUserPtr();
	}

	void setServerDataPtr(void * pData)
	{
		ServerData::setUserPtr(pData);
	}

	/*
	* decrements m_outstandingWrites
	*/
	void writeCompleted();

	/*
	* increments m_outstandingWrites
	*/
	bool writePending();

	/*
	* sets m_clientClosed to 1, calls shutdown().
	*/
	void onClientClose();

	/*
	* calls internalClose
	*/
	void onConnectionReset();

	bool isValid();

	/*
	* calls ::closesocket readShutdown writeShutdown
	*/
	void internalClose();

	void onConnectionError(
		Buffer * pBuffer,
		DWORD lastError);

	std::mutex m_crit;

	SocketServer &m_server;
	SOCKET m_socket;

	long m_ref;
	long m_outstandingWrites;

	bool m_readShutdown;
	bool m_writeShutdown;
	bool m_closing;
	long m_clientClosed;

	enum SequenceType
	{
		ReadSequenceNo,
		WriteSequenceNo,
		FilteredReadSequenceNo,
		FilteredWriteSequenceNo,
		MaxSequenceNo
	};

	/*
	* pass in a sequencetype, returns a long from the SequenceData struct
	*/
	long getSequenceNumber(SequenceType type);

	/*
	* get the next buffer in the sequence data.
	*/
	Buffer * getNextBuffer(Buffer * pBuffer = 0);

	struct SequenceData
	{
		explicit SequenceData(std::mutex &crit);

		void reset();

		long m_numbers[4];

		InOrderBufferList m_outOfSequenceWrites;
	};

	SequenceData * m_pSequenceData;

	// No copies do not implement
	ServerSocket(const ServerSocket &rhs);
	ServerSocket &operator=(const ServerSocket &rhs);
};

};
};

#endif