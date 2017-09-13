#ifndef __STATEMACHINE_H_
#define __STATEMACHINE_H_

#include <Utilities/definitions_types.h>
#include "state.h"

namespace GS {
namespace State {

template <typename T>
class IStateMachine
{
public:
	virtual ~IStateMachine(){}
	virtual IState<T> * getState() = 0;
	inline virtual void changeState(IState<T> *) = 0;
};

template <typename MACHINE>
class StateMachine : public IStateMachine<MACHINE>
{
selective:
	State::IState<MACHINE> * m_pCurrentState;
public:
	virtual State::IState<MACHINE> * getState()
	{
		return m_pCurrentState;
	}

	virtual void changeState(State::IState<MACHINE> * a_newState) = 0;

	// even with an inline, the "this" pointer still is a StateMachine, and not
	// a derived class.
	//inline virtual void changeState(State::IState<MACHINE> * a_newState)
	//{
	//	m_pCurrentState->onExit(this);
	//	delete m_pCurrentState; 
	//	m_pCurrentState = a_newState; 
	//	m_pCurrentState->onEnter(this); 
	//}

	//virtual void changeState(State::IState<MACHINE> * a_newState)
	//{
	//	m_pCurrentState->onExit(this);
	//	delete m_pCurrentState; 
	//	m_pCurrentState = a_newState; 
	//	m_pCurrentState->onEnter(this); 
	//}
};

/*
* This has to be a define because the definition of the "this"
* pointer needs to be the class defining this function.
*/
#define IMPLEMENT_CHANGESTATE(MACHINE) \
public: \
virtual void changeState(State::IState<MACHINE> * a_newState) \
{ \
	m_pCurrentState->onExit(this); \
	delete m_pCurrentState; \
	m_pCurrentState = a_newState; \
	m_pCurrentState->onEnter(this); \
}

};
};

#endif