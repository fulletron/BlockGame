#include "test2state.h"

// Target state
#include "test3state.h"

#ifdef DEBUG_OUTPUT_ENABLED
#include <iostream>
#endif

#include "Utilities/input/iinput.h"
extern GS::Utilities::IInput * g_pInput;

namespace GS {
namespace State {

_UINT32 Test2State::onEnter(OverState * a_sm)
{
	DEBUG_OUT("TEST2STATE ENTER");
	return 0;
}

_UINT32 Test2State::onUpdate(OverState * a_sm)
{
	if (m_stateTransitioner.overrideUpdate(a_sm, this))
		return 0;

	if (g_pInput->isPressed(49))
	{
		StateTransitioner<OverState>::TransRecipe transOut
			(StateTransitioner<OverState>::TransDirection::TRANS_RIGHT, 
			StateTransitioner<OverState>::TransEffect::TRANS_FADE,
			0.25);
		StateTransitioner<OverState>::TransRecipe transIn
			(StateTransitioner<OverState>::TransDirection::TRANS_LEFT,
			StateTransitioner<OverState>::TransEffect::TRANS_FADE,
			0.25);
		Test3State * pNextState = new Test3State();
		m_stateTransitioner.armForTransitions(transOut, pNextState, pNextState, transIn);
		DEBUG_OUT("Armed for transition from 2 to 3.");
	}
	return 0;
}

_UINT32 Test2State::onExit(OverState * a_sm)
{
	DEBUG_OUT("TEST2STATE EXIT ");
	return 0;
}

};
};