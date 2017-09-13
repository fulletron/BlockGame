#include "overstage.h"

// STARTING STATE
#include "overstages/selectstage.h"

#include "Utilities/input/iinput.h"
extern GS::Utilities::IInput * g_pInput;

#include "Utilities/filepath/filepath.h"

#include "Launchpad/transition/transition.h"

namespace GS {
namespace Stage {

_UINT32 OverStage::init()
{
	m_isRunning = true;
	// Director is first state
	// call it, and enter it.
	SelectStage * pNextState = new SelectStage();
	/*
	GS::Transition::TransRecipe transIn(
		GS::Transition::TransDirection::TRANS_NODIR,
		GS::Transition::TransEffect::TRANS_FADE,
		0.0);
	pNextState->setTransitionersRecipe(
		GS::Transition::TransStatus::TRANS_IN,
		transIn
		);
	*/
	m_pCurrentState = pNextState;
	m_pCurrentState->onEnter(this);

	DEBUG_OUT(FILEPATH.getAbsoluteFilePath_str());
	DEBUG_OUT_RED("This text is red!");
	DEBUG_OUT_YELLOW("This text is yellow!");
	DEBUG_OUT_GREEN("This text is green!");
	DEBUG_OUT("test");

	return 0;
}

_UINT32 OverStage::update()
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

_UINT32 OverStage::shutdown()
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

_BOOL OverStage::isRunning()
{
	return m_isRunning;
}

};
};