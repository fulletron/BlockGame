#ifndef __TEST2STATE_H_
#define __TEST2STATE_H_

#include <Utilities/definitions_types.h>
#include "../overstate.h"

namespace GS {
namespace State {

class Test2State : public IState<OverState>
{
	IMPLEMENT_ISTATE(OverState);
};

};
};

#endif