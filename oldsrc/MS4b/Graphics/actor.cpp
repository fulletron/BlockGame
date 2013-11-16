#include "actor.h"

namespace GS {
namespace GraphicsNS {

	_UINT32 ActorManager::init(GS::Game * const a_rpGame)
	{
		m_rpGame = a_rpGame;
		sortActors();

		return 0;
	}

	void ActorManager::manageDraw()
	{
		for(int i = m_actors.size() - 1; i >= 0; --i)
			m_actors.get(i)->draw();
	}

	bool ActorManager::manageInput(GS::InputNS::Input * const a_input)
	{
		for(int i = 0; i < m_actors.size(); ++i)
			m_actors.get(i)->input(a_input);
		return false;
	}

	void ActorManager::manageUpdate(const _DOUBLE & a_dt)
	{
		for(int i = 0; i < m_actors.size(); ++i)
			m_actors.get(i)->update(a_dt);
	}

	void ActorManager::manageShutdown()
	{
		for(int i = 0; i < m_actors.size(); ++i)
			m_actors.get(i)->shutdown();
	}

	void ActorManager::sortActors()
	{
		if(m_actors.size() > 1)
			m_actors.sort(__sortAlgorithm);
	}

	bool ActorManager::__sortAlgorithm(void * a1, void * a2)
	{
		IActor * d1 = (IActor *)a1;
		IActor * d2 = (IActor *)a2;
		return d1->getFocus() > d2->getFocus();
	}

	void ActorManager::manageOnScreenResize()
	{
		for(int i = 0; i < m_actors.size(); ++i)
			m_actors.get(i)->onScreenResize();
	}

	void ActorManager::addActor(IActor * const a_pActor)
	{
		m_actors.add(a_pActor);
	}

	void ActorManager::removeActor(IActor * const a_pActor)
	{
		/// KYLE :: THIS MIGHT NOT REMOVE THE DATA! BE SURE TO FIX THIS!
		m_actors.removeData(a_pActor);
	}

};
};