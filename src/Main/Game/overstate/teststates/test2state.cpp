#include "test2state.h"

// Target state
#include "test1state.h"

#include <iostream>

#include "Utilities/input/iinput.h"
extern GS::Utilities::IInput * g_pInput;

namespace GS {
namespace State {

_UINT32 Test2State::onEnter(OverState * a_sm)
{
	std::cout << "TEST2STATE ENTER " << std::endl;
	return 0;
}

_UINT32 Test2State::onUpdate(OverState * a_sm)
{
	if (g_pInput->isPressed(49))
	{
		a_sm->changeState(new Test1State());
		std::cout << "Just killed this test2state" << std::endl;
	}
	return 0;
}

_UINT32 Test2State::onExit(OverState * a_sm)
{
	std::cout << "TEST2STATE EXIT " << std::endl;
	return 0;
}

};
};