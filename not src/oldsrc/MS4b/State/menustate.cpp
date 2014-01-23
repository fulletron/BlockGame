#include "menustate.h"
#include "..\Panel\base\panel.h"
/// THIS INCLUDE LIST IS FOR EACH INDIVIDUAL PANEL POSSIBLY ON THE SCREEN
//#include <Panel\implementedpanels\panelbackground.h>
#include <Panel\implementedpanels\paneldebuginfo.h>

#include <Entity\paneentities.h>
#include <Resource\constructs\textures.h>
#include <Resource\constructs\fonts.h>

namespace GS {
namespace StateNS {
	_UINT32 MenuState::init(GS::Game* a_rpGame)
	{
		m_rpGame = a_rpGame;

		/// INSTR :: THIS IS WHERE PANELS GET ASSIGNED (AND NEW'D), 
		/// ADDED TO A LIST OF ALL AND VISIBLE, AND THEN INIT'D THROUGH
		/// THE PANEL MANAGER init FUNCTION.

		//m_actorManager.addActor((GS::EntityNS::Entity2D *)GS::EntityNS::PaneTexture::Construct(
		//	a_rpGame, 
		//	0,
		//	GS::ResourceNS::Textures::init_panebk00,
		//	_RECT<_FLOAT>(0.50f,0.50f,1.00f,1.00f),
		//	ALIGN_CENTER
		//	));

		m_actorManager.addActor(GS::PanelNS::PanelDebugInfo::Construct(a_rpGame, 0));
		///m_actorManager.addActor(GS::PanelNS::LayerDebugInfoList::Construct(a_rpGame, 0));
		//m_actorManager.addActor(GS::EntityNS::PaneTexture::Construct(
		//	a_rpGame,
		//	0,
		//	GS::ResourceNS::Textures::init_panebk00,
		//	_RECT<_FLOAT>(0.5f,0.5f,1.0f,1.0f),
		//	ALIGN_CENTER)
		//);
		/*
		m_actorManager.addActor((GS::EntityNS::Entity2D *)GS::EntityNS::PaneFontText::Construct(
			a_rpGame, 
			0,
			GS::ResourceNS::Fonts::init_ftkash48,
			//_RECT<_FLOAT>(0.50f,1.00f - (i * 0.05f),0.0f,0.05f),
			_RECT<_FLOAT>(0.25f,0.50,0.0f,0.33f),
			ALIGN_CENTER,
			_ARRAYFOUR<_FLOAT>(1.0f,1.0f,1.0f,1.0f),
			GS::EntityNS::DATATYPE_NONE,
			0,
			"Test fps:"
			));
		*/
		m_actorManager.init(m_rpGame);

		return 0;
	}
};
};