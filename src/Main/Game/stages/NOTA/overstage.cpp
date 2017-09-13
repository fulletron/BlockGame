#include "overstage.h"

// STARTING STATE
#include "overstages/selectstage.h"

#include "Utilities/input/iinput.h"
extern GS::Utilities::IInput * g_pInput;

#include <Utilities/filepath/filepath.h>

#include <Framework/transition/transition.h>

namespace GS {
namespace Stage {

_UINT32 OverStage::init()
{
	// Set the Game to be running.
	m_isRunning = true;

	// Subscribe to all art assets needed for the 
	// SelectState, the CreateState, and the OptionsState
	// WE MIGHT NOT WANT TO DO THE SUBSCRIPTION HERE AT ALL

	// Opening state is the Select State
	SelectStage * pNextState = new SelectStage();

	// SET UP TRANSITIONER
	// This shouldn't happen in onEnter because
	// in some cases, the entrance will be different
	// (menu L1->R1->L1, for example).
	GS::Transition::TransRecipe transIn(
		GS::Transition::TransDirection::TRANS_NODIR,
		GS::Transition::TransEffect::TRANS_FADE,
		0.0);
	pNextState->setTransitionersRecipe(
		GS::Transition::TransStatus::TRANS_IN,
		transIn
		);

	m_pCurrentState = pNextState;

	// Call onEnter, which will check
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