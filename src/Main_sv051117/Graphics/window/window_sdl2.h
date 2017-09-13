#ifndef __WINDOW_SDL2_H_
#define __WINDOW_SDL2_H_

#include "iwindow.h"

namespace GS {
namespace Graphics {

#ifdef USING_SDL
class Window_SDL2 : public IDimensionable
{

selective:
	bool			m_isOpen;
	//GLFWwindow *	m_pGLFWwindow;

public:
	Window();
	~Window();

	_UINT32 init();
	bool isOpen();
	_UINT32 shutdown();
	void swapBuffers();

	/**
	* Get the Pixel Dimensions of the current master window
	*/
	_VEC2D<_INT32> getPixelDimensions() const;

	/**
	* returns the window's framebuffer (always 0)
	*/
	//	GLuint getFramebuffer() const;

	//	GLFWwindow * getGLFWwindow();
};

typedef Window_SDL Window;

#endif

};
};

#endif
