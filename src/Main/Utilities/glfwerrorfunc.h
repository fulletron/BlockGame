#ifndef __GLFWERRORFUNC_H_
#define __GLFWERRORFUNC_H_

namespace GS {
namespace Utilities {
namespace ErrorCallbacks {

static int g_latestErrorCode = 0;
static const char * g_pLatestErrorDesc = 0;

typedef void(*GLFWerrorfun)(int, const char *);
void glfwErrorCallback(int, const char *);
bool errorsExist();

};
};
};

#endif