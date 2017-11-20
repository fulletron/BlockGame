#include "serverwrapper.h"
#include "serversocket.h"

#include "buffer/buffer.h"

namespace GS {
namespace Server {

ServerWrapper::ServerWrapper(
	const std::string & welcomeMessage,
	unsigned long addressToListenOn,
	unsigned short portToListenOn,
	size_t maxFreeSockets,
	size_t maxFreeBuffers,
	size_t bufferSize,
	size_t numThreads)
	: GS::Server::SocketServer(addressToListenOn, portToListenOn, maxFreeSockets, maxFreeBuffers, bufferSize, numThreads),
	m_welcomeMessage(welcomeMessage)
{
}

void ServerWrapper::onConnectionEstablished(
	ServerSocket *pSocket,
	Buffer * /*pAddress*/)
{
	//Output(_T("OnConnectionEstablished"));

	//pSocket->write(m_welcomeMessage.c_str(), m_welcomeMessage.length());

	// reads the first message sent from the connection established.
	pSocket->read();
}

void ServerWrapper::readCompleted(
	ServerSocket * pSocket,
	Buffer * pBuffer)
{
// FOR ECHO SERVERS;	__echoMessage(pSocket, pBuffer);

	pBuffer = processDataStream(pSocket, pBuffer);
	pSocket->read(pBuffer);

	//pSocket->read();
}

GS::Server::Buffer * ServerWrapper::processDataStream(
	ServerSocket * pSocket,
	GS::Server::Buffer * pBuffer) const
{
	bool done;

	do
	{
		done = true;
		const size_t used = pBuffer->getUsed();

		if (used >= getMinimumMessageSize())
		{
			const size_t messageSize = getMessageSize(pBuffer);

			if (messageSize == 0)
			{
				// have not yet gotten a complete message

				// we null terminate messages in the buffer, reserve a byte
				if (used == (pBuffer->getSize() - 1))
				{
					DEBUG_OUT_RED("Too Much Data!!!!");
					const std::string response("-ERR too much data! Go Away! \r\n");

					pSocket->write(response.c_str(), response.length());
					pSocket->shutdown();

					pBuffer->empty();

					done = true;
				}
			}
			else if (used == messageSize)
			{
				pBuffer->addData(0); // null terminate the command string;

				// do the deed.
				processCommand(pSocket, pBuffer);

				pBuffer->empty();
				done = true;
			}
			else if (used > messageSize)
			{
				Buffer * pMessage = pBuffer->splitBuffer(messageSize);

				pMessage->addData(0); // null terminate it

				processCommand(pSocket, pMessage);

				pMessage->release();

				done = false;
			}
		}
	} while (!done);

	return pBuffer;
}

void ServerWrapper::processCommand(
	ServerSocket * pSocket,
	const GS::Server::Buffer * pBuffer) const
{
	std::string command = reinterpret_cast<const char*>(pBuffer->getBuffer());

	std::string echoCommand = command.substr(0, command.length() - 2); // strip the \r\n

	for (size_t i = 0; i < command.length(); ++i)
	{
		command[i] = (char)toupper(command[i]);
	}

	bool ok = false;

	if (command.length() >= getMinimumMessageSize())
	{
		if (command.substr(0, 3) == "TOP")
		{
			ok = true;
		}
		else
		{
			const std::string cmd = command.substr(0, 4);

			if (cmd == "APOP" ||
				cmd == "DELE" ||
				cmd == "LIST" ||
				cmd == "NOOP" ||
				cmd == "PASS" ||
				cmd == "QUIT" ||
				cmd == "RETR" ||
				cmd == "RSET" ||
				cmd == "STAT" ||
				cmd == "UIDL" ||
				cmd == "USER")
			{
				ok = true;
			}
		}
	}

	if (ok)
	{
		// MESSAGE SUCCESS
		std::string response("-ERRSUC we get you but we're actually an echo server... \r\n");
		pSocket->write(response.c_str(), response.length());
	}
	else
	{
		// GIVE EM THE BIRD
		std::string response("-ERR sorry, we don't get you, bye... \r\n");
		pSocket->write(response.c_str(), response.length());
		pSocket->shutdown();
	}
}

size_t ServerWrapper::getMinimumMessageSize() const
{
	// presume 3 characters plus \r\n
	return 5;
}

size_t ServerWrapper::getMessageSize(
	const GS::Server::Buffer * pBuffer) const
{
	const BYTE *pData = pBuffer->getBuffer();
	const size_t used = pBuffer->getUsed();

	for (size_t i = 0; i < used; ++i)
	{
		if (pData[i] == '\r')
		{
			if (i + 1 < used && pData[i + 1] == '\n')
			{
				// the end of the message is i+1
				// we actually want a count of characters, not a zero based
				// index, so we have to add 1...
				return i + 1 + 1;
			}
		}
	}

	return 0;
}

/*
void ServerWrapper::__echoMessage(ServerSocket * pSocket, Buffer * pBuffer)
{
	pSocket->write(pBuffer);
}
*/

void ServerWrapper::onThreadCreated(std::thread::id id)
{ 
	DEBUG_OUT("worker thread created:"); 
	DEBUG_OUT_GREEN(toString(id));
}
void ServerWrapper::onThreadBeginProcessing() { DEBUG_OUT("worker thread begin processing."); }
void ServerWrapper::onThreadEndProcessing() { DEBUG_OUT("worker thread end processing."); }
void ServerWrapper::onThreadDestroyed(std::thread::id id) { DEBUG_OUT_YELLOW("worker thread destroyed."); DEBUG_OUT_YELLOW(toString(id)); }

void ServerWrapper::onStartAcceptingConnections() { DEBUG_OUT("started accepting connections."); }
void ServerWrapper::onStopAcceptingConnections() { DEBUG_OUT("stopped accepting connections."); }
void ServerWrapper::onShutdownInitiated() { DEBUG_OUT_YELLOW("shutdown initiated."); }
void ServerWrapper::onShutdownComplete() { DEBUG_OUT_YELLOW("shutdown completed."); }
void ServerWrapper::onConnectionCreated(ServerSocket * pSocket) 
{
	pSocket;
	DEBUG_OUT_GREEN("connection created."); 
}

void ServerWrapper::onConnectionClientClose(
	ServerSocket * pSocket) 
{
	DEBUG_OUT_YELLOW("client closed connection.");
}

void ServerWrapper::onConnectionReset(
	ServerSocket * pSocket) 
{
	DEBUG_OUT("connection reset.");
}

bool ServerWrapper::onConnectionClosing(
	ServerSocket * pSocket) 
{
	pSocket;
	DEBUG_OUT("connection closing.");
	return false;
}

void ServerWrapper::onConnectionClosed(
	ServerSocket * pSocket) 
{
	pSocket;
	DEBUG_OUT("connection closed.");
}

void ServerWrapper::onConnectionDestroyed() 
{
	DEBUG_OUT("connection destroyed.");
}

void ServerWrapper::onBufferCreated() 
{
	DEBUG_OUT("buffer created.");
}

void ServerWrapper::onBufferAllocated() 
{
	DEBUG_OUT("buffer allocated.");
}

void ServerWrapper::onBufferReleased() 
{
	DEBUG_OUT("buffer released.");
}

void ServerWrapper::onBufferDestroyed() 
{
	DEBUG_OUT("buffer destroyed.");
}



};
};