#include "fpscounter.h"
#include <Graphics/reslib.h>

extern GS::Graphics::ResourceLibrary g_lib;

namespace GS { 
namespace Game {

_INT32 FPSCounter::init()
{
	m_pProg = g_lib.findShaderProgramResource( CV8::RES_SP_FONTDRAW );
	m_pFont = g_lib.findFontResource( CV8::RES_FONT_KASHSCRIPT );

	return 0;
}

/**
* Check the state of an object to see if it needs to be redrawn
*/
_BOOL FPSCounter::isDirty() const
{
	return m_isDirty;
}

/**
* Tells the PaneAsset to clean up
*/ 
void FPSCounter::shutdown()
{
	g_lib.forgetResource(m_pFont->getType(), m_pFont->getName());
	g_lib.forgetResource(m_pProg->getType(), m_pProg->getName());
}

/**
* Draws the PaneAsset.
*/
void FPSCounter::draw( GS::Graphics::IDimensionable * const a_dims )
{
	std::string fps = "FIRST!";
	fps= "FPS: " + boost::lexical_cast<std::string>( getFPS() );

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

	Vec2D<_INT32> dims = a_dims->getPixelDimensions();
	m_pFont->renderText(
		fps, 
		//GS::Graphics::Vector2_t( SC(_FLOAT, -dims.x), SC(_FLOAT, (dims.y-m_pFont->getHeight() ) ) ), 
		GS::Graphics::Vector2_t( -400.0f, 600.0f-m_pFont->getHeight() ), 
		GS::Graphics::Color4f_t(0.0f, 1.0f, 1.0f, 1.0f) 
	);
}

/**
* Determines how to handle input for the PaneAsset
*/
_BOOL FPSCounter::handleInput()
{
	return false;
}

/**
* Updates the PaneAsset by dt.
*/
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
