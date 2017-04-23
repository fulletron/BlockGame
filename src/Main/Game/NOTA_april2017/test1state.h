#ifndef __TEST1STATE_H_
#define __TEST1STATE_H_

#include <Utilities/definitions_types.h>
#include "../overstate.h"
#include "../../state/statetransitionable.h"

namespace GS {
namespace State {

class Test1State : public IState<OverState>, IStateTransitionable<OverState>
{
	IMPLEMENT_ISTATE_NOUPDATE(OverState);
	IMPLEMENT_ISTATETRANSITIONABLE(OverState);
	IMPLEMENT_ISTATETRANSITIONABLE_UPDATEOVERRIDE(OverState);
};

};
};

#endif