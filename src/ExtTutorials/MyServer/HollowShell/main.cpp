#include <iostream>
#include "definitions_types.h"

#include "server/serverwrapper.h"

#include <conio.h>

// TEST CLIENT
#include "client/client.h"

int main()
{
	GS::Server::ServerWrapper server(
		"WELCOME MESSAGE!\r\n",
		INADDR_ANY,
		5555,
		10,
		10,
		1024,
		2);

	server.start();
	server.startAcceptingConnections();

	DEBUG_OUT("Press a key to connect a dummy client...");

	GS::Client::Client client;
	client.makeConnection(5555);
	DEBUG_OUT_YELLOW("Client has connected");

	//_getch();

	char OUTMSG[1024] = "TOP\r\n";
	DEBUG_OUT_YELLOW("Sending OUTMSG to the server...");
	client.sendMsg(OUTMSG, 5);

	//_getch();

	char ECHOBACK[1024];
	client.recvMsg(ECHOBACK, 1024);
	DEBUG_OUT_YELLOW("Client recieved echoback: ");
	DEBUG_OUT_YELLOW(ECHOBACK);

	//_getch();

	char OUTMSG2[1024] = "APOP\r\n";
	DEBUG_OUT_YELLOW("Sending OUTMSG2 to the server...");
	client.sendMsg(OUTMSG2, 6);
	int test = 1;

	//_getch();

	char ECHOBACK2[1024];
	client.recvMsg(ECHOBACK2, 1024);
	DEBUG_OUT_YELLOW("Client recieved echoback2: ");
	DEBUG_OUT_YELLOW(ECHOBACK2);

	_getch();


	DEBUG_OUT("Shutting Down...");

	server.waitForShutdownToComplete();

	return 0;
}