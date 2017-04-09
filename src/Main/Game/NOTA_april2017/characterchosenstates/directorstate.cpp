#include "directorstate.h"
#include "directorstates/launchpadstate.h"

namespace GS {
namespace State {

_INT32 DirectorState::onEnter(CharacterChosenState * a_g)
{
	// No mission is selected when initially entering this state.
	m_selectedMission = 0;

	// This state starts in the LaunchPadState();
	m_pCurrentState = new LaunchPadState();
	return 0;
}

_INT32 DirectorState::onUpdate(CharacterChosenState * a_g)
{
	// have the menu only react to the director state.
	if (menuIsOpen())
		m_pCurrentMenu->onUpdate();
	else
		m_pCurrentState->onUpdate(this);

	return 0;
}

_INT32 DirectorState::onExit(CharacterChosenState * a_g)
{
	m_pCurrentState->onExit(this);
	delete m_pCurrentState;
	m_pCurrentState = 0;

	return 0;
}

};
};