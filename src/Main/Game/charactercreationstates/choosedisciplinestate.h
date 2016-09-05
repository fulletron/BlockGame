#ifndef __CHOOSEDISCIPLINESTATE_H_
#define __CHOOSEDISCIPLINESTATE_H_

#include <Utilities/typedefinitions.h>
#include "../charactercreationstate.h"

namespace GS {
namespace State {

class ChooseDisciplineState : public IState<CharacterCreationState>
{
#pragma region STATE FUNCTIONALITY
// CharacterCreationState is itself a state of Game.
selective:
public:
	virtual _INT32 onEnter(CharacterCreationState * a_g);
	virtual _INT32 onUpdate(CharacterCreationState * a_g);
	virtual _INT32 onExit(CharacterCreationState * a_g);
#pragma endregion

};

};
};

#endif