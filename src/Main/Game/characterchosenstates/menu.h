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
#pragma region STATE FUNCTIONALITY
	typedef CharacterChosenState CURRENT_ISTATE_TEMPLATE;
	// This is itself a state for the CURRENT_ISTATE_TEMPLATE State Machine.
selective:
public:
	virtual _INT32 onEnter(CURRENT_ISTATE_TEMPLATE *);
	virtual _INT32 onUpdate(CURRENT_ISTATE_TEMPLATE *);
	virtual _INT32 onExit(CURRENT_ISTATE_TEMPLATE *);
#pragma endregion

#pragma region STATE MACHINE FUNCTIONALITY
	/// ================ STATE MACHINE FUNCTIONALITY =======================
selective :
	typedef Menu CURRENT_TEMPLATE;
	// I can just change this one typedef and it will be a different class template
	// this block will be copy-pasted. If I create a base class that isn't an 
	// interface, I risk accidentally implementing multiple inheritance, which
	// would be bad.
	State::IState<CURRENT_TEMPLATE> * m_pCurrentState;

public:
	virtual State::IState<CURRENT_TEMPLATE> * getState()
	{
		return m_pCurrentState;
	}

	virtual void IStateMachine<CURRENT_TEMPLATE>::changeState(State::IState<CURRENT_TEMPLATE> * a_newState)
	{
		// Exit the Old State.
		m_pCurrentState->onExit(this);

		// Clean it up
		delete m_pCurrentState;
		m_pCurrentState = a_newState;

		// Enter the New State.
		m_pCurrentState->onEnter(this);
	}
#pragma endregion

};

};
};

#endif