#include "misc.h"

namespace GS {
namespace Utilities {
namespace Misc {

_UINT32 getClosestSquareRoot(const _UINT32 a_num)
{
	_UINT32 i = 0;
	while( i * i < a_num )
		++i;

	return i;
}

};
};
};