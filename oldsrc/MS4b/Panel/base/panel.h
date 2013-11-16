#ifndef __PANEL_H_
#define __PANEL_H_

#include "..\..\Game\definitions.h"
#include <Graphics\framebuffer.h>
#include <Graphics\actor.h>
#include <Graphics\window.h>

namespace GS { class Game;
namespace InputNS{ class Input; };
namespace PanelNS {
	
	class Panel : public GS::GraphicsNS::ActorBase
	{
		public:
			virtual void becomeDirty() = 0;
			virtual bool isInputGate() = 0;
			virtual bool isDrawGate() = 0;
			virtual bool isDirty() = 0;
			virtual GS::WindowNS::Screen * getScreen() = 0;
			virtual GS::WindowNS::Screen * getParentScreen() = 0;
			virtual Panel * getParentPanel() = 0;
			virtual GS::GraphicsNS::Framebuffer * getFramebuffer() = 0;
	};

	class PanelBase : public Panel
	{
		protected:
			/// PANEL GIVENS
			GS::Game *						m_rpGame;
			GS::GraphicsNS::Framebuffer *	m_pFramebuffer;

			/// PANEL STATIC ATTRIBUTES! (SET AND FORGET!)
			bool							m_isInputGate;
			bool							m_isDrawGate;
			Panel *							m_pParentPanel;
			GS::WindowNS::Screen *			m_pParentScreen;

			/// PANEL DYNAMIC ATTRIBUTES
			bool							m_isDirty;
			GS::WindowNS::Screen 			m_screen;

		public:
			PanelBase()
			: m_rpGame(0), m_pFramebuffer(0), m_isInputGate(false), m_isDrawGate(false), m_pParentPanel(0)
			{}

			void								becomeDirty(){m_isDirty = true; if(m_pParentPanel){m_pParentPanel->becomeDirty();}}

			bool								isInputGate(){return m_isInputGate;}
			bool								isDrawGate(){return m_isDrawGate;}
			bool								isDirty(){return m_isDirty;}

			Panel *								getParentPanel(){return m_pParentPanel;}
			GS::WindowNS::Screen *				getParentScreen(){return m_pParentScreen;}
			GS::WindowNS::Screen *				getScreen(){return &m_screen;}
			GS::GraphicsNS::Framebuffer *		getFramebuffer(){return m_pFramebuffer;}

			virtual void								draw();
			bool								input(GS::InputNS::Input * const);
			virtual void								update(const _DOUBLE &);
			void								shutdown();
			void								onScreenResize();

			void								setParentPanel(Panel * const a_pParentPanel);

	};
};
};

#endif