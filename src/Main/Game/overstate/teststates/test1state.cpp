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
	return 0;
}

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

_UINT32 Test1State::onExit(OverState * a_sm)
{
	std::cout << "TEST1STATE EXIT " << std::endl;
	return 0;
}

};
};