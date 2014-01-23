#include "entitymanager.h"
#include "entity.h"

namespace GS {
namespace EntityNS {
	/*
	_UINT32 EntityManager::init(GS::Game * const a_rpGame)
	{
		m_rpGame = a_rpGame;

		/// ENTITIES ARE ALREADY INITED BY THIS TIME. NO NEED TO GO THROUGH m_allEntities AND INIT THEM ALL!

		return 0;
	}
	void EntityManager::render()
	{
		for(int i = 0; i < m_allEntities.size(); ++i)
			m_allEntities.get(i)->draw();
	}
	void EntityManager::input(const GS::InputNS::Input & a_input, bool & a_moDone, bool & a_kbDone)
	{
		for(int i = 0; i < m_allEntities.size(); ++i)
			m_allEntities.get(i)->input(a_input, a_moDone, a_kbDone);
	}
	void EntityManager::update(_DOUBLE a_dt)
	{
		for(int i = 0; i < m_allEntities.size(); ++i)
			m_allEntities.get(i)->update(a_dt);
	}
	void EntityManager::shutdown()
	{
		for(int i = 0; i < m_allEntities.size(); ++i)
			m_allEntities.get(i)->shutdown();
	}
	void EntityManager::onScreenResize()
	{
		for(int i = 0; i < m_allEntities.size(); ++i)
			m_allEntities.get(i)->onScreenResize();
	}

	void EntityManager::addEntity(Entity * const a_pEntity)
	{
		m_allEntities.add(a_pEntity);
	}

	void EntityManager::removeEntity(Entity * const a_pEntity)
	{
		/// KYLE :: THIS MIGHT NOT REMOVE THE DATA! BE SURE TO FIX THIS!
		m_allEntities.removeData(a_pEntity);
	}
	*/
};
};