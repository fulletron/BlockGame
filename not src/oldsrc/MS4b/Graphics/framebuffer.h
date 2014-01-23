#ifndef __FRAMEBUFFER_H_
#define __FRAMEBUFFER_H_

#include "openglincludes.h"
#include <Game\definitions.h>

namespace GS { class Game;
namespace ResourceNS { class ShaderProgramResource; class MeshResource; };
namespace PanelNS { class Panel; };
namespace WindowNS { struct Screen; };
namespace GraphicsNS {

	class Framebuffer
	{
	public:
		virtual _UINT32 init(GS::Game * const a_pg, GS::WindowNS::Screen * const a_rpOwnerScreen, GS::WindowNS::Screen * const a_rpOwnerParentScreen) = 0;
		virtual void arm(const bool & a_clear) = 0;
		virtual void disarm(GS::PanelNS::Panel * const a_pParentPanel) = 0;
		virtual void dumpToCurrentFramebuffer() = 0;
		virtual void onScreenResize() = 0;
		virtual void shutdown() = 0;

		virtual GLuint get_gluintFramebuffer() = 0;
		virtual GLuint get_gluintTexColorBuffer() = 0;
		virtual GLuint get_gluintRboDepthStencil() = 0;

		/// DEBUG!
		virtual void setClearColor(const _ARRAYFOUR<_FLOAT> & a_cc) = 0;
	};

	class FramebufferBasic : public Framebuffer
	{
	public:
	private:
		GS::Game *											m_rpGame;

		GS::ResourceNS::ShaderProgramResource *				m_rpShaderProgram;
		GS::ResourceNS::MeshResource *						m_rpMesh;

		GLuint												m_framebuffer;
		GLuint												m_texColorBuffer;
		GLuint												m_rboDepthStencil;

		GS::WindowNS::Screen *								m_rpOwnerScreen;
		GS::WindowNS::Screen *								m_rpParentScreen;

		///DEBUG PURPOSES
		_ARRAYFOUR<_FLOAT>									m_clearColor;

	public:

		FramebufferBasic() : m_clearColor(0.11f,0.11f,0.11f, 1.0f) {}
		~FramebufferBasic(){}

		_UINT32 init(GS::Game * const a_pg, GS::WindowNS::Screen * const a_rpOwnerScreen, GS::WindowNS::Screen * const a_rpParentScreen);

		void arm(const bool & a_clear);
		void disarm(GS::PanelNS::Panel * const a_pParentPanel);
		void dumpToCurrentFramebuffer();
		void onScreenResize();
		void shutdown();

		GLuint get_gluintFramebuffer(){ return m_framebuffer; }
		GLuint get_gluintTexColorBuffer(){ return m_texColorBuffer; }
		GLuint get_gluintRboDepthStencil(){ return m_rboDepthStencil; }
	
		///DEBUG PURPOSES
		void setClearColor(const _ARRAYFOUR<_FLOAT> & a_cc){m_clearColor = a_cc;}	
	};

};
};

#endif