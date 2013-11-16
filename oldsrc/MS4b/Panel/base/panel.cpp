#include "panel.h"
#include <Graphics\window.h>
#include <Game\game.h>

namespace GS {
namespace PanelNS {

	void PanelBase::draw()
	{
		if(isDirty())
		{
			if(m_pFramebuffer)
				m_pFramebuffer->arm(true);
			m_actorManager.manageDraw();

			if(m_pFramebuffer)
				m_pFramebuffer->disarm(m_pParentPanel);

			m_isDirty = false;
		}

		if(m_pFramebuffer)
			m_pFramebuffer->dumpToCurrentFramebuffer();
			//if(getParentPanel())
			//	m_pFramebuffer->dumpToFramebuffer(getParentPanel()->getFramebuffer());
			//else
			//	m_pFramebuffer->dumpToFramebuffer(0);

	}
	bool PanelBase::input(GS::InputNS::Input * const a_input)
	{
		m_actorManager.manageInput(a_input);

		return false;
	}
	void PanelBase::update(const _DOUBLE & a_dt)
	{
		m_actorManager.manageUpdate(a_dt);
	}
	void PanelBase::shutdown()
	{
		m_actorManager.manageShutdown();
	}

	void PanelBase::onScreenResize()
	{
		m_screen.m_pxRect = GS::WindowNS::GetPXRectFromRect(m_screen.m_relPosCov, m_screen.m_relAlignment, getParentScreen()->m_pxRect);
		getFramebuffer()->onScreenResize();
		m_actorManager.manageOnScreenResize();
		m_isDirty = true;
	}

	void PanelBase::setParentPanel(Panel * const a_pParentPanel)
	{
		if(a_pParentPanel)
		{
			m_pParentPanel = a_pParentPanel;
			m_pParentScreen = a_pParentPanel->getScreen();
		}
		else
		{
			m_pParentPanel = 0;
			m_pParentScreen = m_rpGame->getGraphics()->get__m_baseWindow()->get__m_windowScreen();
		}
	}
};
};