#include "menustate.h"

#include "menustates/equipmentstate.h"

namespace GS {
namespace State {

_INT32 MenuState::onEnter(CharacterChosenState * a_g)
{
	// When opening the menu, the initial state is the MenuCharacterState
	m_pCurrentState = new EquipmentState();
	return 0;
}

_INT32 MenuState::onUpdate(CharacterChosenState * a_g)
{
	return 0;
}

_INT32 MenuState::onExit(CharacterChosenState * a_g)
{
	// When closing the menu, you can delete whatever menu specific state currently exists.
	delete m_pCurrentState;
	m_pCurrentState = 0;

	return 0;
}

};
};