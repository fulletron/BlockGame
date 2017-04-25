#include "test3state.h"

// Target state
#include "test2state.h"

#ifdef DEBUG_OUTPUT_ENABLED
#include <iostream>
#endif

#include "Utilities/input/iinput.h"
extern GS::Utilities::IInput * g_pInput;

namespace GS {
namespace State {

_UINT32 Test3State::onEnter(OverState * a_sm)
{
	DEBUG_OUT("TEST3STATE ENTER ");
	return 0;
}

_UINT32 Test3State::onUpdate(OverState * a_sm)
{
	if (m_stateTransitioner.overrideUpdate(a_sm, this))
		return 0;

	if (g_pInput->isPressed(50))
	{
		GS::Transition::TransRecipe transOut(
			GS::Transition::TransDirection::TRANS_RIGHT,
			GS::Transition::TransEffect::TRANS_FADE,
			0.25);
		GS::Transition::TransRecipe transIn(
			GS::Transition::TransDirection::TRANS_LEFT,
			GS::Transition::TransEffect::TRANS_FADE,
			0.25);
		Test2State * pNextState = new Test2State();
		m_stateTransitioner.armForTransitions(transOut, pNextState, pNextState, transIn);
		DEBUG_OUT("Just Armed to trans from 3 to 2. ");
	}
	return 0;
}

_UINT32 Test3State::onExit(OverState * a_sm)
{
	DEBUG_OUT("TEST3STATE EXIT ");
	return 0;
}

};
};