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
	bool			m_isOpen;
	GLFWwindow *	m_pGLFWwindow;

public:
	Window();
	~Window();

	_UINT32 init();
	bool isOpen();
	_UINT32 shutdown();
	void swapBuffers();
	GLFWwindow * getGLFWwindow();

	/// TODO :: KYLE :: MISPLACED ::
	//glm::mat4x4 m_projMat;
	
private:
	_UINT32 __createOnlyWindow();
};

};
};

#endif
