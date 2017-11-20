#include "client.h"

// for inet_pton
#include <WS2tcpip.h>

namespace GS {
namespace Client {

Client::Client()
{
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &m_wsaData) != 0)
	{
		DEBUG_OUT_RED("Client failed to start.");
	}
}

void Client::makeConnection(u_short port, PCSTR ip)
{
	int addrlen = sizeof(m_addr);
	inet_pton(AF_INET, ip, &(m_addr.sin_addr.S_un.S_addr));
	m_addr.sin_port = htons(port);
	m_addr.sin_family = AF_INET;

	m_connection = socket(AF_INET, SOCK_STREAM, NULL);

	if (connect(m_connection, (SOCKADDR *)&m_addr, addrlen))
	{
		DEBUG_OUT_RED("Client failed to connect.");
	}
}

void Client::sendMsg(const char * a_msg, int a_len)
{
	send(m_connection, a_msg, a_len, NULL);
}

void Client::recvMsg(char * a_msg, int a_len)
{

	// recv returns size of the message? null if not ready?
	// recheck this from the windows help pages.
	recv(m_connection, a_msg, a_len, NULL);
}

}
}