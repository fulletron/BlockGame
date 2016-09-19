#ifndef __PLAYSTATE_H_
#define __PLAYSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../characterchosenstate.h"
#include "menu.h"

namespace GS {
namespace State {

class PlayState : public IState<CharacterChosenState>, IMenuable
{
	IMPLEMENT_ISTATE(CharacterChosenState);
	IMPLEMENT_IMENUABLE;
};

};
};

#endif