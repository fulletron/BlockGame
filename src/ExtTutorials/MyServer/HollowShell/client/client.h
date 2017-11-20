#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "../definitions_types.h"
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>

namespace GS {
namespace Client {

class Client
{
public:
	Client();
	~Client(){}

	void makeConnection(u_short port, PCSTR ip = "127.0.0.1");
	void sendMsg(const char * a_msg, int a_len);
	void recvMsg(char * a_msg, int a_len);

selective:
	WSAData m_wsaData;
	SOCKADDR_IN m_addr;
	SOCKET m_connection;
};

}
}

#endif