#include "directorstate.h"
#include "directorstates/worldmapstate.h"

namespace GS {
namespace State {

_INT32 DirectorState::onEnter(CharacterChosenState * a_g)
{
	m_pCurrentState = new WorldMapState();
	return 0;
}

_INT32 DirectorState::onUpdate(CharacterChosenState * a_g)
{
	// Update the current map it is on.
	m_pCurrentState->onUpdate(this);

	// If the menu button is pressed, allow it to happen
//	if (MENU_OPENED)
//	{
//		m_pMenu = new Menu<>()
//	}

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