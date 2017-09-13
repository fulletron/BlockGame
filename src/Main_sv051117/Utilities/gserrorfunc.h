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
	static int glErrorsExist();
	static bool flaggedErrorsExist();
	static bool specificErrorExists(int x);
	static bool checkForNoErrorOrSpecificError(int x);
};
};
};

// WHEN TEST IS ENABLED, ONLY ALLOW FOR ERROR CHECKING FROM GTEST
#ifdef TEST_ENABLED
#define _CheckForErrors() ;
#define _CheckForError(x) ;
#define _CheckForNoErrorOrSpecificError(x) ;

#define G_CheckForErrors() GS::Utilities::ErrorCallbacks::flaggedErrorsExist()
#define G_CheckForError(x) GS::Utilities::ErrorCallbacks::specificErrorExists(x)
#define G_CheckForNoErrorOrSpecificError(x) GS::Utilities::ErrorCallbacks::checkForNoErrorOrSpecificError(x)

#else
#define _CheckForErrors() GS::Utilities::ErrorCallbacks::flaggedErrorsExist()
#define _CheckForError(x) GS::Utilities::ErrorCallbacks::specificErrorExists(x)
#define _CheckForNoErrorOrSpecificError(x) GS::Utilities::ErrorCallbacks::checkForNoErrorOrSpecificError(x)
#endif

#endif