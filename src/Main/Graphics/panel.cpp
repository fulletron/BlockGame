#include "panel.h"
#include <Graphics/openglincludes.h>
#include <Graphics/window.h>
#include <Graphics/reslib.h>

extern GS::Graphics::Window g_window;
extern GS::Graphics::ResourceLibrary g_lib;


namespace GS {
namespace Graphics {

_BOOL Pane::m_screenLoaded = false;
GLuint Pane::m_vaoQuad = 0;
GLuint Pane::m_vboQuad = 0;
Pane * Pane::NO_PARENT = 0;

GLuint Pane::getFramebuffer() const
{
	return m_framebuffer;
}

_INT32 Pane::init()
{
	m_pTex = g_lib.findTextureResource( CV8::RES_TEX_PANEBKG );	
	m_pMesh = g_lib.findMeshResource( CV8::RES_MSH_RECT );
	m_pTexProg = g_lib.findShaderProgramResource( CV8::RES_SP_TEXRECTDRAW );
	m_pScreenMesh = g_lib.findMeshResource( CV8::RES_MSH_SCREEN );

	m_texloc = glGetUniformLocation( m_pTexProg->getProgram(), "tex" );
	m_transloc = glGetUniformLocation( m_pTexProg->getProgram(), "trans");

	return __postInit();
}

Vec2D<_INT32> Pane::getPixelDimensions() const
{
	Vec2D<_INT32> dims;
	dims.x = m_boxActual.box_width;
	dims.y = m_boxActual.box_height;

	return dims;
	// KYLE :: THIS MIGHT GET PERMISSIVE ON ERROR!
	//return Vec2D<_INT32>(m_boxActual.box_width, m_boxActual.box_height);
}

_INT32 Pane::initPaneBlues( Pane * const a_pParentPane, const Vec4D<float> & a_blueprint )
{
	m_pParentPane = a_pParentPane;
	m_boxBlueprint = a_blueprint;

	__calculateDimActual();
	__initFramebuffer();

	return 0;
}

_UINT32 Pane::__initFramebuffer()
{
	if( __glFramebufferInit() )
		return 1;
	if( __glTexColorBufferInit() )
		return 2;
	if( __glRboDepthStencilInit() )
		return 3;
	if ( __initScreenVAOVBO() )
		return 4;
	if( glCheckFramebufferStatus(GL_FRAMEBUFFER)
		!= GL_FRAMEBUFFER_COMPLETE)
		return 5;
	return 0;
}

_INT32 Pane::__initScreenVAOVBO()
{
	if ( m_screenLoaded )
		return 0;
	// Framebuffer Quad vertices
	GLfloat quadVertices[] = {
		-1.0f,  1.0f,  0.0f, 1.0f,	 
		 1.0f,  1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		 1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		-1.0f,  1.0f,  0.0f, 1.0f
	};

	// Create VAOs
	glGenVertexArrays(1, &m_vaoQuad);
	glBindVertexArray(m_vaoQuad);

	// Load vertex dat
	glGenBuffers(1, &m_vboQuad);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboQuad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glVertexAttribPointer( (GLuint)0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0 );
	glVertexAttribPointer( (GLuint)1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)) );

	m_screenLoaded = true;

	return 0;
}

void Pane::draw( GS::Graphics::IDimensionable * const a_dimensionable )
{
	if ( !a_dimensionable )
		return;

	if( isDirty() )
	{	
		glViewport(0, 0, m_boxActual.box_width, m_boxActual.box_height);
        glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.50f,0.20f,0.20f,1.0f);
        //glEnable(GL_DEPTH_TEST);
		//glEnable(GL_STENCIL_TEST);
		//glDisable(GL_STENCIL_TEST);
		
		for( std::vector<IPaneAsset *>::iterator it_asset = m_paneAssets.begin(); 
			it_asset != m_paneAssets.end();
			++it_asset )
			(*it_asset)->draw( this );
	}

	Vec2D<_INT32> dims = a_dimensionable->getPixelDimensions();

	glViewport(0, 0, dims.x, dims.y);
	glBindFramebuffer( GL_FRAMEBUFFER, a_dimensionable->getFramebuffer() );
	// BIND ALL THE CRAP
	glBindVertexArray( m_pScreenMesh->getVAO() );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_pScreenMesh->getEBO() );
	glUseProgram( m_pTexProg->getProgram() );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, m_texColorBuffer );

	//static GLint S_TEXLOC = glGetUniformLocation( m_pTexProg->getProgram(), "tex" );
	//glUniform1i( S_TEXLOC, 0 );
	glUniform1i( m_texloc, 0 );

	//static GLint S_TRANSLOC = glGetUniformLocation( m_pTexProg->getProgram(), "trans");
	glm::mat4 trans;
	//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 1.0f));
	trans = glm::scale(trans, glm::vec3(m_boxBlueprint.box_width, m_boxBlueprint.box_height, 1.0f));
	//trans = glm::translate(trans, glm::vec3( -1.0f, 1.0f, 0.0f ));
	trans = glm::translate(trans, glm::vec3( m_boxBlueprint.pos_x * 2.0f, m_boxBlueprint.pos_y * 2.0f, 0.0f ));
	//glUniformMatrix4fv( S_TRANSLOC, 1, GL_FALSE, glm::value_ptr(trans) );
	glUniformMatrix4fv( m_transloc, 1, GL_FALSE, glm::value_ptr(trans) );

  	// THESE NEED TO BE SPECIFIED EVERYTIME
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
}

_BOOL Pane::isDirty() const
{
	// Go through all of this panels PaneAssets
	for( std::vector<IPaneAsset *>::const_iterator it_asset = m_paneAssets.begin(); 
		it_asset != m_paneAssets.end();
		++it_asset )
		// If any asset is dirty, return true
		if ( (*it_asset)->isDirty() )
			return true;

	// If no asset is dirty, the panel itself is clean
	return false;
}

_BOOL Pane::handleInput()
{
	// Go through all of this panels PaneAssets
	for( std::vector<IPaneAsset *>::const_iterator it_asset = m_paneAssets.begin(); 
		it_asset != m_paneAssets.end();
		++it_asset )
		// If any asset is dirty, return true
		if ( (*it_asset)->handleInput() )
			return true;

	// If no asset is dirty, the panel itself is clean
	return false;
}


void Pane::update( const _DOUBLE a_dt )
{
	for( std::vector<IPaneAsset *>::iterator it_asset = m_paneAssets.begin(); 
		it_asset != m_paneAssets.end();
		++it_asset )
		(*it_asset)->update( a_dt );
}

void Pane::shutdown()
{
	__preShutdown();

	g_lib.forgetResource( m_pTex->getType(), m_pTex->getName() );
	g_lib.forgetResource( m_pScreenProg->getType(), m_pScreenProg->getName() );
	g_lib.forgetResource( m_pTexProg->getType(), m_pTexProg->getName() );
	g_lib.forgetResource( m_pMesh->getType(), m_pMesh->getName() );
	g_lib.forgetResource( m_pScreenMesh->getType(), m_pScreenMesh->getName() );
}

void Pane::__shutdownScreenVAOVBO()
{
	if( !m_screenLoaded )
		return;

	glDeleteVertexArrays(1, &m_vaoQuad );
	glDeleteBuffers(1, &m_vboQuad );

	m_vaoQuad = 0;
	m_vboQuad = 0;

	m_screenLoaded = false;
}

_INT32 Pane::__calculateDimActual()
{
	if( m_pParentPane ) {
		Vec4D<_UINT32> * pParentActual = &(m_pParentPane->m_boxActual);
		m_boxActual.box_width = STATIC_CAST(_UINT32, pParentActual->box_width * m_boxBlueprint.box_width);
		m_boxActual.box_height = STATIC_CAST(_UINT32, pParentActual->box_height * m_boxBlueprint.box_height);
		m_boxActual.pos_x = STATIC_CAST(_UINT32, pParentActual->box_width * m_boxBlueprint.pos_x);
		m_boxActual.pos_y = STATIC_CAST(_UINT32, pParentActual->box_height * m_boxBlueprint.pos_y);
	} else {
		Vec2D<_INT32> winDim = g_window.getPixelDimensions();
		m_boxActual.box_width = STATIC_CAST(_UINT32, winDim.x * m_boxBlueprint.box_width);
		m_boxActual.box_height = STATIC_CAST(_UINT32, winDim.y * m_boxBlueprint.box_width);
		m_boxActual.pos_x = STATIC_CAST(_UINT32, winDim.x * m_boxBlueprint.pos_x);
		m_boxActual.pos_y = STATIC_CAST(_UINT32, winDim.y * m_boxBlueprint.pos_y);
	}
	return 0;
}

_UINT32 Pane::__glFramebufferInit()
{
	if( m_framebuffer )
		__glFramebufferDestroy();
	
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer( GL_FRAMEBUFFER, m_framebuffer );

	return 0;
}

void Pane::__glFramebufferDestroy()
{
	if( m_framebuffer )
		glDeleteFramebuffers(1, &m_framebuffer);
}
/* REFERENCE
    // Create frame buffer
    GLuint frameBuffer;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    // Create texture to hold color buffer
    GLuint texColorBuffer;
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

    // Create Renderbuffer Object to hold depth and stencil buffers
    GLuint rboDepthStencil;
    glGenRenderbuffers(1, &rboDepthStencil);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepthStencil);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepthStencil);

*/
_UINT32 Pane::__glTexColorBufferInit()
{
	if( m_texColorBuffer )
		__glTexColorBufferDestroy();
	
	glGenTextures( 1, &m_texColorBuffer );
	glBindTexture( GL_TEXTURE_2D, m_texColorBuffer );

	glTexImage2D( 	GL_TEXTURE_2D, 
			0, 
			GL_RGB, 
			m_boxActual.box_width,
			m_boxActual.box_height,
			0, 
			GL_RGB, 
			GL_UNSIGNED_BYTE, 
			NULL
			);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_texColorBuffer, 0);
	glFramebufferTexture2D(
			GL_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D,
			m_texColorBuffer,
			0
			);	

	// DE BIND THIS TEXTURE. IT IS THE OUT OF WHENEVER FRAMEBUFFER IS
	// DRAWN TO
	glBindTexture( GL_TEXTURE_2D, 0 );

	return 0;
}

void Pane::__glTexColorBufferDestroy()
{
	if( m_texColorBuffer )
		glDeleteTextures( 1, &m_texColorBuffer );
}

_UINT32 Pane::__glRboDepthStencilInit()
{
	if( m_rboDepthStencil )
		__glRboDepthStencilDestroy();

	glGenRenderbuffers( 1, &m_rboDepthStencil );
	
	glBindRenderbuffer( GL_RENDERBUFFER, m_rboDepthStencil );
	glRenderbufferStorage(	GL_RENDERBUFFER, 
				GL_DEPTH24_STENCIL8, 
				m_boxActual.box_width,
				m_boxActual.box_height
				);
	
	glFramebufferRenderbuffer( 
			GL_FRAMEBUFFER,
			GL_DEPTH_STENCIL_ATTACHMENT,
			GL_RENDERBUFFER, 
			m_rboDepthStencil
			);

	// PUT IT BACK- BINDING THE FRAMEBUFFER GETS THIS
	glBindRenderbuffer( GL_RENDERBUFFER, 0 );

	// DE BIND THE FRAME BUFFER- USE IT WHEN DRAWING
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
	return 0;
}

void Pane::__glRboDepthStencilDestroy()
{
	if( m_rboDepthStencil )
		glDeleteRenderbuffers( 1, &m_rboDepthStencil );
}

};
};
