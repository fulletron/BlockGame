#ifndef __GSINVESTOR_H_
#define __GSINVESTOR_H_

#include "typedefinitions.h"

namespace GS {
namespace Utilities {

class GSInvestor
{
public:
	virtual _UINT32 readjust( const _INT64 a_frameName, const _INT64 a_adjustment ) = 0;
};

};
};

#endif
