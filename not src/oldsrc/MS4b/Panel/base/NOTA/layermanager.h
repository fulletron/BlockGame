#ifndef __LAYERMANAGER_H_
#define __LAYERMANAGER_H_

#include "..\..\Game\definitions.h"

namespace GS { class Game;
namespace InputNS { class Input; };
namespace PanelNS {
	class IPanel;
	class ILayer;

	class LayerManager
	{
		public:
			//typedef GS::UtilitiesNS::GSVector<IPanel *> _GSVECTOR(IPanel*);

		private:
			GS::Game *				m_rpGame;
			GS::PanelNS::IPanel *	m_rpParentPanel;
			_GSVECTOR(ILayer*)		m_layers;

		public:
			_UINT32 init(GS::Game * const a_rpGame, GS::PanelNS::IPanel * const a_rpParentPanel, const _GSVECTOR(ILayer*) & a_layers);
			void render();
			bool input(const GS::InputNS::Input & a_input, bool & a_moDone, bool & a_kbDone);
			void update(_DOUBLE a_dt);
			void shutdown();
			void onScreenResize();
	};

};
};

#endif