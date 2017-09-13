#ifndef __ISERVERSHARD_H_
#define __ISERVERSHARD_H_

#include <Utilities\definitions_types.h>

namespace GS {
namespace Server {

class IServerShard
{
public:
	virtual _VECTOR<_UINT32 *> * getRecipients() = 0;
};

};
};

#endif