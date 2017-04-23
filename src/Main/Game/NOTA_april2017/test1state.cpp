#include "test1state.h"

// Target state
#include "test2state.h"

#include <iostream>

#include "Utilities/input/iinput.h"
extern GS::Utilities::IInput * g_pInput;

namespace GS {
namespace State {

_UINT32 Test1State::onEnter(OverState * a_sm)
{
	std::cout << "TEST1STATE ENTER " << std::endl;
	initTransitionable();
	return 0;
}

/*
_UINT32 Test1State::onUpdate(OverState * a_sm)
{
	if (g_pInput->isPressed(50))
	{
		a_sm->changeState(new Test2State());
		std::cout << "Just killed this test1state" << std::endl;
	}
	else if (g_pInput->isReleased(87))
	{
		std::cout << " W IS RELEASED " << std::endl;
	}
	return 0;
}
*/

_UINT32 Test1State::initTransitionable()
{
	setTransitionStatus(TransStatus::TRANS_IN);
	return 0;
}

_UINT32 Test1State::shutdownTransitionable()
{
	setTransitionStatus(TransStatus::TRANS_UNKNOWN);
	m_pNextState = 0;
	return 0;
}


_UINT32 Test1State::onTransitionIn(OverState *a_sm)
{
	std::cout << "TEST1STATE::transitioning in..." << std::endl;
	setTransitionStatus(TransStatus::TRANS_UPDATE);
	return 0;
}

_UINT32 Test1State::onTransitionOut(OverState * a_sm)
{
	std::cout << "TEST1STATE::transitioning out..." << std::endl;
	a_sm->changeState(getNextState());
	return 0;
}

_UINT32 Test1State::onActualUpdate(OverState * a_sm)
{
	if (g_pInput->isPressed(50))
	{
		setNextState(new Test2State());
		setTransitionStatus(TransStatus::TRANS_OUT);
		std::cout << "made new Test2State()" << std::endl;
	}
	else if (g_pInput->isReleased(87))
	{
		std::cout << " W IS RELEASED " << std::endl;
	}
	return 0;
}

_UINT32 Test1State::onExit(OverState * a_sm)
{
	std::cout << "TEST1STATE EXIT " << std::endl;
	shutdownTransitionable();
	return 0;
}

};
};