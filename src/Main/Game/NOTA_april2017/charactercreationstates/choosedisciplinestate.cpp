#include "choosedisciplinestate.h"

namespace GS {
namespace State {

_INT32 ChooseDisciplineState::onEnter(CharacterCreationState * a_g)
{
	return 0;
}

_INT32 ChooseDisciplineState::onUpdate(CharacterCreationState * a_g)
{
	// Possible Outs:
	// CharacterChosenState (from accepting and moving forward)
	// CharacterSelectState (from canceling creation and moving back)
	return 0;
}

_INT32 ChooseDisciplineState::onExit(CharacterCreationState * a_g)
{
	return 0;
}

};
};