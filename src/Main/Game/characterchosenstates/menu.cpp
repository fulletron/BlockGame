#include "menu.h"

#include "menustates/equipmentstate.h"

namespace GS {
namespace State {

_INT32 Menu::onEnter(CharacterChosenState * a_g)
{
	// When opening the menu, the initial state is the MenuCharacterState
	m_pCurrentState = new EquipmentState();

	// perhaps have a flag here to open as either equipment state or as inspect player state.
	return 0;
}

_INT32 Menu::onUpdate(CharacterChosenState * a_g)
{
	// If the menu has no state, we should be prepping for a close somewhere else
	if (!m_pCurrentState)
		return 0;

	m_pCurrentState->onUpdate(this);

	return 0;
}

_INT32 Menu::onExit(CharacterChosenState * a_g)
{
	// When closing the menu, you can delete whatever menu specific state currently exists.
	delete m_pCurrentState;
	m_pCurrentState = 0;

	return 0;
}

};
};