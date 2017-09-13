#ifndef __STATETRANSITIONER_H_
#define __STATETRANSITIONER_H_

#include <Utilities\definitions_types.h>

// Needed for definition of TransStatus
#include <Framework/transition/transition.h>

// Needed for state
#include <Framework/state/state.h>

// typeinfo
#include <typeinfo>   // operator typeid


//#include "Utilities/time/itime.h"
//extern GS::Utilities::ITime * g_pTime;

namespace GS {
namespace State {

/*
* Handles all of the time aspects of a transition from a state to a state.
* TransitionIn is decided at onEnter, using m_pPreviousState as a typeid
* TransitionOut is decided during onUpdate, using armForTransitionTo
*/
template <typename MACHINE> class StateTransitioner
{
selective :
	// Pointer to the time object
	//GS::Utilities::ITime * m_pTime;

	// The total duration of the transition.
	_DOUBLE m_transDuration;

	// How much time has elapsed during the transition
	_DOUBLE m_timeElapsed;

	// The current status of the transition.
	GS::Transition::TransStatus m_transStatus;

	// The state being transitioned into
	GS::State::IState<MACHINE> * m_pNextState;
	std::string m_nextStateName;

	// The state that the current state came from
	GS::State::IState<MACHINE> * m_pPreviousState;
	std::string m_previousStateName;

public:

	StateTransitioner()
	{
		m_timeElapsed = 0.0;
		//m_pTime = 0;
		m_transDuration = 0.0;

		m_transStatus = GS::Transition::TransStatus::TRANS_STA_UNKNOWN;

		m_pNextState = 0;
		m_nextStateName = "";
		m_pPreviousState = 0;
		m_previousStateName = "";
	}
	~StateTransitioner()
	{
		m_timeElapsed = 0.0;
		//m_pTime = 0;
		m_transDuration = 0.0;

		m_transStatus = GS::Transition::TransStatus::TRANS_STA_UNKNOWN;

		m_pNextState = 0;
		m_nextStateName = "";
		m_pPreviousState = 0;
		m_previousStateName = "";
	}

	_UINT32 StateTransitioner<MACHINE>::init(/*GS::Utilities::ITime * a_pTime*/)
	{
		//m_pTime = a_pTime;

		return 0;
	}

	_UINT32 StateTransitioner<MACHINE>::shutdown()
	{
		// MOVED THIS BIT TO DESTRUCTOR
		return 0;
	}

	_DOUBLE StateTransitioner<MACHINE>::getCurrentPercentageComplete(const GS::Transition::TransStatus & a_transWhich) const
	{
		if (a_transWhich == GS::Transition::TransStatus::TRANS_OUT
		|| a_transWhich == GS::Transition::TransStatus::TRANS_IN)
		{
			if (m_transDuration == 0.00)
				return 1.00;
			else
				return m_timeElapsed / m_transDuration;
		}
		else
		{
			// KYLE :: ERROR CHECK
			DEBUG_OUT_RED("getCurrentPercentageComplete was given an unknown transStatus.");
			return 1.00;
		}
	}

	/*
	* decides whether or not the state is done transitioning.
	* Returns TRUE if transitioning
	* Returns FALSE if not transitioning
	*/
	_BOOL StateTransitioner<MACHINE>::overrideUpdate(MACHINE * a_sm, _DOUBLE a_dt)
	{
		switch (m_transStatus)
		{
		case GS::Transition::TransStatus::TRANS_UPDATE:
		case GS::Transition::TransStatus::TRANS_STA_UNKNOWN:
			return false;
			break;
		default:
			break;
		};
		
		_DOUBLE transPerc = 0.0;

		switch (m_transStatus)
		{
		case GS::Transition::TransStatus::TRANS_IN:
		//m_timeElapsed += m_pTime->getDeltaTime();
		m_timeElapsed += a_dt;
		transPerc = getCurrentPercentageComplete(m_transStatus);
		if (transPerc >= 1.00)
		{
			DEBUG_OUT(a_sm->getState()->whoAmI() + " :: Trans In Complete!");
			m_transStatus = GS::Transition::TransStatus::TRANS_UPDATE;
			m_timeElapsed = 0.00;
		}
		break;
		case GS::Transition::TransStatus::TRANS_OUT:
		//m_timeElapsed += m_pTime->getDeltaTime();
		m_timeElapsed += a_dt;
		transPerc = getCurrentPercentageComplete(m_transStatus);
		if (transPerc >= 1.00)
		{
			DEBUG_OUT(a_sm->getState()->whoAmI() + " ST :: Trans Out Complete!");
			m_timeElapsed = 0.00;
			// CANT CALL SHUTDOWN HERE, AS 
			// IT NULLS OUT m_pNextState
			a_sm->changeState(m_pNextState);
			// IT IS TOO LATE TO CALL SHUTDOWN.
			// THE DELETE FUNCTION IS HAPPENING, AND THAT MEANS MEMBER VARIABLES
			// MIGHT BECOME NOTHING.
		}
		break;
		default:
		break;
		}
		return true;
	}

	/*
	* This will tell the transitioner to set sail for the next stage.
	* CALL THIS FROM onUpdate
	*/
	_UINT32 StateTransitioner<MACHINE>::armForTransitionTo(GS::State::IState<MACHINE> * a_pNextState, GS::State::IState<MACHINE> * a_pCurrentState, _DOUBLE a_duration)
	{
		m_transStatus = GS::Transition::TransStatus::TRANS_OUT;
		m_pNextState = a_pNextState;
		m_pNextState->getStateTransitioner()->setPreviousStateName(a_pCurrentState->whoAmI());
		m_nextStateName = m_pNextState->whoAmI();
		m_transDuration = a_duration;

		return 0;
	}

	/*
	* This will tell the transitioner to begin transitioning in.
	* CALL THIS FROM onEnter
	*/
	_UINT32 StateTransitioner<MACHINE>::armForTransitionFrom(_DOUBLE a_duration)
	{
		m_transStatus = GS::Transition::TransStatus::TRANS_IN;
		m_transDuration = a_duration;

		return 0;
	}

	/*
	* returns the name of the previous state
	*/
	std::string StateTransitioner<MACHINE>::getPreviousStateName()
	{
		return m_previousStateName;
	}

	/*
	* returns the name of the previous state
	*/
	void StateTransitioner<MACHINE>::setPreviousStateName(std::string a_name)
	{
		m_previousStateName = a_name;
	}


	/*
	* returns the name of the next state
	*/
	std::string StateTransitioner<MACHINE>::getNextStateName()
	{
		return m_nextStateName;
	}

};

};
};

#endif