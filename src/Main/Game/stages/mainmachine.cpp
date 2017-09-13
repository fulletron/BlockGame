#include "mainmachine.h"

// STARTING STATE
#include "mainstages/launchstage.h"

#include <Utilities/filepath/filepath.h>

#include <Framework/transition/transition.h>

namespace GS {
namespace Stage {

_UINT32 MainMachine::init(GS::Referencer * a_ref)
{
	// This holds all of the stuff i want
	m_pRef = a_ref;
	m_pInput = m_pRef->pInput;

	// Set the Game to be running.
	m_isRunning = true;

	// Subscribe to all art assets needed for the 
	// SelectState, the CreateState, and the OptionsState
	// WE MIGHT NOT WANT TO DO THE SUBSCRIPTION HERE AT ALL

	// Opening state is the Launch State
	LaunchStage * pNextState = new LaunchStage();
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

_UINT32 MainMachine::update()
{
	// Update sub state.
	if (m_pCurrentState)
		m_pCurrentState->onUpdate(this);

// DEBUG STUFF
	if (m_pInput->isPressed(256))
	{
std::cout << " ESCAPE IS PRESSED " << std::endl;
		shutdown();
	}
	else if (m_pInput->isPressed(87))
	{
std::cout << " W IS PRESSED " << std::endl;
	}
	return 0;
}

_UINT32 MainMachine::shutdown()
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

_BOOL MainMachine::isRunning()
{
	return m_isRunning;
}

};
};