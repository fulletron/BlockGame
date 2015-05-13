#ifndef __TESTPANE_H_
#define __TESTPANE_H_

#include <Graphics/panel.h>
#include "fpscounter.h"

namespace GS {

namespace Graphics {
class FontResource;
class ShaderProgramResource;
class TextureResource;
class MeshResource;
};

namespace Game {

class TestPane : public GS::Graphics::Pane
{
selective:
	GS::Graphics::TextureResource * m_pTex;
	GS::Graphics::FontResource * m_pFont;
	GS::Graphics::ShaderProgramResource * m_pProg;
	GS::Graphics::ShaderProgramResource * m_pScreenProg;
	GS::Graphics::ShaderProgramResource * m_pTexProg;
	GS::Graphics::MeshResource * m_pMesh;
	GS::Graphics::MeshResource * m_pScreenMesh;
	FPSCounter * m_pFPS;
public:
	TestPane():	Pane(), 
			m_pTex(0),
			m_pFont(0), 
			m_pProg(0), 
			m_pScreenProg(0), 
			m_pTexProg(0),
			m_pMesh(0),
			m_pScreenMesh(0),
			m_pFPS(0) 
			{}	
	_INT32 init( FPSCounter * a_fpsCtr );
	
	_BOOL isDirty();
	void draw();	
	_BOOL handleInput(){return false;}
};

};
};

#endif
