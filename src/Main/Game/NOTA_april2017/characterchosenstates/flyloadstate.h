#ifndef __FLYLOADSTATE_H_
#define __FLYLOADSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../characterchosenstate.h"
#include "menu.h"

namespace GS {
namespace State {

// Flying loading screen state ala destiny.
class FlyLoadState : public IState<CharacterChosenState>, IMenuable
{
	IMPLEMENT_ISTATE(CharacterChosenState);
	IMPLEMENT_IMENUABLE;
};

};
};

#endif