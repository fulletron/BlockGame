#include "window.h"

namespace GS {
namespace Graphics {

Window::Window()
{
}

_UINT32 Window::init()
{
	glewInit();
	/*
	if(!glfwInit())
		exit( EXIT_FAILURE );

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	/// SOIL USES DEPRECATED CALLS(IN CERTAIN FUNCTIONS). IT IS POSSIBLE YOU WILL NOT BE ABLE TO FORWARD COMPAT!
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 8);
	*/

	return 0;
}

};
};