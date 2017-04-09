#ifndef __CHARACTERCHOSENSTATE_H_
#define __CHARACTERCHOSENSTATE_H_

#include <Utilities/typedefinitions.h>
#include "game.h"

namespace GS {
namespace State {

class CharacterChosenState : public IState<Game>, IStateMachine<CharacterChosenState>
{
	IMPLEMENT_ISTATE(Game);
	IMPLEMENT_ISTATEMACHINE(CharacterChosenState);
};

};
};

#endif