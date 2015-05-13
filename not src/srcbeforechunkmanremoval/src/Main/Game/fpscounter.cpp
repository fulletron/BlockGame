#include "fpscounter.h"

namespace GS { 
namespace Game {

void FPSCounter::update( const _DOUBLE a_dt )
{
	if( m_isDirty ) 
		__clean();

	m_timer += a_dt;
	m_count++;

	if( m_timer > 1.0 )
		m_isDirty = true;
}

void FPSCounter::__clean()
{
	m_isDirty = false;
	m_count = 0;
	m_timer = 0.0;
}

};
};
