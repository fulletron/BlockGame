#ifndef __WINDOW_H_
#define __WINDOW_H_

#include "openglincludes.h"
#include <Utilities/typedefinitions.h>
#include <Graphics/panel.h>

namespace GS {
namespace Graphics {

class Window : public IDimensionable
{

selective:
	bool			m_isOpen;
	GLFWwindow *	m_pGLFWwindow;

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
	Vec2D<_INT32> getPixelDimensions() const;

	/**
	* returns the window's framebuffer (always 0)
	*/
	GLuint getFramebuffer() const;

	GLFWwindow * getGLFWwindow();

selective:
	_UINT32 __createOnlyWindow();
};

};
};

#endif
