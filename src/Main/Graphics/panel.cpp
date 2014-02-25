#include "panel.h"
#include <Graphics/openglincludes.h>

namespace GS {
namespace Graphics {

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
	
	glFramebufferTexture2D(
			GL_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D,
			m_texColorBuffer,
			0
			);	

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

	return 0;
}

void Pane::__glRboDepthStencilDestroy()
{
	if( m_rboDepthStencil )
		glDeleteRenderbuffers( 1, &m_rboDepthStencil );
}

};
};
