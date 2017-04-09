#ifndef __EARTHMAPSTATE_H_
#define __EARTHMAPSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../directorstate.h"

namespace GS {
namespace State {

class EarthMapState : public IState<DirectorState>
{
	IMPLEMENT_ISTATE(DirectorState);
};

};
};

#endif