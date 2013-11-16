#ifndef __MENUSTATE_H_
#define __MENUSTATE_H_

#include "state.h"

namespace GS {
namespace PanelNS{ class Panel; };
namespace StateNS {
	class MenuState : public GS::StateNS::StateBase
	{
	private:
		/// INSTR :: THIS IS A LIST OF EVERY PANEL
		/// AVAILABLE TO THE STATE
		//GS::PanelNS::Panel *			m_pPanelBackground;
		GS::PanelNS::Panel *			m_pPanelDebugInfo;

	public:
		/// INSTR :: INITIALIZERLIST ALL TO NULL
		MenuState()
			: //m_pPanelBackground(0), 
			m_pPanelDebugInfo(0)
		{}
		_UINT32 init(GS::Game*);
	};
};
};

#endif