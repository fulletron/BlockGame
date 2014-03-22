#include "testpane.h"
#include <Graphics/reslib.h>

extern GS::Graphics::ResourceLibrary g_lib;

namespace GS {
namespace Game {

_INT32 TestPane::init( FPSCounter * const a_fpsCtr )
{
	m_pProg = g_lib.findShaderProgramResource( CV8::RES_SP_FONTDRAW );
	m_pFont = g_lib.findFontResource( CV8::RES_FONT_KASHSCRIPT );
	m_pFPS = a_fpsCtr;
	return 0;
}

_BOOL TestPane::isDirty()
{
	// KYLE :: TODO:: 
	// THIS FUNCTION CALLS ALL OF getDirty() functions of all the pane objects.
	return false;
}

void TestPane::draw()
{
	// KYLE :: DO MAGIC
	glUseProgram( m_pProg->getProgram() );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, m_pFont->m_texture );
	glUniform1i( glGetUniformLocation( m_pProg->getProgram(), "tex" ), 0 );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	m_pFont->renderText( "test", GS::Graphics::Vector2_t(-800.00f, 500.00f), GS::Graphics::Color4f_t(0.0f, 1.0f, 1.0f, 1.0f) );

	//std::string test = "FPS: " + boost::lexical_cast<std::string>(1/dt);
}

};
};
