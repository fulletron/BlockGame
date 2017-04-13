#ifndef __INPUT_GLFW_H_
#define __INPUT_GLFW_H_

#include "iinput.h"
#include "../../Graphics/openglincludes.h"

namespace GS {
namespace Utilities {

#ifdef USING_GLFW
class Input_GLFW : public IInput
{
public:
	virtual _UINT32 init(void);
	virtual _UINT32 shutdown(void);
	virtual _UINT32 intake(void);
	//virtual _UINT32 clear(void);
	virtual _BOOL isPressed(const _UINT32 &) const;
	virtual _BOOL isHeld(const _UINT32 &) const;
	virtual _BOOL isReleased(const _UINT32 &) const;
	virtual _VEC2D<_DOUBLE> mouseMovement(const _UINT32 &) const;
	virtual _VEC2D<_DOUBLE> analogMovement(const _UINT32 &) const;

selective:
	_VEC2D<_DOUBLE> m_mouseMove;
	_VEC2D<_DOUBLE> m_mouseScroll;
	_VEC2D<_DOUBLE> m_analogLeft;
	_VEC2D<_DOUBLE> m_analogRight;
	_VECTOR<_UINT32> m_pressed;
	_VECTOR<_UINT32> m_held;
	_VECTOR<_UINT32> m_released;
};

typedef Input_GLFW Input;
#endif
}
}

#endif