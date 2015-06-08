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

Window::~Window()
{
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
	/// TODO :: KYLE :: MISPLACED ::
	//m_projMat = glm::ortho(0,SCREEN_WIDTH,0,SCREEN_HEIGHT);

	glClearColor(0.0f,0.0f,0.0f,0.0f);

	if(!glfwInit())
		return 1;

	// SET STANDARD ERROR CALLBACK
	glfwSetErrorCallback(GS::Utilities::ErrorCallbacks::glfwErrorCallback);

	/// Set GLFW Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	/// SOIL USES DEPRECATED CALLS(IN CERTAIN FUNCTIONS). IT IS POSSIBLE YOU WILL NOT BE ABLE TO FORWARD COMPAT!
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	/// Set Multisample Rate
	glfwWindowHint(GLFW_SAMPLES, 8);

	if( __createOnlyWindow() )
		return 2;

	glfwSwapInterval(0);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	_CheckForErrors();

	return 0;
}

_UINT32 Window::shutdown()
{
	glfwDestroyWindow(m_pGLFWwindow);
	m_isOpen = false;
	glfwTerminate();

	return 0;
}

void Window::swapBuffers()
{
	glfwSwapBuffers(m_pGLFWwindow);
}

Vec2D<_INT32> Window::getPixDims()
{
	Vec2D<_INT32> dims; // KYLE :: THIS MIGHT GET PERMISSIVE ON
				// DIFF BIT MACHINE
	glfwGetWindowSize(m_pGLFWwindow, &dims.x, &dims.y);
	return dims;
}

bool Window::isOpen()
{
	if(glfwWindowShouldClose(m_pGLFWwindow)
	|| !m_isOpen )
		return false;

	return true;
}

GLFWwindow * Window::getGLFWwindow()
{
	return m_pGLFWwindow;
}

};
};