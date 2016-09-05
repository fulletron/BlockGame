#include "state.h"
#include "characterselectstate.h"

#include "characterchosenstate.h"
#include "charactercreationstate.h"

namespace GS {
namespace State {

_INT32 CharacterSelectState::onEnter(Game * a_g)
{
	// This is the initial bootup state: 
	// Load Basic Resources
	// This is probably where the black loading screen with basic icon is inited
	// Load the minimum req of any save data options and present them in a list
	return 0;
}

_INT32 CharacterSelectState::onUpdate(Game * a_g)
{
	// Allow the player to look over the list.
	// "Scrolling Over" different characters should load different images.


	// BASED ON INPUT
#define CHARACTER_IS_PICKED 0
	if (CHARACTER_IS_PICKED)
	{
		// Load character data into player data (probably located in GAME) for the CharacterChosenState to handle
		//a_g->setCharacter(this char);

		// Change the state to CharacterChosenState
		a_g->changeState(new CharacterChosenState());
	}
#define NEW_CHARACTER 0
	else if (NEW_CHARACTER)
	{
		// Setup whatever mildly temporary structures are necessary to ultimately save out a character that can be loaded.

		// Change the state to CharacterCreationState()
		a_g->changeState(new CharacterCreationState());
	}

	return 0;
}

_INT32 CharacterSelectState::onExit(Game * a_g)
{
	// REMEMBER: this gets called after selecting a character AND after deciding to create a new character.
	// Destroy any lists created to present all characters.
	return 0;
}

};
};