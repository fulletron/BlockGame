#ifndef __DIRECTORSTATE_H_
#define __DIRECTORSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../characterchosenstate.h"

namespace GS {
namespace State {

class DirectorState : public IState<CharacterChosenState>, IStateMachine<DirectorState>
{
	IMPLEMENT_ISTATE(CharacterChosenState);
	IMPLEMENT_ISTATEMACHINE(DirectorState);
};

};
};

#endif