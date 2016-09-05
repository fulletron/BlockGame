#ifndef __FPSCOUNTER_H_
#define __FPSCOUNTER_H_

#include <Utilities/typedefinitions.h>
#include <Game/presentable.h>
//#include <Graphics/panel.h>

namespace GS { 
namespace Game {

class FPSCounter : public GS::Game::Presentable
{
selective:
	_UINT32 m_count;
	_DOUBLE m_timer;

public:
	FPSCounter() : 
		m_count(0),
		m_timer(0.0)
		//m_dirty(true)
		{}
	/** 
	* Returns the current count
	*/
	_UINT32 getFPS() const { return m_count; }

	/**
	* Tells the PaneAsset to clean up
	*/ 
	void shutdown();

	/**
	* Updates the PaneAsset by dt.
	*/
	void update(const _DOUBLE a_dt);

	_UNION8 getPresentationElement8(const _UINT32 & a_index);

	/**
	*
	*/
	_INT32 init ();

selective:
	void __clean();
};

}
};

#endif
