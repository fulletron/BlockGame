#ifndef __STATETRANSITIONER_H_
#define __STATETRANSITIONER_H_

#include <Utilities\definitions_types.h>

#include "state.h"
#include "istatetransitioner.h"

#ifdef DEBUG_OUTPUT_ENABLED
#include <iostream>
#endif

#include "Utilities/time/itime.h"
extern GS::Utilities::ITime * g_pTime;

namespace GS {
namespace State {

template <typename MACHINE> class StateTransitioner
{
public:
	const enum TransStatus {
		TRANS_STA_UNKNOWN = 0,
		TRANS_IN = 1,
		TRANS_OUT = 2,
		TRANS_UPDATE = 3
	};

	const enum TransDirection {
		TRANS_DIR_UNKNOWN = 0,
		TRANS_UP = 1,
		TRANS_DOWN = 2,
		TRANS_LEFT = 3,
		TRANS_RIGHT = 4,
		TRANS_NODIR = 5
	};

	const enum TransEffect {
		TRANS_EFF_UNKNOWN = 0,
		TRANS_FADE = 1,
		TRANS_NOFADE = 2
	};

	struct TransRecipe
	{
		TransDirection dir;
		TransEffect eff;
		_DOUBLE duration;
		TransRecipe()
		{
			dir = TRANS_DIR_UNKNOWN;
			eff = TRANS_EFF_UNKNOWN;
			duration = 0.0;
		}
		TransRecipe(TransDirection a_dir, TransEffect a_eff, _DOUBLE a_dur)
		{
			dir = a_dir;
			eff = a_eff;
			duration = a_dur;
		}
	};

selective:
	_DOUBLE m_timeElapsed;

	TransStatus m_transStatus;

	TransRecipe m_transIn;
	TransRecipe m_transOut;

	IState<MACHINE> * m_pNextState;

public:

	StateTransitioner()
	{
		m_timeElapsed = 0.0;

		m_transStatus = TransStatus::TRANS_STA_UNKNOWN;

		TransRecipe blank;
		m_transIn = blank;
		m_transOut = blank;
	}
	~StateTransitioner(){}

	_UINT32 StateTransitioner<MACHINE>::shutdown()
	{
		m_timeElapsed = 0.0;
		m_transStatus = TransStatus::TRANS_STA_UNKNOWN;

		return 0;
	}

	_DOUBLE StateTransitioner<MACHINE>::transitionPercentageComplete( const TransStatus & a_transWhich )
	{
		if (a_transWhich == TransStatus::TRANS_OUT)
		{
			if (m_transOut.duration == 0.00)
				return 1.00;
			else
				return m_timeElapsed / m_transOut.duration;
		}
		else if (a_transWhich == TransStatus::TRANS_IN)
		{
			if (m_transIn.duration == 0.00)
				return 1.00;
			else
				return m_timeElapsed / m_transIn.duration;
		}
		else
		{
			// KYLE :: ERROR CHECK
			return 1.00;
		}
	}

	_BOOL StateTransitioner<MACHINE>::overrideUpdate(MACHINE * a_sm, IState<MACHINE> * a_currentState)
	{
		switch (m_transStatus)
		{
		case TransStatus::TRANS_UPDATE:
		case TransStatus::TRANS_STA_UNKNOWN:
			return false;
			break;
		default:
			break;
		};
		
		m_timeElapsed += g_pTime->getDeltaTime();
		_DOUBLE transPerc = transitionPercentageComplete(m_transStatus);

		//DEBUG_OUT(" ST :: m_timeElapsed == " << m_timeElapsed << ".");

		switch (m_transStatus)
		{
		case StateTransitioner::TransStatus::TRANS_IN:
		//DEBUG_OUT(" ST :: TRANSITIONING IN! " << transPerc << "%");
		if (transPerc >= 1.00)
		{
			DEBUG_OUT(" ST :: Trans In Complete!");
			m_transStatus = TransStatus::TRANS_UPDATE;
			m_timeElapsed = 0.00;
		}
		break;
		case StateTransitioner::TransStatus::TRANS_OUT:
		//DEBUG_OUT(" ST :: TRANSITIONING OUT! " << transPerc << "%" );
		if (transPerc >= 1.00)
		{
			DEBUG_OUT(" ST :: Trans Out Complete!");
			m_timeElapsed = 0.00;
			a_sm->changeState(m_pNextState);
			shutdown();
		}
		break;
		default:
		break;
		}
		return true;
	}

	_UINT32 StateTransitioner<MACHINE>::armForTransitions(TransRecipe a_currentOut, IState<MACHINE> * a_pNextState, IStateTransitioner<MACHINE> * a_pNextStateTrans, TransRecipe a_nextIn)
	{
		setRecipe(TransStatus::TRANS_OUT, a_currentOut);
		m_pNextState = a_pNextState;

		if (a_pNextStateTrans)
		{
			StateTransitioner<MACHINE> * pNextTrans = a_pNextStateTrans->getStateTransitioner();
			pNextTrans->setRecipe(TransStatus::TRANS_IN, a_nextIn);
		}

		return 0;
	}

	void StateTransitioner<MACHINE>::setRecipe(const TransStatus & a_transWhich, TransRecipe a_recipe)
	{
		if (a_transWhich == TransStatus::TRANS_OUT)
		{
			m_transOut = a_recipe;
			m_transStatus = a_transWhich;
		}
		else if (a_transWhich == TransStatus::TRANS_IN)
		{
			m_transIn = a_recipe;
			m_transStatus = a_transWhich;
		}
		else
		{
			// KYLE :: ERROR CHECK
		}
	}

};

};
};

#endif