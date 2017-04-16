#include "input_GLFW.h"
#include "Graphics/window/window.h"

extern GS::Graphics::Window * g_pWindow;

namespace GS {
namespace Utilities {

#ifdef USING_GLFW

// GLFW_KEY_W 87
// GLFW_KEY_ESCAPE 256

//	GLFW_KEY_1   49

//	GLFW_KEY_2   50

Input_GLFW::Input_GLFW()
{
}

Input_GLFW::~Input_GLFW()
{
}

_UINT32 Input_GLFW::init(void)
{
	m_pGLFWwindow = g_pWindow->getGLFWwindow();

	// Whenever you poll state, you risk missing the state change you are 
	// looking for. If a pressed key is released again before you poll its 
	// state, you will have missed the key press. The recommended solution 
	// for this is to use a key callback, but there is also the 
	// GLFW_STICKY_KEYS input mode.
	glfwSetInputMode(m_pGLFWwindow, GLFW_STICKY_KEYS, 1);

	m_pressed.clear();
	m_held.clear();
	m_released.clear();
	m_subscribedKeys.clear();


	m_subscribedKeys.push_back(GLFW_KEY_SPACE); // 32
	m_subscribedKeys.push_back(GLFW_KEY_1); // 49
	m_subscribedKeys.push_back(GLFW_KEY_2); // 50
	m_subscribedKeys.push_back(GLFW_KEY_W); // 87
	m_subscribedKeys.push_back(GLFW_KEY_ESCAPE); // 256

	return 0;
}

_UINT32 Input_GLFW::shutdown(void)
{
	return 0;
}

_UINT32 Input_GLFW::intake(void)
{
	glfwPollEvents();

	// We know that anything that WAS flagged released has finished being flagged released.
	m_released.clear();

	// We add presses to both pressed and held at the same time.
	m_pressed.clear();

	// Next we need to push input from the held list to the released list if its current button state is
	// release.
	for (_VECTOR<_UINT32>::iterator iter = m_held.begin(); iter < m_held.end();)
	{
		if (!__checkHeldToReleased(&iter))
			iter++;
	}

	// next we need to decide if we are going to add a key press
	for (_VECTOR<_UINT32>::iterator iter = m_subscribedKeys.begin(); iter < m_subscribedKeys.end(); iter++)
	{
		__checkAlreadyPressed(&iter);
	}

	return 0;
}

_BOOL Input_GLFW::isPressed(const _UINT32 & a_key) const
{
	for (_VECTOR<_UINT32>::const_iterator iter = m_pressed.begin(); iter < m_pressed.end(); iter++)
	{
		if (*iter == a_key)
			return true;
	}
	return false;
}

_BOOL Input_GLFW::isHeld(const _UINT32 & a_key) const
{
	for (_VECTOR<_UINT32>::const_iterator iter = m_held.begin(); iter < m_held.end(); iter++)
	{
		if (*iter == a_key)
			return true;
	}
	return false;
}

_BOOL Input_GLFW::isReleased(const _UINT32 & a_key) const
{
	for (_VECTOR<_UINT32>::const_iterator iter = m_released.begin(); iter < m_released.end(); iter++)
	{
		if (*iter == a_key)
			return true;
	}
	return false;
}

_VEC2D<_DOUBLE> Input_GLFW::mouseMovement(const _UINT32 &) const
{
	return _VEC2D<_DOUBLE>(0.0, 0.0);
}

_VEC2D<_DOUBLE> Input_GLFW::analogMovement(const _UINT32 &) const
{
	return _VEC2D<_DOUBLE>(0.0, 0.0);
}

/**
* This traverses through the m_held list to see if
* a_key is currently marked as HELD. If it isnt Held yet,
* it adds the key to both the pressed and held lists.
*/
_BOOL Input_GLFW::__checkAlreadyPressed(_VECTOR<_UINT32>::iterator * iter)
{
	_UINT32 key = *(*iter);
	// Get the state of the key in question
	int state = glfwGetKey(m_pGLFWwindow, key);

	// if the state of the subbed key is PRESSED, then we need to do stuff
	if (state == GLFW_PRESS)
	{
		// IF IT IS NOT HELD
		if (!isHeld(key))
		{
			m_pressed.push_back(key);
			m_held.push_back(key);
			return false;
		}
		return true;
	}
	return false;
}

/**
* Checks an iteration of the m_held vector to see if that input is still held.
* Call this after clearing m_released, and before dumping to pressed or held.
*/
_BOOL Input_GLFW::__checkHeldToReleased(_VECTOR<_UINT32>::iterator * iter)
{
	_UINT32 key = *(*iter);
	// Get the state of the key in question
	int state = glfwGetKey(m_pGLFWwindow, key);

	// if the (previously held) key is RELEASED, then we need to do stuff
	if (state == GLFW_RELEASE)
	{
		(*iter) = m_held.erase((*iter));
		m_released.push_back(key);
		return true;
	}

	return false;
}

#endif
}
}
