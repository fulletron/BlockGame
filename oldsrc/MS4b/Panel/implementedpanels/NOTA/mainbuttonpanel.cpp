#include "mainbuttonpanel.h"
//#include "..\Resource\resourcedictionary.h"
#include <Entity\entitymanager.h>

/// INSTR :: EVERY ENTITY IN THE PANEL NEEDS TO BE INCLUDED
//#include "..\..\Entity\backgroundimage.h"
#include <Entity\button.h>

namespace GS {
namespace PanelNS {
	_UINT32 MainButtonPanel::init(GS::Game * a_rpGame)
	{
		m_rpGame = a_rpGame;

		/// INSTR :: SET THESE THREE TO WHAT THEY SHOULD BE!
		m_isInputGate = false;
		m_isDrawGate = false;
		m_panelLayerNum = 0;

		/*
		GS::EntityNS::EntityManager::EntPtrVector t_allEntities;

		/// INSTR :: NEW EVERY ENTITY AND ADD IT TO THE LIST
		m_pButtonTEST = new GS::EntityNS::Button();
		m_pButtonTEST->init(m_rpGame, 
				&EntityNS::Builder_Button(
					L"TEST!",
					ResourceNS::BUTTON_MENU,
					_2DFLOATVEC(0.5f, 0.5f),
					_2DFLOATVEC(1.0f, 1.0f)
				)
			);
		t_allEntities.add(m_pButtonTEST);

		m_entityManager.init(m_rpGame, t_allEntities);
		*/

		return 0;
	}
};
};