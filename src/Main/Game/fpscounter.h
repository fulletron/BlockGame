#ifndef __FPSCOUNTER_H_
#define __FPSCOUNTER_H_

#include <Utilities/typedefinitions.h>
#include <Graphics/panel.h>

namespace GS { 

namespace Graphics {
class FontResource;
class ShaderProgramResource;
class TextureResource;
class MeshResource;
};

namespace Game {

class FPSCounter : public GS::Graphics::IPaneAsset
{
selective:
	GS::Graphics::FontResource * m_pFont;
	GS::Graphics::ShaderProgramResource * m_pProg;

	_UINT32 m_count;
	_DOUBLE m_timer;
	_BOOL m_isDirty;
public:
	FPSCounter() : 
		m_count(0),
		m_timer(0.0),
		m_isDirty(true)
		{}
	/** 
	* Returns the current count
	*/
	_UINT32 getFPS() const { return m_count; }

	/**
	* Check the state of an object to see if it needs to be redrawn
	*/
	_BOOL isDirty() const;

	/**
	* Tells the PaneAsset to clean up
	*/ 
	void shutdown();

	/**
	* Draws the PaneAsset.
	*/
	void draw( GS::Graphics::IDimensionable * const a_dims );

	/**
	* Determines how to handle input for the PaneAsset
	*/
	_BOOL handleInput();

	/**
	* Updates the PaneAsset by dt.
	*/
	void update(const _DOUBLE a_dt);

	/**
	*
	*/
	_INT32 init ();

selective:
	void __clean();
};

/*
class FPSCounter //: public GS::Graphics::PaneObj
{
selective:
	_UINT32 m_count;
	_DOUBLE m_timer;
public:
	FPSCounter() : 
		//GS::Graphics::PaneObj(),
		m_count(0),
		m_timer(0.0)
		{}
	_UINT32 getFPS() const { return m_count; }
	void update( const _DOUBLE a_dt );

selective:
	void __clean();
};
*/

}
};

#endif
