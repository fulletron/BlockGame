#ifndef __ITIME_H_
#define __ITIME_H_

#include "../definitions_types.h"

namespace GS {
namespace Utilities {
	
class ITime
{
public:
	virtual _UINT32 init() = 0;
	virtual _UINT32 shutdown() = 0;

	virtual _DOUBLE getSecondsSinceBootup () const = 0;
	virtual _DOUBLE getDeltaTime () const = 0;
	virtual _DOUBLE checkDeltaTime() const = 0;
	virtual void updateInternalValues () = 0;
};

};
};

#endif