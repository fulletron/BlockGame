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
// CharacterCreationState is itself a state of Game.
selective:
public:
	virtual _INT32 onEnter(Game * a_g);
	virtual _INT32 onUpdate(Game * a_g);
	virtual _INT32 onExit(Game * a_g);
#pragma endregion

#pragma region STATE MACHINE FUNCTIONALITY
	/// ================ STATE MACHINE FUNCTIONALITY =======================
selective :
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

	virtual void IStateMachine<CharacterCreationState>::changeState(State::IState<CURRENT_TEMPLATE> * a_newState)
	{
		delete m_pCurrentState;
		m_pCurrentState = a_newState;
	}
	/// ===================================================================
#pragma endregion
};

};
};

#endif