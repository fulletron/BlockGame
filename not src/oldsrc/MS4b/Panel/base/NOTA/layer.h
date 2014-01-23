#ifndef __LAYER_H_
#define __LAYER_H_

#include "..\..\Entity\entitymanager.h"

namespace GS { class Game; 
namespace PanelNS {
	class IPanel;
	class ILayer
	{
		public:
			virtual _UINT32 init(GS::Game * const, GS::PanelNS::IPanel * const) = 0;
			virtual void draw() = 0;
			virtual bool input(const GS::InputNS::Input & a_input, bool & a_moDone, bool & a_kbDone) = 0;
			virtual void update(_DOUBLE a_dt) = 0;
			virtual void shutdown() = 0;
			virtual void onScreenResize() = 0;
			virtual bool isDirty() = 0;
			virtual IPanel * getParentPanel() = 0;
	};

	class LayerBase : public ILayer
	{
	public:
	protected:
		GS::Game *						m_rpGame;
		GS::EntityNS::EntityManager		m_entityManager;
		bool							m_isDirty;
		//FrameBuffer					m_fb;
		IPanel *						m_pParentPanel;
	public:
		LayerBase()
		: m_rpGame(0)
		{}

		virtual _UINT32 init(GS::Game * const, GS::PanelNS::IPanel * const) = 0;

		void onScreenResize();
		void draw();
		bool input(const GS::InputNS::Input & a_input, bool & a_moDone, bool & a_kbDone);
		void update(_DOUBLE a_dt);
		void shutdown();
		bool isDirty(){return m_isDirty;}
		IPanel * getParentPanel(){return m_pParentPanel;}
	};

};
};


#endif