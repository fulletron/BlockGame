#ifndef __SOCKETWRAPPER_H__
#define __SOCKETWRAPPER_H__

#include "../definitions_types.h"

// KYLE :: remove redefines
#ifndef _WINSOCK2API_
#include <WinSock2.h>
#endif

namespace GS {
namespace Server 
{
/*
* Class that holds a basic windows SOCKET.
*/
class SocketWrapper
{
public:
	class InternetAddress;

	/*
	* Basic constructor, creates an uninitialized socket.
	*/
	SocketWrapper();

	/*
	* Sets this socket with an already made socket.
	*/
	explicit SocketWrapper(
		SOCKET theSocket);

	~SocketWrapper();

	/*
	* Associates an actual windows SOCKET with my Socket class.
	*/
	void attach(
		SOCKET theSocket);

	/*
	* Detaches the actual windows SOCKET and returns it.
	* This leaves this socket actually SOCKET-less.
	*/
	SOCKET detatch();

	/*
	* Calls ::closesocket() on the windows SOCKET.
	*/
	void close();

	/*
	* Calls ::setsockopt() on the windows SOCKET with a linger struct.
	*/
	void abortiveClose();

	/*
	* Calls ::shutdown(SOCKET, how). 
	*/
	void shutdown(
		int how);

	/*
	* Calls ::listen(SOCKET, backlog) on the SOCKET.
	*/
	void listen(
		int backlog);

	/*
	* Calls ::bind() on the SOCKET.
	*/
	void bind(
		const SOCKADDR_IN &address);

	/*
	* Calls ::bind() on the SOCKET.
	*/
	void bind(
		const struct sockaddr &address,
		size_t addressLength);


privatized:
	SOCKET m_socket;

	// No copies do not implement
	SocketWrapper(const SocketWrapper &rhs);
	SocketWrapper &operator=(const SocketWrapper &rhs);
};

class SocketWrapper::InternetAddress : public SOCKADDR_IN
{
public:
	InternetAddress(
		unsigned long address,
		unsigned short port);
};

};
};

#endif