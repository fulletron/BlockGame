#ifndef __WORLDMAPSTATE_H_
#define __WORLDMAPSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../directorstate.h"

namespace GS {
namespace State {

class WorldMapState : public IState<DirectorState>
{
	IMPLEMENT_ISTATE(DirectorState);
};

};
};

#endif