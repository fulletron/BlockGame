#include "paneldebuginfo.h"

#include <Graphics\window.h>
#include <Game\game.h>

/// INSTR :: EVERY ENTITY IN EACH LAYER NEEDS TO BE INCLUDED
#include <Entity\paneentities.h>

#include <Resource\constructs\fonts.h>
#include <Resource\constructs\shaderprograms.h>
#include <Resource\constructs\meshes.h>
#include <Resource\constructs\textures.h>

#include <Resource\base\shaderprogramresource.h>
#include <Resource\base\meshresource.h>

#include <Graphics\openglincludes.h>

namespace GS {
namespace PanelNS {

	LayerDebugInfoList * LayerDebugInfoList::Construct(GS::Game * const a_pG, GS::PanelNS::Panel * const a_rpParentPanel)
	{
		LayerDebugInfoList * ret = new LayerDebugInfoList();
		ret->m_rpGame = a_pG;
		ret->setParentPanel(a_rpParentPanel);

		ret->m_fps = 0;
		ret->m_time = 0;

		/// INSTR :: SET THESE THREE TO WHAT THEY SHOULD BE!
		ret->m_isInputGate = false;
		ret->m_isDrawGate = false;
		ret->setMyBaseFocus(200);

		ret->m_screen.set(ret->getParentScreen(), _RECT<_FLOAT>(0.50f,0.50f,1.00f,1.00f), ALIGN_CENTER);

		/// SET FRAMEBUFFER STUFF
		ret->m_pFramebuffer = new GS::GraphicsNS::FramebufferBasic();
		ret->m_pFramebuffer->init(a_pG, &ret->m_screen, ret->getParentScreen());
		ret->m_pFramebuffer->setClearColor(_ARRAYFOUR<_FLOAT>(0.0f,0.22f,0.0f,1.0f));
		ret->m_isDirty = true;

		/// INSTR :: NEW EVERY ENTITY AND ADD IT TO THE LIST
		ret->m_actorManager.addActor((GS::EntityNS::Entity2D *)GS::EntityNS::PaneTexture::Construct(
			a_pG, 
			ret,
			GS::ResourceNS::Textures::init_smalbk00,
			_RECT<_FLOAT>(0.50f,0.50f,1.00f,1.00f),
			ALIGN_CENTER
			));

		////for(int i = 0; i < TESTNUMREPS; ++i)
		////{
		//ret->m_actorManager.addActor((GS::EntityNS::Entity2D *)GS::EntityNS::PaneFontText::Construct(
		//	a_pG, 
		//	ret,
		//	GS::ResourceNS::Fonts::init_ftkash48,
		//	//_RECT<_FLOAT>(0.50f,1.00f - (i * 0.05f),0.0f,0.05f),
		//	_RECT<_FLOAT>(0.25f,0.50,0.0f,0.33f),
		//	ALIGN_CENTER,
		//	_ARRAYFOUR<_FLOAT>(1.0f,1.0f,1.0f,1.0f),
		//	GS::EntityNS::DATATYPE_NONE,
		//	0,
		//	"Test fps:"
		//	));

		ret->m_actorManager.addActor((GS::EntityNS::Entity2D *)GS::EntityNS::PaneFontText::Construct(
			a_pG, 
			ret,
			GS::ResourceNS::Fonts::init_ftkash48,
			//_RECT<_FLOAT>(0.50f,1.00f - (i * 0.05f),0.0f,0.05f),
			_RECT<_FLOAT>(0.65f,0.50,0.0f,0.20f),
			ALIGN_CENTER,
			_ARRAYFOUR<_FLOAT>(1.0f,1.0f,1.0f,1.0f),
			GS::EntityNS::DATATYPE_UINT32,
			&ret->m_fps,
			""
			));
		//}
	
		ret->m_actorManager.init(a_pG);

		return ret;
	}

	void LayerDebugInfoList::update(const _DOUBLE & a_dt)
	{
		/// NEEDS TO HAPPEN TO EVERY PANEL FOREVER!
		m_actorManager.manageUpdate(a_dt);

		if(m_time > 1.0)
		{
			m_time = 0.0;
			m_fps = 0;
		}

		m_time += a_dt;
		m_fps++;

		if(m_time > 1.0)
		{
			becomeDirty();
		}

	}

	PanelDebugInfo * PanelDebugInfo::Construct(GS::Game * const a_rpGame, GS::PanelNS::Panel * const a_rpPanel)
	{
		PanelDebugInfo * ret = new PanelDebugInfo();
		ret->m_rpGame = a_rpGame;
		ret->setParentPanel(a_rpPanel);

		/// INSTR :: SET THESE THREE TO WHAT THEY SHOULD BE!
		ret->m_isInputGate = false;
		ret->m_isDrawGate = false;
		ret->setMyBaseFocus(200);

		ret->m_screen.set(ret->getParentScreen(), _RECT<_FLOAT>(0.50f,0.05f,0.10f,0.10f), ALIGN_CENTER);
		//ret->m_screen.set(ret->getParentScreen(), _RECT<_FLOAT>(0.50f,0.75f,1.00f,1.00f), ALIGN_CENTER);
		//ret->m_screen.set(ret->getParentScreen(), _RECT<_FLOAT>(0.50f,0.50f,0.50f,0.50f), ALIGN_CENTER);
		//ret->m_screen.set(ret->getParentScreen(), _RECT<_FLOAT>(0.50f,0.50f,0.50f,1.00f), ALIGN_CENTER);
		//ret->m_screen.set(ret->getParentScreen(), _RECT<_FLOAT>(0.50f,0.50f,1.00f,1.00f), ALIGN_CENTER);

		ret->m_pFramebuffer = new GS::GraphicsNS::FramebufferBasic();
		ret->m_pFramebuffer->init(a_rpGame, &ret->m_screen, ret->getParentScreen());
		ret->m_pFramebuffer->setClearColor(_ARRAYFOUR<_FLOAT>(1.0f,0.0f,0.0f,1.0f));
		ret->m_isDirty = true;

		/// INSTR :: NEW EVERY LAYER... INIT IT?
		//ret->m_actorManager.addActor(GS::PanelNS::LayerDebugInfoList::Construct(a_rpGame, ret));

		ret->m_actorManager.addActor(GS::EntityNS::PaneTexture::Construct(
			a_rpGame,
			0,
			GS::ResourceNS::Textures::init_panebk00,
			_RECT<_FLOAT>(0.5f,0.5f,1.0f,1.0f),
			ALIGN_CENTER)
		);

		ret->m_actorManager.addActor((GS::EntityNS::Entity2D *)GS::EntityNS::PaneFontText::Construct(
			a_rpGame, 
			ret,
			GS::ResourceNS::Fonts::init_ftkash48,
			//_RECT<_FLOAT>(0.50f,1.00f - (i * 0.05f),0.0f,0.05f),
			_RECT<_FLOAT>(0.25f,0.50,0.0f,0.33f),
			ALIGN_CENTER,
			_ARRAYFOUR<_FLOAT>(1.0f,1.0f,1.0f,1.0f),
			GS::EntityNS::DATATYPE_NONE,
			0,
			"Test fps:"
			));

		return ret;
	}
};
};