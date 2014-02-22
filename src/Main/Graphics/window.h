#ifndef __WINDOW_H_
#define __WINDOW_H_

#include "openglincludes.h"
#include <Utilities/typedefinitions.h>

namespace GS {
namespace Graphics {

class Window
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
	Vec2D<_INT32> getPixDims();
	GLFWwindow * getGLFWwindow();

	/// TODO :: KYLE :: MISPLACED ::
	//glm::mat4x4 m_projMat;
	
selective:
	_UINT32 __createOnlyWindow();
};

};
};

#endif
