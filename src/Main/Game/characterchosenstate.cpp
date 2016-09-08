#include "characterchosenstate.h"
#include "characterchosenstates/directorstate.h"
#include "characterselectstate.h"

namespace GS {
namespace State {

_INT32 CharacterChosenState::onEnter(Game * a_g)
{
	// Director is first state
	// call it, and enter it.
	m_pCurrentState = new DirectorState();
	m_pCurrentState->onEnter(this);
	return 0;
}

_INT32 CharacterChosenState::onUpdate(Game * a_g)
{
	// Update sub state.
	m_pCurrentState->onUpdate(this);

	// From here, I can only exit the game to select state
#define PLAYER_LOGOUT 0
	if (PLAYER_LOGOUT)
	{
		// save off current character
		//
		// delete all data regarding play
		//
		// change state
		a_g->changeState(new CharacterSelectState());
	}
	return 0;
}

_INT32 CharacterChosenState::onExit(Game * a_g)
{
	// Exit the substate without going to a new substate.
	m_pCurrentState->onExit(this);
	// Then delete it, and null it
	delete m_pCurrentState;
	m_pCurrentState = 0;

	return 0;
}

};
};