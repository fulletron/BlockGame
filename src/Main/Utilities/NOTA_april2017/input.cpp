#include "input.h"
#include <Graphics/window.h>

extern GS::Graphics::Window g_window;

namespace GS {
namespace Utilities {

Input::InputDeck Input::inputDeck;

_INT32 Input::init()
{
	//GLFWwindow * pGLFWwindow = g_window.getGLFWwindow();

	//glfwSetKeyCallback( pGLFWwindow, keyCB );
	//glfwSetCursorPosCallback( pGLFWwindow, mousePosCB );
	//glfwSetMouseButtonCallback( pGLFWwindow, mouseClickCB );
	//glfwSetScrollCallback( pGLFWwindow, scrollCB );

	return 0;
};
/*
void Input::mousePosCB( GLFWwindow * a_pGLFWwindow, double a_x, double a_y )
{
	inputDeck.m_x = a_x; 
	inputDeck.m_y = a_y;
}

void Input::keyCB( GLFWwindow * a_pGLFWwindow, int a_key, int a_scancode, int a_action, int a_mods )
{
	Press press(a_key, a_action, a_mods);
	inputDeck.m_presses.push_back(press);
}

void Input::mouseClickCB( GLFWwindow * a_pGLFWwindow, int a_button, int a_action, int a_mods )
{
	Press press(a_button, a_action, a_mods);
	inputDeck.m_presses.push_back(press);
}

void Input::scrollCB( GLFWwindow * a_pGLFWwindow, double a_xOffset, double a_yOffset )
{
	inputDeck.m_scrollX = a_xOffset; inputDeck.m_scrollY = a_yOffset;
}
*/

void Input::wipe()
{
	inputDeck.wipe();
}

};
};
