#ifndef __STATETRANSITIONABLE_H_
#define __STATETRANSITIONABLE_H_

#include <Utilities\definitions_types.h>

#include "state.h"

namespace GS {
namespace State {

/**
* This is a State of the machine provided by the template.
*/
template <typename MACHINE> class IStateTransitionable
{
public:
	const enum TransStatus {
		TRANS_UPDATE = 0,
		TRANS_IN = 1,
		TRANS_OUT = 2,
		TRANS_UNKNOWN = 3
	};

public:
	virtual ~IStateTransitionable(){}
	virtual _UINT32 initTransitionable() = 0;
	virtual _UINT32 shutdownTransitionable() = 0;
	virtual _UINT32 onTransitionIn(MACHINE *) = 0;
	virtual _UINT32 onActualUpdate(MACHINE *) = 0;
	virtual _UINT32 onTransitionOut(MACHINE *) = 0;
	virtual void setNextState(IState<MACHINE> *) = 0;
	virtual IState<MACHINE> * getNextState() = 0;
	virtual void setTransitionStatus(const TransStatus &) = 0;
	virtual TransStatus getTransitionStatus() = 0;
};


// ENSURE the \ is the last character
/**
* ADDS MEMBER VARIABLES:
* IState<MACHINE> *		m_pNextState;
* TransStatus			m_transStatus;
*i_
* Creates the virtual functions for all of IStateTransitioner.
*/
#define IMPLEMENT_ISTATETRANSITIONABLE(MACHINE)		\
selective: \
	IState<MACHINE> * m_pNextState; \
	TransStatus m_transStatus; \
	\
public:									\
	virtual _UINT32 initTransitionable(); \
	virtual _UINT32 shutdownTransitionable(); \
	virtual _UINT32 onTransitionIn(MACHINE *);	\
	virtual _UINT32 onActualUpdate(MACHINE *);	\
	virtual _UINT32 onTransitionOut(MACHINE *);	\
	\
	virtual void setNextState(IState<MACHINE> * a_state) \
	{ m_pNextState = a_state; } \
	virtual IState<MACHINE> * getNextState ()\
	{ return m_pNextState; } \
	virtual void setTransitionStatus(const TransStatus & a_status) \
	{ m_transStatus = a_status; } \
	virtual TransStatus getTransitionStatus() \
	{ return m_transStatus; }

/**
* OVERRIDES the update function fit transition scheme.
*/
#define IMPLEMENT_ISTATETRANSITIONABLE_UPDATEOVERRIDE(MACHINE)		\
public:									\
	virtual _UINT32 onUpdate(MACHINE * a_machine)	\
	{ \
		switch(m_transStatus) \
		{ \
			case TransStatus::TRANS_IN: \
				onTransitionIn(a_machine); \
				break; \
			case TransStatus::TRANS_OUT: \
				onTransitionOut(a_machine); \
				break; \
			case TransStatus::TRANS_UPDATE: \
			default: \
				onActualUpdate(a_machine); \
				break; \
		} \
		return 0; \
	}


};
};

#endif