#ifndef __LAUNCHPADSTATE_H_
#define __LAUNCHPADSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../directorstate.h"

namespace GS {
namespace State {

class LaunchPadState : public IState<DirectorState>
{
	IMPLEMENT_ISTATE(DirectorState);
};

};
};

#endif