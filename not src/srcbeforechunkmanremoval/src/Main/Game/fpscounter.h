#ifndef __FPSCOUNTER_H_
#define __FPSCOUNTER_H_

#include <Utilities/typedefinitions.h>
#include <Utilities/gsvector.h>
#include <Graphics/panel.h>

namespace GS { 
namespace Game {

class FPSCounter : public GS::Graphics::PaneObj
{
selective:
	_UINT32 m_count;
	_DOUBLE m_timer;
public:
	FPSCounter() : 
		GS::Graphics::PaneObj(),
		m_count(0),
		m_timer(0.0)
		{}

	_UINT32 getFPS() const { return m_count; }
	void update( const _DOUBLE a_dt );

selective:
	void __clean();
};

}
};

#endif
