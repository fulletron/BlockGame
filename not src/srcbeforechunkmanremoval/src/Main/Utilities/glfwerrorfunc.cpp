#include "glfwerrorfunc.h"
#include <Graphics/openglincludes.h>

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
	if ( g_latestErrorCode != 0 )
		return true;

	return false;
}

bool ErrorCallbacks::glErrorsExist()
{
	g_latestGLError = glGetError();
	if ( g_latestGLError != GL_NO_ERROR )
		return true;

	return false;
}

bool ErrorCallbacks::flaggedErrorsExist()
{
	if ( glErrorsExist() || glfwErrorsExist() )
		return true;

	return false;
}

};
};
