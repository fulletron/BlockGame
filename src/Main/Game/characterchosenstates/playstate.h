#ifndef __PLAYSTATE_H_
#define __PLAYSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../characterchosenstate.h"

namespace GS {
namespace State {

class PlayState : public IState<CharacterChosenState>
{
	IMPLEMENT_ISTATE(CharacterChosenState);
};

};
};

#endif