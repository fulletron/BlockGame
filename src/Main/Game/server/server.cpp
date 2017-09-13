#include "server.h"

namespace GS {
namespace Server {

_UINT32 Server::init()
{
	static const int MAX_USERS = 8;

	// MAX SIZE OF SERVER
	m_users.resize(MAX_USERS);
	m_users.clear();
	
	// MAX SIZE OF SERVER #2
	m_serverShards.resize(MAX_USERS);
	m_serverShards.clear();


	return 0;
}

_UINT32 Server::addUser(_UINT32 * a_pUser)
{
	// ENSURE THAT THIS NEW USER'S DATA APPEARS CORRECT
	// We're talking game stuff- at this point, we already have
	// confirmed that the user that is connecting is in fact
	// trying to play this game.
	///__verifyNewUser(a_pUser);

	// Either put the user in an existant shard, or make a new one
	///__attemptToPlaceNewUser(a_pUser);
}

_UINT32 Server::shutdown()
{
	m_users.clear();
	m_serverShards.clear();
	return 0;
}

_UINT32 Server::update(_DOUBLE a_dt)
{
	for (_VECTOR<GS::Server::ServerShard *>::const_iterator iter = m_serverShards.begin(); iter < m_serverShards.end(); iter++)
	{
		(*iter)->update(a_dt);
	}
	return 0;
}

};
};