#include "framebuffer.h"
#include <Game\game.h>
#include <Panel\base\panel.h>
#include <Resource\constructs\meshes.h>
#include <Resource\base\meshresource.h>
#include <Resource\constructs\shaderprograms.h>
#include <Resource\base\shaderprogramresource.h>

namespace GS {
namespace GraphicsNS {
	_UINT32 FramebufferBasic::init(GS::Game * a_pg, GS::WindowNS::Screen * const a_rpOwnerScreen, GS::WindowNS::Screen * const a_rpParentScreen)
		{
			m_rpGame = a_pg;
			m_rpOwnerScreen = a_rpOwnerScreen;
			m_rpParentScreen = a_rpParentScreen;

			/// Framebuffer base resources
			m_rpMesh = (GS::ResourceNS::MeshResource *)GS::ResourceNS::Meshes::init_mzscrn00(a_pg);
			m_rpShaderProgram = (GS::ResourceNS::ShaderProgramResource *)GS::ResourceNS::ShaderPrograms::init_spscrn00(a_pg);

			glGenFramebuffers( 1, &m_framebuffer );
			glBindFramebuffer( GL_FRAMEBUFFER, m_framebuffer );

			glGenTextures( 1, &m_texColorBuffer );
			glBindTexture( GL_TEXTURE_2D, m_texColorBuffer );

			int t_width = a_rpOwnerScreen->m_pxRect.width;
			int t_height = a_rpOwnerScreen->m_pxRect.height;
			glTexImage2D(
				GL_TEXTURE_2D, 0, GL_RGB, t_width, t_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL
			);
			/// FRAMEBUFFER VIEWPORTS BELIEVE IN 0,0,width,height
			glViewport(0,0,t_width,t_height);

			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

			glGenRenderbuffers( 1, &m_rboDepthStencil );
			glBindRenderbuffer( GL_RENDERBUFFER, m_rboDepthStencil );
			glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, t_width, t_height );
			glFramebufferRenderbuffer(
			  GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboDepthStencil
			);

			glFramebufferTexture2D(
				GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texColorBuffer, 0
			);

			// Always check that our framebuffer is ok
			if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				return -1;

			m_rpShaderProgram->useProgram();

			GLint posAttrib = glGetAttribLocation( m_rpShaderProgram->getProgramID(), "position" );
			glEnableVertexAttribArray( posAttrib );
			glVertexAttribPointer( posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof( float ), 0 );

			GLint texAttrib = glGetAttribLocation( m_rpShaderProgram->getProgramID(), "texcoord" );
			glEnableVertexAttribArray( texAttrib );
			glVertexAttribPointer( texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof( float ), (void*)( 2 * sizeof( float ) ) );

			// SET THE CURRENT FRAMEBUFFER TO MAIN AGAIN!
			glBindFramebuffer( GL_FRAMEBUFFER, 0 );
			/// FRAMEBUFFER VIEWPORTS BELIEVE IN 0,0,width,height
			glViewport(0,0,a_rpOwnerScreen->m_pxRect.width,a_rpOwnerScreen->m_pxRect.height);

			//glClearColor( m_clearColor.r, m_clearColor.g, m_clearColor.b , m_clearColor.a );
			//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			//glClearDepth(1.0);

			return 0;
		}

		void FramebufferBasic::arm(const bool & a_clear)
		{
			_RECT<_INT32> t_pxRect = m_rpOwnerScreen->m_pxRect;

			glBindFramebuffer( GL_FRAMEBUFFER, m_framebuffer );
			
			/// FRAMEBUFFER VIEWPORTS BELIEVE IN 0,0,width,height
			glViewport(0,0,t_pxRect.width,t_pxRect.height);

			if(a_clear)
			{
				glClearColor( m_clearColor.r, m_clearColor.g, m_clearColor.b , m_clearColor.a );
				glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
				glClearDepth(1.0);
			}
		}

		void FramebufferBasic::disarm(GS::PanelNS::Panel * const a_pParentPanel)
		{ 
			_RECT<_INT32> t_pxRect = m_rpParentScreen->m_pxRect;

			if(a_pParentPanel)
				glBindFramebuffer( GL_FRAMEBUFFER, a_pParentPanel->getFramebuffer()->get_gluintFramebuffer() ); 
			else
				glBindFramebuffer( GL_FRAMEBUFFER, 0 ); 

			/// FRAMEBUFFER VIEWPORTS BELIEVE IN 0,0,width,height
			glViewport(0,0,t_pxRect.width,t_pxRect.height);
		}

		void FramebufferBasic::dumpToCurrentFramebuffer()
		{
			glBindVertexArray(m_rpMesh->get__m_vao());

			glDisable(GL_DEPTH_TEST);
			m_rpShaderProgram->useProgram();

			_RECT<_INT32> t_ownerScreenRect = m_rpOwnerScreen->m_pxRect;
			_RECT<_INT32> t_parentScreenRect = m_rpParentScreen->m_pxRect;

			_FLOAT t_X = (((_FLOAT)((t_ownerScreenRect.left * 2) + t_ownerScreenRect.width)) / ((_FLOAT)(t_parentScreenRect.width))) - 1.0f;
			_FLOAT t_Y = (((_FLOAT)((t_ownerScreenRect.bottom * 2) + t_ownerScreenRect.height)) / ((_FLOAT)(t_parentScreenRect.height))) - 1.0f;

			/// THIS TRANSLATION IS BASED ON the -1.0, 1.0 maxes provided standardly.
			glm::mat4 iden = glm::mat4(1.0f);
			glm::mat4 trans = glm::translate(iden, glm::vec3(t_X,t_Y,0.0));
			glm::mat4 scale = glm::scale(trans, glm::vec3((float)t_ownerScreenRect.width / (float)t_parentScreenRect.width, (float)t_ownerScreenRect.height / (float)t_parentScreenRect.height,1.0));
			//glm::mat4 trans = glm::translate(scale, glm::vec3(t_X,t_Y,0.0));
			//glm::mat4 rotTransScale = glm::rotate(transScale, (float)clock() / (float)CLOCKS_PER_SEC * 180.0f, glm::vec3(0.0f,0.0f,1.0f) );

			m_rpShaderProgram->setUniform("trans",&scale);

			/// ================================================================

			glActiveTexture(GL_TEXTURE0);
			glBindTexture( GL_TEXTURE_2D, m_texColorBuffer );

			glDrawArrays( GL_TRIANGLES, 0, 6 );
		}

		void FramebufferBasic::onScreenResize()
		{
			shutdown();
			init(m_rpGame, m_rpOwnerScreen, m_rpParentScreen);
		}

		void FramebufferBasic::shutdown()
		{
			glDeleteRenderbuffers( 1, &m_rboDepthStencil);
			m_rboDepthStencil = 0;

			glDeleteTextures( 1, &m_texColorBuffer);
			m_texColorBuffer = 0;

			glDeleteFramebuffers( 1, &m_framebuffer );
			m_framebuffer = 0;

			m_rpGame->getLibrary()->remEntry((_UINT64)"mzscrn00");
			m_rpGame->getLibrary()->remEntry((_UINT64)"spscrn00");
		}

};
};