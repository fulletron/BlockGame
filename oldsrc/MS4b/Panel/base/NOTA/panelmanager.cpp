#include "panelmanager.h"
#include "panel.h"

namespace GS {
namespace PanelNS {
	/*
	_UINT32 PanelManager::init(GS::Game * const a_rpGame)
	{
		m_rpGame = a_rpGame;
		__sortVisiblePanels();

		return 0;
	}

	void PanelManager::render()
	{
		for(int i = m_visiblePanels.size() - 1; i >= 0; --i)
			m_visiblePanels.get(i)->draw();
	}

	void PanelManager::input(const GS::InputNS::Input & a_input, bool & a_moDone, bool & a_kbDone)
	{
		for(int i = 0; i < m_allPanels.size(); ++i)
			m_visiblePanels.get(i)->input(a_input, a_moDone, a_kbDone);
	}

	void PanelManager::update(_DOUBLE a_dt)
	{
		for(int i = 0; i < m_allPanels.size(); ++i)
			m_visiblePanels.get(i)->update(a_dt);
	}

	void PanelManager::shutdown()
	{
		for(int i = 0; i < m_allPanels.size(); ++i)
			m_visiblePanels.get(i)->shutdown();
	}

	void PanelManager::__sortVisiblePanels()
	{
		if(m_visiblePanels.size() > 1)
			m_visiblePanels.sort(__sortAlgorithm);
	}

	bool PanelManager::__sortAlgorithm(void * a1, void * a2)
	{
		Panel * d1 = (Panel *)a1;
		Panel * d2 = (Panel *)a2;
		return d1->getFocus() > d2->getFocus();
	}

	void PanelManager::onScreenResize()
	{
		for(int i = 0; i < m_allPanels.size(); ++i)
			m_allPanels.get(i)->onScreenResize();
	}

	void PanelManager::addVisiblePanel(Panel * const a_pPanel)
	{
		m_visiblePanels.add(a_pPanel);
		m_allPanels.add(a_pPanel);
	}

	void PanelManager::addHiddenPanel(Panel * const a_pPanel)
	{
		m_allPanels.add(a_pPanel);
	}
	*/
};
};