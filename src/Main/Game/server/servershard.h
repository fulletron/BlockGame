#ifndef __SERVERSHARD_H_
#define __SERVERSHARD_H_

#include <Framework/server/iserver.h>

#include <Game/Memory/instancememory.h>

#include <Utilities\definitions_types.h>

namespace GS {
namespace Server {

class ServerShard
{
selective:
	/* List of connected users. */
	_VECTOR<_UINT32 *> m_users;

	/* All of the data relevant to this shard */
	GS::Memory::InstanceMemory m_instanceMemory;

public:
	_UINT32 connectUser(_UINT32 * a_pUser);
	_UINT32 update(_DOUBLE a_dt);

	_UINT32 init();
	_UINT32 shutdown();

};

};
};

#endif