#include "worldpanel.h"

namespace GS {
namespace PanelNS {
	_UINT32 WorldPanel::init(GS::Game * a_rpGame)
	{
		m_rpGame = a_rpGame;
		m_isInputGate = false;
		m_isDrawGate = false;
		m_panelLayerNum = 0;

		//TEST_entity = new GS::EntityNS::EntityTest();

		return 0;
	}

};
};