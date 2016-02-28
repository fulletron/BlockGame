#include "glfwerrorfunc.h"
#include <Graphics/openglincludes.h>

#ifdef WIN32
#include <iostream>
#endif

namespace GS {
namespace Utilities {

int ErrorCallbacks::g_latestGLError = 0;
int ErrorCallbacks::g_latestErrorCode = 0;
const char * ErrorCallbacks::g_pLatestErrorDesc = 0;

void ErrorCallbacks::glfwErrorCallback(int a_int, const char * a_desc)
{
	g_latestErrorCode = a_int;
	g_pLatestErrorDesc = a_desc;
}

bool ErrorCallbacks::glfwErrorsExist()
{
	if (g_latestErrorCode != 0)
	{
#ifdef WIN32
		std::cout << "GLFW ERROR CODE " << g_latestErrorCode << std::endl;
#endif
		return true;
	}

	return false;
}

bool ErrorCallbacks::glErrorsExist()
{
	g_latestGLError = glGetError();
	if (g_latestGLError != GL_NO_ERROR)
	{
#ifdef WIN32
		std::cout << "GL ERROR CODE " << g_latestGLError << std::endl;
#endif
		return true;
	}

	return false;
}

bool ErrorCallbacks::flaggedErrorsExist()
{
	bool returnable = false;
	if (glErrorsExist())
		returnable = true;
	if (glfwErrorsExist())
		returnable = true;

	return returnable;
}

};
};
