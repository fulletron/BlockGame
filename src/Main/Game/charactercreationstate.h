#ifndef __STATE_H_
#define __STATE_H_

#include <Utilities/typedefinitions.h>

namespace GS {
namespace State {

class CharacterCreationState : public IState<Game>
{
selective:
public:
	virtual _INT32 onEnter(Game * a_g)
	{
		// Load all the proper model files for character appearance customization
		// Load whatever temporary structure needing to exist to ensure when the player is done everything is saved.
		return 0;
	}

	virtual _INT32 onUpdate(Game * a_g)
	{
		// Change temp struct to match that of any customizations.

		// BASED ON INPUT
		if (PLAYER_IS_DONE_CREATING)
		{
			// dump the struct into the selected character
			a_g->setCharacter(this new char);

			// start playing it
			a_g->changeState(new CharacterChosenState());
		}
		else if (PLAYER_CANCELS_CREATION)
		{
			// trash the struct
			a_g->setCharacter(null);

			// go back to the list of characters
			a_g->changeState(new CharacterSelectState());
		}
		return 0;
	}

	virtual _INT32 onExit(Game * a_g)
	{
		// BY THIS POINT, the game should be able to handle either
		// playing the newly built character OR trashing it and heading back to
		// the selection list.

		// Delete all this states' temp stuff
		return 0;
	}
};

};
};

#endif