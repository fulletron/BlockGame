#include "panel.h"
#include <Graphics/openglincludes.h>
#include <Graphics/window.h>

extern GS::Graphics::Window g_window;

namespace GS {
namespace Graphics {

_BOOL Pane::m_screenLoaded = false;
GLuint Pane::m_vaoQuad = 0;
GLuint Pane::m_vboQuad = 0;

_INT32 Pane::initPaneBlues( Pane * const a_pParentPane, const Vec4D<float> & a_blueprint )
{
	m_pParentPane = a_pParentPane;
	m_boxBlueprint = a_blueprint;
	__calculateDimActual();
	return 0;
}

_UINT32 Pane::initFramebuffer()
{
	if( __glFramebufferInit() )
		return 1;
	if( __glTexColorBufferInit() )
		return 2;
	if( __glRboDepthStencilInit() )
		return 3;
	if ( __initScreenVAOVBO() )
		return 5;
	if( glCheckFramebufferStatus(GL_FRAMEBUFFER)
		!= GL_FRAMEBUFFER_COMPLETE)
		return 4;
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
		m_boxActual.box_width = pParentActual->box_width * m_boxBlueprint.box_width;
		m_boxActual.box_height = pParentActual->box_height * m_boxBlueprint.box_height;
		m_boxActual.pos_x = pParentActual->box_width * m_boxBlueprint.pos_x;
		m_boxActual.pos_y = pParentActual->box_height * m_boxBlueprint.pos_y;
	} else {
		Vec2D<_INT32> winDim = g_window.getPixDims();
		m_boxActual.box_width = winDim.x * m_boxBlueprint.box_width;
		m_boxActual.box_height = winDim.y * m_boxBlueprint.box_width;
		m_boxActual.pos_x = winDim.x * m_boxBlueprint.pos_x;
		m_boxActual.pos_y = winDim.y * m_boxBlueprint.pos_y;
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
