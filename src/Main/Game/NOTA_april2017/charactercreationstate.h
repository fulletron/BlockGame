#ifndef __CHARACTERCREATIONSTATE_H_
#define __CHARACTERCREATIONSTATE_H_

#include <Utilities/typedefinitions.h>
#include "state.h"
#include "game.h"

namespace GS {
namespace State {

class CharacterCreationState : public IState<Game>, IStateMachine<CharacterCreationState>
{
	IMPLEMENT_ISTATE(Game);
	IMPLEMENT_ISTATEMACHINE(CharacterCreationState);
};

};
};

#endif