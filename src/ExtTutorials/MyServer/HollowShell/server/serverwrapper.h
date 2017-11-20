#ifndef __SERVERWRAPPER_H__
#define __SERVERWRAPPER_H__

#include "../definitions_types.h"
#include "socketserver.h"

namespace GS {
namespace Server {

class ServerSocket;

/*
* A wrapper to simplify server interaction.
*/
class ServerWrapper : public SocketServer {
public:
	ServerWrapper(
		const std::string &welcomeMessage,
		unsigned long addressToListenOn,
		unsigned short portToListenOn,
		size_t maxFreeSockets,
		size_t maxFreeBuffers,
		size_t bufferSize = 1024,
		size_t numThreads = 0);
selective:
	const std::string m_welcomeMessage;

privatized:
	// No copies do not implement
	ServerWrapper(const ServerWrapper &rhs);
	ServerWrapper &operator=(const ServerWrapper &rhs);

	// Packets!
	size_t getMinimumMessageSize() const;
	size_t getMessageSize(
		const GS::Server::Buffer * pBuffer) const;

	GS::Server::Buffer * processDataStream
		(ServerSocket * pSocket,
		GS::Server::Buffer * pBuffer) const;

	void processCommand(
		ServerSocket * pSocket,
		const GS::Server::Buffer * pBuffer) const;

// FOR ECHO SERVERS	void __echoMessage(ServerSocket * pSocket, Buffer * pBuffer);

	virtual void readCompleted(
		ServerSocket *pSocket,
		Buffer *pBuffer);

	// OVERRIDES
	virtual void onConnectionEstablished(
		ServerSocket *pSocket,
		Buffer * /*pAddress*/);

	virtual void onThreadCreated(std::thread::id id);
	virtual void onThreadBeginProcessing();
	virtual void onThreadEndProcessing();
	virtual void onThreadDestroyed(std::thread::id id);
	virtual void onStartAcceptingConnections();
	virtual void onStopAcceptingConnections();
	virtual void onShutdownInitiated();
	virtual void onShutdownComplete();
	virtual void onConnectionCreated(ServerSocket *);

	virtual void onConnectionClientClose(
		ServerSocket *);

	virtual void onConnectionReset(
		ServerSocket *);

	virtual bool onConnectionClosing(
		ServerSocket *);

	virtual void onConnectionClosed(
		ServerSocket *);

	virtual void onConnectionDestroyed();

	virtual void onBufferCreated();
	virtual void onBufferAllocated();
	virtual void onBufferReleased();
	virtual void onBufferDestroyed();
};

};
};

#endif