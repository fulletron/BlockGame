#ifndef __GLFWERRORFUNC_H_
#define __GLFWERRORFUNC_H_

namespace GS {
namespace Utilities {

class ErrorCallbacks {

	/*
	static int g_latestGLError = 0;
	static int g_latestErrorCode = 0;
	static const char * g_pLatestErrorDesc = 0;

	typedef void(*GLFWerrorfun)(int, const char *);
	static void glfwErrorCallback(int, const char *);
	static bool errorsExist();
	static bool glErrorExist();
	*/


public:
	static int g_latestGLError;
	static int g_latestErrorCode;
	static const char * g_pLatestErrorDesc;

	typedef void(*GLFWerrorfun)(int, const char *);
	static void glfwErrorCallback(int, const char *);
	static bool glfwErrorsExist();
	static bool glErrorsExist();
	static bool flaggedErrorsExist();

};
};
};

#define _CheckForErrors() GS::Utilities::ErrorCallbacks::flaggedErrorsExist()

#endif