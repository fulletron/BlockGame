#include "time_glfw.h"

namespace GS {
namespace Utilities {
	
#ifdef USING_GLFW
Time_GLFW::Time_GLFW()
{
	
}

Time_GLFW::~Time_GLFW()
{
	
}

_UINT32 Time_GLFW::init(void)
{
	m_latest_abs = 0;
	m_latest_dt = 0;
	updateInternalValues();
	return 0;
}

_UINT32 Time_GLFW::shutdown(void)
{
	m_latest_abs = 0;
	m_latest_dt = 0;
	return 0;
}

_DOUBLE Time_GLFW::getSecondsSinceBootup () const
{
	return m_latest_abs;
}

_DOUBLE Time_GLFW::getDeltaTime () const
{
	return m_latest_dt;
}

_DOUBLE Time_GLFW::checkDeltaTime() const
{
	return glfwGetTime() - m_latest_abs;
}

void Time_GLFW::updateInternalValues ()
{
	_DOUBLE newAbs = glfwGetTime();
	m_latest_dt = newAbs - m_latest_abs;
	m_latest_abs = newAbs;
}

#endif

};
};