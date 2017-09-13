#ifndef __ICOMMSERVER_H_
#define __ICOMMSERVER_H_

#include "../definitions_types.h"

namespace GS {
namespace Utilities {
	
class ICommServer
{
public:
	virtual _UINT32 init() = 0;
	virtual _UINT32 shutdown() = 0;
};

};
};

#endif