#ifndef __STATE_H_
#define __STATE_H_

#include <Utilities/typedefinitions.h>

namespace GS {
namespace State {

class CharacterSelectState : public IState<Game>
{
selective:
public:
	virtual _INT32 onEnter(Game * a_g)
	{
		// This is the initial bootup state: 
		// Load Basic Resources
		// This is probably where the black loading screen with basic icon is inited
		// Load the minimum req of any save data options and present them in a list
		return 0;
	}

	virtual _INT32 onUpdate(Game * a_g, double a_dt)
	{
		// Allow the player to look over the list.
		// "Scrolling Over" different characters should load different images.


		// BASED ON INPUT
		if (CHARACTER_IS_PICKED)
		{
			// Load character data into player data (probably located in GAME) for the CharacterChosenState to handle
			a_g->setCharacter(this char);

			// Change the state to CharacterChosenState
			a_g->changeState(new CharacterChosenState());
		}
		else if (NEW_CHARACTER)
		{
			// Setup whatever mildly temporary structures are necessary to ultimately save out a character that can be loaded.

			// Change the state to CharacterCreationState()
			a_g->changeState(new CharacterCreationState());
		}

		return 0;
	}

	virtual _INT32 onExit(Game * a_g)
	{
		// REMEMBER: this gets called after selecting a character AND after deciding to create a new character.
		// Destroy any lists created to present all characters.
		return 0;
	}
};

};
};

#endif