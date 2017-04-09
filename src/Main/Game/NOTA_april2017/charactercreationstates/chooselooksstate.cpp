#include "chooselooksstate.h"

namespace GS {
namespace State {

_INT32 ChooseLooksState::onEnter(CharacterCreationState * a_g)
{
	return 0;
}

_INT32 ChooseLooksState::onUpdate(CharacterCreationState * a_g)
{
	// Possible Outs:
	// ChooseDisciplineState (from accepting and moving forward)
	// CharacterSelectState (from canceling creation and moving back)
	return 0;
}

_INT32 ChooseLooksState::onExit(CharacterCreationState * a_g)
{
	return 0;
}

};
};