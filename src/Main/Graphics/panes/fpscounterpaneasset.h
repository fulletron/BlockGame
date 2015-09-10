#ifndef __FPSCOUNTERPANEASSET_H_
#define __FPSCOUNTERPANEASSET_H_

#include <Graphics/panel.h>

namespace GS {
namespace Game {
class IPresentable;
};

namespace Graphics {


class FPSCounterPaneAsset : public GS::Graphics::IPaneAsset
{
selective:
	GS::Graphics::FontResource * m_pFpsFont;
	GS::Graphics::ShaderProgramResource * m_pFontDrawingProg;

	GS::Game::IPresentable * m_pFPSCounterPresentable;

	GS::Graphics::IPane * m_pParentPane;
	_BOOL m_isDirty;
public:
	FPSCounterPaneAsset():
		    m_pFpsFont(0),
			m_pFontDrawingProg(0),
			m_pFPSCounterPresentable(0),
			m_pParentPane(0),
			m_isDirty(true)
			{}

	/**
	* init the paneasset resources
	*/
	_INT32 init( Pane * const a_pParent );

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
	_BOOL handleInput(){return false;}

	/**
	* Updates the PaneAsset by dt.
	*/
	void update(const _DOUBLE a_dt);
};

};
};

#endif
