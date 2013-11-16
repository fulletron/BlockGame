#include "layer.h"

namespace GS { 
namespace PanelNS {

	void LayerBase::draw()
	{
		m_entityManager.render();
	}
	bool LayerBase::input(const GS::InputNS::Input & a_input, bool & a_moDone, bool & a_kbDone)
	{
		m_entityManager.input(a_input, a_moDone, a_kbDone);
		return false;
	}
	void LayerBase::update(_DOUBLE a_dt)
	{
		m_entityManager.update(a_dt);
	}
	void LayerBase::shutdown()
	{
		m_entityManager.shutdown();
	}
	void LayerBase::onScreenResize()
	{
		m_entityManager.onScreenResize();
	}

};
};