#include "testpane.h"
#include <Graphics/reslib.h>

extern GS::Graphics::ResourceLibrary g_lib;

namespace GS {
namespace Game {

_INT32 TestPane::init( FPSCounter * const a_fpsCtr )
{
	initPaneBlues( 0, Vec4D<float>(0.0f,0.0f,1.0f,1.0f) );
	initFramebuffer();

	m_pTex = g_lib.findTextureResource( CV8::RES_TEX_PANEBKG );	
	m_pScreenProg = g_lib.findShaderProgramResource( CV8::RES_SP_FBDRAW );
	m_pProg = g_lib.findShaderProgramResource( CV8::RES_SP_FONTDRAW );
	m_pFont = g_lib.findFontResource( CV8::RES_FONT_KASHSCRIPT );
	m_pMesh = g_lib.findMeshResource( CV8::RES_MSH_RECT );
	m_pTexProg = g_lib.findShaderProgramResource( CV8::RES_SP_TEXRECTDRAW );
	m_pScreenMesh = g_lib.findMeshResource( CV8::RES_MSH_SCREEN );
	m_pFPS = a_fpsCtr;
	return 0;
}

_BOOL TestPane::isDirty()
{
	if( m_pFPS->getDirty() )
		return true;
	return false;
}

void TestPane::draw()
{
	if( isDirty() )
	{	
        	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.50f,0.20f,0.20f,1.0f);
        	//glEnable(GL_DEPTH_TEST);
		//glEnable(GL_STENCIL_TEST);
		//glDisable(GL_STENCIL_TEST);
		
		std::string fps = "FIRST!";
		fps= "FPS: " + boost::lexical_cast<std::string>( m_pFPS->getFPS() );

		glUseProgram( m_pProg->getProgram() );
		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, m_pFont->m_texture );
		glUniform1i( glGetUniformLocation( m_pProg->getProgram(), "tex" ), 0 );

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		for(int i = 0; i < 2000; ++i)
			m_pFont->renderText( "Test!", 
				GS::Graphics::Vector2_t( 0.0f, 500.0f - ((float)i/3.0f) ), 
				GS::Graphics::Color4f_t(0.0f, 1.0f, 1.0f, 1.0f) 
			);
		
		m_pFont->renderText( 
			fps, 
			GS::Graphics::Vector2_t(-800.00f, 500.00f), 
			GS::Graphics::Color4f_t(0.0f, 1.0f, 1.0f, 1.0f) 
		);
		//glDisable(GL_DEPTH_TEST);
	}


       	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// BIND ALL THE CRAP
	glBindVertexArray( m_pScreenMesh->getVAO() );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_pScreenMesh->getEBO() );
	glUseProgram( m_pTexProg->getProgram() );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, m_texColorBuffer );
	glUniform1i( glGetUniformLocation( m_pTexProg->getProgram(), "tex" ), 0 );
  	// THESE NEED TO BE SPECIFIED EVERYTIME
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
}

};
};
