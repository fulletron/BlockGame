#ifndef __STATEMACHINE_H_
#define __STATEMACHINE_H_

#include <Utilities/typedefinitions.h>
#include "state.h"

namespace GS {
namespace State {

template <typename T>
class IStateMachine
{
public:
	virtual ~IStateMachine(){}
	virtual IState<T> * getState() = 0;
	virtual void changeState(IState<T> *) = 0;
};

// ENSURE \ IS THE LAST CHARACTER
#define IMPLEMENT_ISTATEMACHINE(MACHINE)							\
selective:															\
State::IState<MACHINE> * m_pCurrentState;							\
public:																\
	virtual State::IState<MACHINE> * getState()						\
	{																\
		return m_pCurrentState;										\
	}																\
	virtual void IStateMachine<MACHINE>::							\
		changeState(State::IState<MACHINE> * a_newState)			\
	{																\
		m_pCurrentState->onExit(this);								\
		delete m_pCurrentState;										\
		m_pCurrentState = a_newState;								\
		m_pCurrentState->onEnter(this);								\
	}																\

};
};

#endif