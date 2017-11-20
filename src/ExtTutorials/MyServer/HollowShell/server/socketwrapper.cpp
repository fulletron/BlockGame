#include "socketwrapper.h"

#pragma comment(lib, "ws2_32.lib")

namespace GS {
namespace Server {

SocketWrapper::SocketWrapper()
	: m_socket(INVALID_SOCKET)
{}

SocketWrapper::SocketWrapper(
	SOCKET theSocket)
	: m_socket(theSocket)
{
	if (m_socket == INVALID_SOCKET)
	{
		DEBUG_OUT("The set socket was set to a bad socket");
	}
}

SocketWrapper::~SocketWrapper()
{
	if (m_socket != INVALID_SOCKET)
	{
		abortiveClose();
	}
}

void SocketWrapper::close()
{
	if (0 != ::closesocket(m_socket))
	{
		DEBUG_OUT("The socket failed to close.");
		//::WSAGetLastError();
	}
}

void SocketWrapper::attach(
	SOCKET theSocket)
{
	abortiveClose();

	m_socket = theSocket;
}

SOCKET SocketWrapper::detatch()
{
	SOCKET theSocket = m_socket;

	m_socket = INVALID_SOCKET;

	return theSocket;
}

void SocketWrapper::abortiveClose()
{
	LINGER lingerStruct;

	lingerStruct.l_onoff = 1;
	lingerStruct.l_linger = 0;

	if (SOCKET_ERROR == ::setsockopt(m_socket, SOL_SOCKET, SO_LINGER, (char *)&lingerStruct, sizeof(lingerStruct)))
	{
		DEBUG_OUT("The socket failed to abortiveClose");
		//::WSAGetLastError();
	}
}

void SocketWrapper::shutdown(int a_how)
{
	if (0 != ::shutdown(m_socket, a_how))
	{
		DEBUG_OUT("socket ::shutdown failed.");
		//::WSAGetLastError();
	}
}

void SocketWrapper::listen(
	int backlog)
{
	if (SOCKET_ERROR == ::listen(m_socket, backlog))
	{
		DEBUG_OUT("socket ::listen failed.");
		//::WSAGetLastError();
	}
}

void SocketWrapper::bind(
	const SOCKADDR_IN &address)
{
	if (SOCKET_ERROR == ::bind(m_socket, reinterpret_cast<struct sockaddr *>(const_cast<SOCKADDR_IN*>(&address)), sizeof(SOCKADDR_IN)))
	{
		DEBUG_OUT("socket ::bind failed. A.");
		// ::WSAGetLastError();
	}
}

void SocketWrapper::bind(
	const struct sockaddr &address,
	size_t addressLength)
{
	//lint -e{713} Loss of precision (arg. no. 3) (unsigned int to int)
	if (SOCKET_ERROR == ::bind(m_socket, const_cast<struct sockaddr *>(&address), addressLength))
	{
		DEBUG_OUT("socket ::bind failed. B.");
		//::WSAGetLastError());
	}
}

SocketWrapper::InternetAddress::InternetAddress(
	unsigned long address,
	unsigned short port)
{
	this->sin_family = AF_INET;
	this->sin_port = htons(port);
	this->sin_addr.S_un.S_addr = htonl(address);
}



};
};