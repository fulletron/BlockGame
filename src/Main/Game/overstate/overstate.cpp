#include "overstate.h"

// STARTING STATE
#include "teststates/test3state.h"


#include <iostream>


#include "Utilities/input/iinput.h"
extern GS::Utilities::IInput * g_pInput;

namespace GS {
namespace State {

_UINT32 OverState::init()
{
	m_isRunning = true;
	// Director is first state
	// call it, and enter it.
	Test3State * pNextState = new Test3State();

	GS::Transition::TransRecipe transIn(
		GS::Transition::TransDirection::TRANS_NODIR,
		GS::Transition::TransEffect::TRANS_FADE,
		0.0);
	pNextState->setTransitionersRecipe(
		GS::Transition::TransStatus::TRANS_IN,
		transIn
		);
	m_pCurrentState = pNextState;
	m_pCurrentState->onEnter(this);
	return 0;
}

_UINT32 OverState::update()
{
	// Update sub state.
	if (m_pCurrentState)
		m_pCurrentState->onUpdate(this);

	if (g_pInput->isPressed(256))
	{
std::cout << " ESCAPE IS PRESSED " << std::endl;
		shutdown();
	}
	else if (g_pInput->isPressed(87))
	{
std::cout << " W IS PRESSED " << std::endl;
	}
	return 0;
}

_UINT32 OverState::shutdown()
{
	if (m_pCurrentState)
	{
		// Exit the substate without going to a new substate.
		m_pCurrentState->onExit(this);
		// Then delete it, and null it
		delete m_pCurrentState;
		m_pCurrentState = 0;
	}

	m_isRunning = false;

	return 0;
}

_BOOL OverState::isRunning()
{
	return m_isRunning;
}

};
};