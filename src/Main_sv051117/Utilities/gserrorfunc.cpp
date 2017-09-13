#include "gserrorfunc.h"
#include <Graphics/openglincludes.h>

#ifdef WIN32
#include <iostream>
#endif

namespace GS {
namespace Utilities {

int ErrorCallbacks::g_latestGLError = 0;
int ErrorCallbacks::g_latestErrorCode = 0;
const char * ErrorCallbacks::g_pLatestErrorDesc = 0;
/*
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
*/

int ErrorCallbacks::glErrorsExist()
{
	g_latestGLError = glGetError();
	if (g_latestGLError)
	{
#ifdef WIN32
		std::cout << "GL ERROR CODE " << g_latestGLError << std::endl;
#endif
		return g_latestGLError;
	}
	return GL_NO_ERROR;
}

bool ErrorCallbacks::flaggedErrorsExist()
{
	bool returnable = false;
	if (glErrorsExist())
		returnable = true;
	//if (glfwErrorsExist())
	//	returnable = true;

	return returnable;
}

bool ErrorCallbacks::specificErrorExists(int x)
{
	if (x == glErrorsExist())
		return true;
	//if (glfwErrorsExist())
	//	returnable = true;

	return false;
}

bool ErrorCallbacks::checkForNoErrorOrSpecificError(int x)
{
	int error_code = glErrorsExist();
	if (error_code == 0
		|| error_code == x)
		return true;
	else
		return false;
}

};
};
