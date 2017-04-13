#ifndef __IWINDOW_H_
#define __IWINDOW_H_

#include "..\openglincludes.h"
#include "..\idimensionable.h"

namespace GS {
namespace Graphics {

/**
* IWindow will give us the game window. The guts of it change based on GLFW/OTHER 
*/
class IWindow : public IDimensionable
{
public:
	virtual _UINT32 init() = 0;
	virtual _BOOL isOpen() = 0;
	virtual _UINT32 shutdown() = 0;
	virtual _VEC2D<_INT32> getPixelDimensions() const = 0;
};

};
};

#endif
