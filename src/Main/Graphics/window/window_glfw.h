#ifndef __WINDOW_GLFW_H_
#define __WINDOW_GLFW_H_

#include "iwindow.h"
#include "../idimensionable.h"

namespace GS {
namespace Graphics {

#ifdef USING_GLFW
class Window_GLFW : public IWindow
{
privatized:
	GLFWwindow *	m_pGLFWwindow;

selective:
	bool			m_isOpen;

public:
	Window_GLFW();
	~Window_GLFW();

	_UINT32 init();
	bool isOpen();
	_UINT32 shutdown();
	void swapBuffers();

	/**
	* Get the Pixel Dimensions of the current master window
	*/
	Vec2D<_INT32> getPixelDimensions() const;

	/**
	* returns the window's framebuffer (always 0)
	*/
//	GLuint getFramebuffer() const;

//	GLFWwindow * getGLFWwindow();

selective:
	_UINT32 __createOnlyWindow();
};
#endif

};
};

#endif
