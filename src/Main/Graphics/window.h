#ifndef __WINDOW_H_
#define __WINDOW_H_

#include "openglincludes.h"
#include <Utilities/typedefinitions.h>

namespace GS {
namespace Graphics {

class Window
{
#ifdef TEST_ENABLED
public:
#else
private:
#endif
	bool m_isOpen;

public:
	Window();
	_UINT32 init();
	bool isOpen() {return m_isOpen;};
};

};
};

#endif