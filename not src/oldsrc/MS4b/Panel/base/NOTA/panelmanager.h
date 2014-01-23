#ifndef __PANELMANAGER_H_
#define __PANELMANAGER_H_

//#include "panel.h"
#include "..\..\Game\definitions.h"

namespace GS { class Game;
namespace InputNS { class Input; }
namespace PanelNS {
	class Panel;
	/*
	class PanelManager
	{
		private:
			GS::Game * m_rpGame;

			_GSVECTOR(IActor*) m_actors;

			static bool __sortAlgorithm(void *, void *);
			void __sortActors();

		public:
			_UINT32 init(GS::Game * const a_rpGame);
			void render();
			void input(const GS::InputNS::Input & a_input, bool&, bool&);
			void update(_DOUBLE a_dt);
			void shutdown();
			void onScreenResize();

			void addActor(Panel * const);
			void removeActor(Panel * const);
	};
	*/
};
};

#endif