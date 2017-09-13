#ifndef __TIME_GLFW_H_
#define __TIME_GLFW_H_

#include "../definitions_types.h"
#include "itime.h"
#include "../../Graphics/openglincludes.h"

namespace GS {
namespace Utilities {
	
#ifdef USING_GLFW
class Time_GLFW : public ITime
{
public:
	Time_GLFW();
	~Time_GLFW();

	virtual _UINT32 init(void);
	virtual _UINT32 shutdown(void);

	virtual _DOUBLE getSecondsSinceBootup () const;
	virtual _DOUBLE getDeltaTime () const;
	virtual _DOUBLE checkDeltaTime() const;
	virtual void updateInternalValues ();
	
selective:
	_DOUBLE m_latest_abs;
	_DOUBLE m_latest_dt;
};

typedef Time_GLFW Time;
#endif

};
};

#endif