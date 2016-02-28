#include <Graphics/reslib.h>

#include <Graphics/Panes/DebugPane/fpscounterpasset.h>
#include <Game/brain.h> // TODO :: REMOVE! ONCE SINGLETON IS NO LONGER USED

extern GS::Graphics::ResourceLibrary g_lib;

namespace GS {
namespace Graphics {

/**
* init the paneasset resources
*/
_INT32 FPSCounterPasset::init( Pane * const a_pParent )
{
	m_pParentPane = a_pParent;

	// RELEVANT TO FPS COUNTER ASSET
	m_pFontDrawingProg = g_lib.findShaderProgramResource( CV8::RES_SP_FONTDRAW );
	m_pFpsFont = g_lib.findFontResource( CV8::RES_FONT_KASHSCRIPT_16 );

	GS::Game::Brain * pBrain = &GS::Game::Brain::getInstance();
	m_pFPSCounterPresentable = pBrain->getFpsCounter();

	return 0;
}


_BOOL FPSCounterPasset::isDirty() const
{
	if (m_pFPSCounterPresentable->isDirty())
		return true;
	return false;
}

/**
* Tells the PaneAsset to clean up
*/ 
void FPSCounterPasset::shutdown()
{
	// RELEVANT TO FPS COUNTER ASSET
	g_lib.forgetResource( m_pFontDrawingProg );
	g_lib.forgetResource( m_pFpsFont );
}

/**
* Draws the PaneAsset.
*/
void FPSCounterPasset::draw( GS::Graphics::IDimensionable * const a_dims )
{
	std::string fps = "FIRST!";
	//fps= "I need to change what is written FPS: " + boost::lexical_cast<std::string>( m_pFPSCounterPresentable->getPresentationElement8(0).asInt32 );

	fps = "FPS : ";
	std::string num = std::to_string(m_pFPSCounterPresentable->getPresentationElement8(0).asInt32);
	fps.append(num);

	glUseProgram( m_pFontDrawingProg->getProgram() );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, m_pFpsFont->m_texture );
	glUniform1i( glGetUniformLocation( m_pFontDrawingProg->getProgram(), "tex" ), 0 );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//for(int i = 0; i < 2000; ++i)
	//	m_pFont->renderText( "Test!", 
	//		GS::Graphics::Vector2_t( 0.0f, 500.0f - ((float)i/3.0f) ), 
	//		GS::Graphics::Color4f_t(0.0f, 1.0f, 1.0f, 1.0f) 
	//	);

	m_pFpsFont->renderText(
		fps, 
		//GS::Graphics::Vector2_t( STATIC_CAST(_FLOAT, -dims.x), STATIC_CAST(_FLOAT, (dims.y-m_pFont->getHeight() ) ) ), 
		GS::Graphics::Vector2_t(-1000.0f, 1000.0f), 
		a_dims->getPixelDimensions(),
		1.0f,
		GS::Graphics::Color4f_t(0.0f, 1.0f, 1.0f, 1.0f) 
	);
}

/**
* Updates the PaneAsset by dt.
*/
void FPSCounterPasset::update(const _DOUBLE a_dt)
{

}


};
};
