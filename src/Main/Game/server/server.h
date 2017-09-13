#ifndef __SERVER_H_
#define __SERVER_H_

#include <Utilities\definitions_types.h>

#include <Framework/server/iserver.h>
#include <Game/server/servershard.h>


namespace GS {
namespace Server {

class Server : public IServer
{
selective:
	/* List of connected users. */
	_VECTOR<_UINT32 *> m_users;

	/* List of currently existant instance shards. */
	_VECTOR<GS::Server::ServerShard *> m_serverShards;

	/* List of currently existant chat shards. */
	//_VECTOR<_UINT32 *> m_chatShards;

public:
	_UINT32 init();
	_UINT32 shutdown();

	_UINT32 addUser(_UINT32 *);

	/*
	* Update the server shards and users.
	*/
	_UINT32 update(_DOUBLE a_dt);

	/*
	* Look through the inbound message list and
	* do that work.
	*/
	virtual _UINT32 handleInboundMessages()
	{
		return 0;
	}

	/*
	* Add a single message to the outbound list.
	* PROBABLY DON'T WANT IT AT THIS LEVEL?
	*/
	virtual _UINT32 prepareOutboundMessage(_UINT32 a_msg)
	{
		return 0;
	}

	/*
	* Give all the messages in the outbound list to NET or ClientList
	*/
	virtual _UINT32 sendOutboundMessages()
	{
		return 0;
	}
};

};
};

#endif