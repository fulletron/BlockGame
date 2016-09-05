#include <Graphics/reslib.h>

#include <Graphics/Panes/DebugPane/bkgpicpasset.h>
//#include <Game/brain.h> // TODO :: REMOVE! ONCE SINGLETON IS NO LONGER USED

extern GS::Graphics::ResourceLibrary g_lib;

namespace GS {
namespace Graphics {

/**
* init the paneasset resources
*/
_INT32 BkgPicPasset::init( Pane * const a_pParent )
{
	m_pParentPane = a_pParent;

	// RELEVANT TO FPS COUNTER ASSET
	m_pTex = g_lib.findTextureResource( CV8::TEX::PANEBKG );
	m_pTexProg = g_lib.findShaderProgramResource( CV8::RES_SP_TEXRECTDRAW );
	m_pScreenMesh = g_lib.findMeshResource( CV8::RES_MSH_SCREEN );

	m_texloc = glGetUniformLocation( m_pTexProg->getProgram(), "tex" );
	m_transloc = glGetUniformLocation( m_pTexProg->getProgram(), "trans");

	return 0;
}


_BOOL BkgPicPasset::isDirty() const
{
	//return true;
	return false;
}

/**
* Tells the PaneAsset to clean up
*/ 
void BkgPicPasset::shutdown()
{
	g_lib.forgetResource( m_pTex );
	g_lib.forgetResource( m_pTexProg );
	g_lib.forgetResource( m_pScreenMesh );
}

/**
* Draws the PaneAsset.
*/
void BkgPicPasset::draw( GS::Graphics::IDimensionable * const a_dims )
{
	glUseProgram( m_pTexProg->getProgram() );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, m_pTex->getTexture() );
	glUniform1i( m_texloc, 0 );

	// BIND ALL THE CRAP
	glBindVertexArray( m_pScreenMesh->getVAO() );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_pScreenMesh->getEBO() );
	glUseProgram( m_pTexProg->getProgram() );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, m_pTex->getTexture() );

	glUniform1i( m_texloc, 0 );

	glm::mat4 trans;
	trans = glm::scale(trans, glm::vec3(1.0f, 1.0f, 1.0f));
	trans = glm::translate(trans, glm::vec3( 0.0f * 2.0f, 0.0f * 2.0f, 0.0f ));
	glUniformMatrix4fv( m_transloc, 1, GL_FALSE, glm::value_ptr(trans) );

  	// THESE NEED TO BE SPECIFIED EVERYTIME
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	_CheckForErrors();
}

/**
* Updates the PaneAsset by dt.
*/
void BkgPicPasset::update(const _DOUBLE a_dt)
{
}


};
};
