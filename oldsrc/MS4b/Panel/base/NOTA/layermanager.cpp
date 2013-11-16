#include "layermanager.h"
#include "layer.h"

namespace GS {
namespace PanelNS {

	_UINT32 LayerManager::init(GS::Game * const a_rpGame, GS::PanelNS::IPanel * const a_rpParentPanel, const _GSVECTOR(ILayer*) & a_layers)
	{
		m_rpGame = a_rpGame;
		m_rpParentPanel = a_rpParentPanel;
		m_layers.copy(a_layers);
		 
		///ARE LAYERS INITD AT THIS POINT?
		for(int i = 0; i < m_layers.size(); ++i)
			m_layers.get(i)->init(m_rpGame, m_rpParentPanel);

		return 0;
	}

	void LayerManager::render()
	{
		for(int i = m_layers.size() - 1; i >= 0; --i)
			m_layers.get(i)->draw();
	}

	bool LayerManager::input(const GS::InputNS::Input & a_input, bool & a_moDone, bool & a_kbDone)
	{
		for(int i = 0; i < m_layers.size(); ++i)
			if(m_layers.get(i)->input(a_input, a_moDone, a_kbDone))
				return true; // if both are done, return true;

		return false; // at leat one is not true;
	}

	void LayerManager::update(_DOUBLE a_dt)
	{
		for(int i = 0; i < m_layers.size(); ++i)
			m_layers.get(i)->update(a_dt);
	}

	void LayerManager::shutdown()
	{
		for(int i = 0; i < m_layers.size(); ++i)
			m_layers.get(i)->shutdown();
	}

	void LayerManager::onScreenResize()
	{
		for(int i = 0; i < m_layers.size(); ++i)
			m_layers.get(i)->onScreenResize();
	}

};
};