#include "input.h"
#include <Graphics/window.h>

namespace GS {
namespace Utilities {

Input * Input::s_pInput = 0;
Input::InputDeck * Input::s_pInputDeck = 0;

_INT32 Input::init(GS::Graphics::Window * a_pWindow)
{
	GLFWwindow * pGLFWwindow = a_pWindow->getGLFWwindow();

	glfwSetKeyCallback( pGLFWwindow, keyCB );
	glfwSetCursorPosCallback( pGLFWwindow, mousePosCB );
	glfwSetMouseButtonCallback( pGLFWwindow, mouseClickCB );
	glfwSetScrollCallback( pGLFWwindow, scrollCB );

	s_pInput = this;
	s_pInputDeck = &inputDeck;

	s_pInputDeck->wipe();

	return 0;
};

};
};