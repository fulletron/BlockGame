#ifndef __MENUSTATE_H_
#define __MENUSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../characterchosenstate.h"

namespace GS {
namespace State {

class MenuState : public IState<CharacterChosenState>, IStateMachine<MenuState>
{
#pragma region STATE FUNCTIONALITY
selective:
public:
	virtual _INT32 onEnter(CharacterChosenState * a_g);
	virtual _INT32 onUpdate(CharacterChosenState * a_g);
	virtual _INT32 onExit(CharacterChosenState * a_g);
#pragma endregion

#pragma region STATE MACHINE FUNCTIONALITY
	/// ================ STATE MACHINE FUNCTIONALITY =======================
selective :
	typedef MenuState CURRENT_TEMPLATE;
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
		delete m_pCurrentState;
		m_pCurrentState = a_newState;
	}
	/// ===================================================================
#pragma endregion

};

};
};

#endif