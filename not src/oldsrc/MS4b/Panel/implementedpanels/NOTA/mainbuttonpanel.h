#ifndef __MAINBUTTONPANEL_H_
#define __MAINBUTTONPANEL_H_

#include "Panel\base\panel.h"
#include "..\..\Entity\entity.h"
namespace GS {
namespace EntityNS {
	/// INSTR :: THIS IS A LIST OF EVERY
	/// ENTITY AVAILABLE TO THE PANEL
	class Button;
};
namespace PanelNS {
	class MainButtonPanel : public GS::PanelNS::PanelBase
	{
		private:
			/// INSTR :: THIS IS WHERE THE ENTITIES GO
			GS::EntityNS::Button *		m_pButtonTEST;

		public:
			/// INSTR :: INITIALIZER LIST NEEDS TO NULL EVERYTHING!
			MainButtonPanel() 
			{}

			_UINT32 init(GS::Game *);
	};
};
};

#endif