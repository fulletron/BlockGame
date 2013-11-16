#include "window.h"
#include "Utilities/utilities.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

namespace GS {
namespace Graphics {

Window::Window()
{
	m_pGLFWwindow = 0;
}

_UINT32 Window::__createOnlyWindow()
{
	/// TODO :: add loading of a pref, add fullscreen using glfwGetPrimaryMonitor();
	/// Create the Window
	m_pGLFWwindow = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "KYLE :: BlockGame", 0, 0 );
	if(!m_pGLFWwindow)
	{
		glfwTerminate();
		return 101;
	}

	/// Make the window the opengl context
	glfwMakeContextCurrent(m_pGLFWwindow);

	/// All systems go
	m_isOpen = true;
	return 0;
}

_UINT32 Window::init()
{
	GLenum error = glGetError();

	glClearColor(0.0f,0.0f,0.0f,0.0f);

	if(!glfwInit())
		return 1;

	/// Set GLFW Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	/// SOIL USES DEPRECATED CALLS(IN CERTAIN FUNCTIONS). IT IS POSSIBLE YOU WILL NOT BE ABLE TO FORWARD COMPAT!
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	/// Set Multisample Rate
	glfwWindowHint(GLFW_SAMPLES, 8);

	if(__createOnlyWindow())
		return 2;

	//glfwSetWindowSizeCallback( _windowResizeFunction ); /// TODO ::
	glfwSwapInterval(0);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	//GSU::checkForGLErrors(); /// TODO ::
	error = glGetError();
	return 0;
}

_UINT32 Window::shutdown()
{
	glfwDestroyWindow(m_pGLFWwindow);
	m_isOpen = false;
	glfwTerminate();

	return 0;
}

bool Window::isOpen()
{
	if(glfwWindowShouldClose(m_pGLFWwindow)
	|| !m_isOpen )
		return false;

	return true;
}

};
};