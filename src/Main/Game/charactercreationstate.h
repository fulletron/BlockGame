#ifndef __CHARACTERCREATIONSTATE_H_
#define __CHARACTERCREATIONSTATE_H_

#include <Utilities/typedefinitions.h>
#include "state.h"
#include "game.h"

namespace GS {
namespace State {

class CharacterCreationState : public IState<Game>, IStateMachine<CharacterCreationState>
{
#pragma region STATE FUNCTIONALITY
	typedef Game CURRENT_ISTATE_TEMPLATE;
	// This is itself a state for the CURRENT_ISTATE_TEMPLATE State Machine.
selective:
public:
	virtual _INT32 onEnter(CURRENT_ISTATE_TEMPLATE *);
	virtual _INT32 onUpdate(CURRENT_ISTATE_TEMPLATE *);
	virtual _INT32 onExit(CURRENT_ISTATE_TEMPLATE *);
#pragma endregion

#pragma region STATE MACHINE FUNCTIONALITY
	/// ================ STATE MACHINE FUNCTIONALITY =======================
selective:
	typedef CharacterCreationState CURRENT_TEMPLATE;
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