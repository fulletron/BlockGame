#include "game.h"

#include "characterselectstate.h"

namespace GS {

_INT32 Game::init()
{
	// DO ALL THE INITIAL LOADING HERE

	// The first game state on bootup is the character select state.
	m_pCurrentState = new State::CharacterSelectState();

	return 0;
}

};