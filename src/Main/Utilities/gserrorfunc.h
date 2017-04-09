#ifndef __GSERRORFUNC_H_
#define __GSERRORFUNC_H_

namespace GS {
namespace Utilities {

class ErrorCallbacks {
public:
	static int g_latestGLError;
	static int g_latestErrorCode;
	static const char * g_pLatestErrorDesc;

	//typedef void(*GLFWerrorfun)(int, const char *);
	//static void glfwErrorCallback(int, const char *);
	//static bool glfwErrorsExist();
	static bool glErrorsExist();
	static bool flaggedErrorsExist();

};
};
};

#define _CheckForErrors() GS::Utilities::ErrorCallbacks::flaggedErrorsExist()

#endif