#include "state.h"
#include "..\..\Input\input.h"

namespace GS { class Game;
namespace InputNS { class Input; };
namespace StateNS {
	void StateBase::update(const _DOUBLE & a_dt)
	{
		m_actorManager.manageUpdate(a_dt);
	}

	void StateBase::render()
	{
		m_actorManager.manageDraw();
	}

	void StateBase::input(GS::InputNS::Input * const a_input)
	{
		m_actorManager.manageInput(a_input);
	}

	void StateBase::shutdown()
	{
		m_actorManager.manageShutdown();
	}

	void StateBase::onScreenResize()
	{
		m_actorManager.manageOnScreenResize();
	}
};
};