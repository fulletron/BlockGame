#include "fpscounter.h"
#include <Graphics/reslib.h>

extern GS::Graphics::ResourceLibrary g_lib;

namespace GS { 
namespace Game {

_INT32 FPSCounter::init()
{
	setDirty(true);
	return 0;
}

/**
* Tells the PaneAsset to clean up
*/ 
void FPSCounter::shutdown()
{
}

/**
*
*/
_UNION8 FPSCounter::getPresentationElement8(const _UINT32 & a_index) 
{ 
	_UNION8 returnable; 
	switch(a_index)
	{
	case 0: returnable.asInt32 = m_count; break;
	case 1: returnable.asDouble = m_timer; break;
	default: returnable.asInt32 = 0; break;
	}

	return returnable;  
}

/**
* Updates the object by dt.
*/
void FPSCounter::update( const _DOUBLE a_dt )
{
	if( isDirty() ) 
		__clean();

	m_timer += a_dt;
	m_count++;

	if( m_timer > 1.0 )
		setDirty(true);
}

void FPSCounter::__clean()
{
	setDirty(false);
	m_count = 0;
	m_timer = 0.0;
}

};
};
