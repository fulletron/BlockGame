#include "glfwerrorfunc.h"

namespace GS {
namespace Utilities {
namespace ErrorCallbacks {

void glfwErrorCallback(int a_int, const char * a_desc)
{
	g_latestErrorCode = a_int;
	g_pLatestErrorDesc = a_desc;
}

bool errorsExist()
{
	if (g_latestErrorCode != 0)
		return true;
	return false;
}

};
};
};
