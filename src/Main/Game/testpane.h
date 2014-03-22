#ifndef __TESTPANE_H_
#define __TESTPANE_H_

#include <Graphics/panel.h>
#include "fpscounter.h"

namespace GS {

namespace Graphics {
class FontResource;
class ShaderProgramResource;
};

namespace Game {

class TestPane : public GS::Graphics::Pane
{
selective:
	GS::Graphics::FontResource * m_pFont;
	GS::Graphics::ShaderProgramResource * m_pProg;
	FPSCounter * m_pFPS;
public:
	TestPane():Pane(), m_pFont(0), m_pProg(0), m_pFPS(0) {}	
	_INT32 init( FPSCounter * a_fpsCtr );
	
	_BOOL isDirty();
	void draw();	
	_BOOL handleInput(){return false;}
};

};
};

#endif
