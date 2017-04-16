#include "window_glfw.h"
#include "Utilities\definitions_values.h"
#include "Utilities\gserrorfunc.h"

namespace GS {
namespace Graphics {

#ifdef USING_GLFW

Window_GLFW::Window_GLFW()
{
	m_pGLFWwindow = 0;
}

Window_GLFW::~Window_GLFW()
{
}

_UINT32 Window_GLFW::__createOnlyWindow()
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
	_CheckForErrors();

	/// All systems go
	m_isOpen = true;
	return 0;
}

_UINT32 Window_GLFW::init()
{
	/// TODO :: KYLE :: MISPLACED ::
	//m_projMat = glm::ortho(0,SCREEN_WIDTH,0,SCREEN_HEIGHT);
	if(!glfwInit())
		return 1;


	/// Set GLFW Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/// SOIL USES DEPRECATED CALLS(IN CERTAIN FUNCTIONS). IT IS POSSIBLE YOU WILL NOT BE ABLE TO FORWARD COMPAT!
	// KYLE :: TODO :: 4/2017 DOESNT MAKE SENSE TO ME WHY SOIL WOULD AFFECT OPENGL, BUT WHATEVS
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// KYLE :: TODO :: Remove this. 
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	/// Set Multisample Rate
	glfwWindowHint(GLFW_SAMPLES, 8);

	if( __createOnlyWindow() )
		return 2;

	_CheckForErrors();

	glfwSwapInterval(0);

	_CheckForErrors();
	// Initialize GLEW
	glewExperimental = GL_TRUE;

	_CheckForErrors();

	glewInit();
	// THIS ALWAYS FAILS WITH 1282, 1280
	_CheckForErrors();

	// SET WINDOW RESIZE CALLBACK
	//glfwSetWindowSizeCallback(m_pGLFWwindow, windowResizeCallback);

	_CheckForErrors();

	// SET STANDARD ERROR CALLBACK
	//glfwSetErrorCallback(GS::Utilities::ErrorCallbacks::glfwErrorCallback);

	_CheckForErrors();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	_CheckForErrors();

	return 0;
}

_UINT32 Window_GLFW::shutdown()
{
	glfwSetWindowShouldClose(m_pGLFWwindow, 1); // 1 == GLFW_TRUE

	glfwDestroyWindow(m_pGLFWwindow);
	m_isOpen = false;
	glfwTerminate();

	return 0;
}

/**
* draws the screen
*/
void Window_GLFW::swapBuffers()
{
	glfwSwapBuffers(m_pGLFWwindow);
}

_VEC2D<_INT32> Window_GLFW::getPixelDimensions() const
{
	_VEC2D<_INT32> dims; // KYLE :: THIS MIGHT GET PERMISSIVE ON
				// DIFF BIT MACHINE
	glfwGetWindowSize(m_pGLFWwindow, &dims.x, &dims.y);
	return dims;
}

bool Window_GLFW::isOpen()
{
	if(glfwWindowShouldClose(m_pGLFWwindow)
	|| !m_isOpen )
		return false;

	return true;
}

#endif

/**
* This is specifically useful for getting a handle to the GLFW input
*/
GLFWwindow * Window::getGLFWwindow()
{
	return m_pGLFWwindow;
}


/*
void (*GLFWwindowsizefun)(GLFWwindow*, int, int);

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
	//1.77f == 16:9
	//1.6f == 16:10
	//1.5f == 3:2
	//1.33f == 4:3
	// Returns monitor that is currently fullscreening the window- this is 0 if windowed mode
	if (glfwGetWindowMonitor(window))
		return;

	float imperfect_aspect_ratio = (float)width / (float)height;

	if (imperfect_aspect_ratio > 1.69f )
		glfwSetWindowSize( window, height * 1.77, height ); 
	else if (imperfect_aspect_ratio > 1.55f )
		glfwSetWindowSize( window, height * 1.6f, height );
	else if (imperfect_aspect_ratio > 1.41f )
		glfwSetWindowSize( window, height * 1.5f, height );
	else
		glfwSetWindowSize( window, height * 1.33f, height );
}
*/

//GLuint Window::getFramebuffer() const
//{
//	return 0;
//}


};
};
