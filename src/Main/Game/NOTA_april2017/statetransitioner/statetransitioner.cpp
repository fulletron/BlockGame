#include "statetransitioner.h"

namespace GS {
namespace State {
/*
template <typename MACHINE>
StateTransitioner<MACHINE>::StateTransitioner()
{ 
	m_transitionPeriod = 0.0; 
	m_timeElapsed = 0.0; 
	m_transStatus = TransStatus::TRANS_STA_UNKNOWN; 
	m_transInDirection = TransDirection::TRANS_DIR_UNKNOWN;
	m_transOutDirection = TransDirection::TRANS_DIR_UNKNOWN;
	m_transInEffect = TransEffect::TRANS_EFF_UNKNOWN;
	m_transOutEffect = TransEffect::TRANS_EFF_UNKNOWN;
}

template <typename MACHINE>
_UINT32 StateTransitioner<MACHINE>::init(_DOUBLE a_transitionPeriod)
{
	m_transitionPeriod = a_transitionPeriod;
	m_transStatus = TRANS_IN;
}

template <typename MACHINE>
_UINT32 StateTransitioner<MACHINE>::shutdown()
{
	m_transitionPeriod = 0;
	m_timeElapsed = 0;
	m_transStatus = TransStatus::TRANS_STA_UNKNOWN;
}
*/

/*
template <typename MACHINE>
StateTransitioner<MACHINE>::TransStatus StateTransitioner<MACHINE>::getTransStatus() const
{
	return m_transStatus;
}

template <typename MACHINE>
void StateTransitioner<MACHINE>::setTransStatus(const TransStatus & a_status)
{
	m_transStatus = a_status;
}

template <typename MACHINE>
StateTransitioner<MACHINE>::TransDirection StateTransitioner<MACHINE>::getTransDirection(const TransStatus & a_transWhich) const
{
	if (a_transWhich == TRANS_IN)
		return m_transInDirection;
	else if (a_transWhich == TRANS_OUT)
		return m_transOutDirection;
	else
	{
// KYLE :: DO ERROR CHECKING
		return m_transInDirection;
	}
}

template <typename MACHINE>
void StateTransitioner<MACHINE>::setTransDirection(const TransStatus & a_transWhich, const TransDirection & a_dir)
{
	if (a_transWhich == TRANS_IN)
		m_transInDirection = a_dir;
	else if (a_transWhich == TRANS_OUT)
		m_transOutDirection = a_dir;
}

template <typename MACHINE>
StateTransitioner<MACHINE>::TransEffect StateTransitioner<MACHINE>::getTransEffect(const TransStatus & a_transWhich) const
{
	if (a_transWhich == TRANS_IN)
		return m_transInEffect;
	else if (a_transWhich == TRANS_OUT)
		return m_transOutEffect;
	else
	{
		// KYLE :: DO ERROR CHECKING
		return m_transInEffect;
	}
}

template <typename MACHINE>
void StateTransitioner<MACHINE>::setTransEffect(const TransStatus & a_transWhich, const TransEffect & a_effect)
{
	if (a_transWhich == TRANS_IN)
		m_transInEffect = a_effect;
	else if (a_transWhich == TRANS_OUT)
		m_transOutEffect = a_effect;
}

*/
/*
template <typename MACHINE>
_DOUBLE StateTransitioner<MACHINE>::transitionPercentageComplete()
{
	return (m_timeElapsed / m_transitionPeriod);
}
*/

/*
template <typename MACHINE>
_BOOL StateTransitioner<MACHINE>::overrideUpdate(MACHINE * a_sm, IState<MACHINE> * a_currentState)
{
	switch (getTransStatus())
	{
	case TransStatus::TRANS_UPDATE:
	case TransStatus::TRANS_STA_UNKNOWN:
		return false;
		break;
	default:
		break;
	};
	return true;
}

template<typename MACHINE>
_UINT32 StateTransitioner<MACHINE>::armForTransitions(TransRecipe a_currentOut, IState<MACHINE> * a_pNextState, TransRecipe a_nextIn)
{
	return 0;
}
*/

};
};