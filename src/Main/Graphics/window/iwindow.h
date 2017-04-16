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
	/**
	* Creates the window.
	*/
	virtual _UINT32 init() = 0;

	/**
	* Checks if the window is currently open.
	*/
	virtual _BOOL isOpen() = 0;

	/**
	* Destroys the window and cleans up.
	*/
	virtual _UINT32 shutdown() = 0;

	/**
	* Grabs the dimensions of the window in pixels.
	*/
	virtual _VEC2D<_INT32> getPixelDimensions() const = 0;

	/**
	* Presents the current window
	*/
	virtual void swapBuffers() = 0;
};

};
};

#endif
