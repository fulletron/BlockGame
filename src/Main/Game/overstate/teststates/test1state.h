#ifndef __TEST1STATE_H_
#define __TEST1STATE_H_

#include <Utilities/definitions_types.h>
#include "../overstate.h"

namespace GS {
namespace State {

class Test1State : public IState<OverState>
{
	IMPLEMENT_ISTATE(OverState);
};

};
};

#endif