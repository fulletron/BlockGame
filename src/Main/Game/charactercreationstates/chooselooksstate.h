#ifndef __CHOOSELOOKSSTATE_H_
#define __CHOOSELOOKSSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../charactercreationstate.h"

namespace GS {
namespace State {

class ChooseLooksState : public IState<CharacterCreationState>
{
#pragma region STATE FUNCTIONALITY
// CharacterCreationState is itself a state of Game.
selective:
public:
	virtual _INT32 onEnter(CharacterCreationState *);
	virtual _INT32 onUpdate(CharacterCreationState *);
	virtual _INT32 onExit(CharacterCreationState *);
#pragma endregion

};

};
};

#endif