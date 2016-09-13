#ifndef __MENU_H_
#define __MENU_H_

#include <Utilities/typedefinitions.h>
#include "../characterchosenstate.h"

namespace GS {
namespace State {

// The Menu class should NOT have to know anything about any state it is being called from. If the menu is closed
// via the menu button, then it is force-quitted from the state that instatiated it. If the menu is dismissed,
// it can be cleaned up at a later point? Cleanup, as in, when "dismiss" is issued, convert it to a menu button press
// which will be caught by the current state to force-quit (hack).
class Menu : public IStateMachine<Menu>
{
	// Implementing these function because I happen to use them, not because I need them.
	IMPLEMENT_ISTATE(CharacterChosenState);

	IMPLEMENT_ISTATEMACHINE(Menu);
};

};
};

#endif