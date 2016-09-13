#ifndef __FLYLOADSTATE_H_
#define __FLYLOADSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../characterchosenstate.h"

namespace GS {
namespace State {

class FlyLoadState : public IState<CharacterChosenState>
{
	IMPLEMENT_ISTATE(CharacterChosenState);
};

};
};

#endif