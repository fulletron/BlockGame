#ifndef __TEST3STATE_H_
#define __TEST3STATE_H_

#include <Utilities/definitions_types.h>
#include "../overstate.h"
#include "../../state/statetransitioner.h"
#include "../../state/istatetransitioner.h"

namespace GS {
namespace State {

class Test3State : public IState<OverState>, public GS::Transition::IHasTransitioner
{
	IMPLEMENT_ISTATE(OverState);
	IMPLEMENT_IHASTRANSITIONER(OverState);
};

};
};

#endif