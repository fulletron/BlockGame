#include "entity.h"

namespace GS {
namespace EntityNS {
	/*
		_UINT32 Entity2DGrid::init(GS::Game * const a_rpGame, void const * const a_data)
		{ 
			Builder_Entity2DGrid * t_pBuilder = (Builder_Entity2DGrid *)a_data;

			m_pGame = a_rpGame;
			m_entitiesGrid.resize(t_pBuilder->rows,t_pBuilder->cols,0);
			_UtilitiesNSTable<Entity2D *>::iter iter = m_entitiesGrid.begin();
			while(iter != m_entitiesGrid.end())
			{
				(*iter)->init(a_rpGame, a_data);
				++iter;
			}
			return 0;
		}

		void Entity2DGrid::draw()
		{
			_UtilitiesNSTable<Entity2D *>::iter iter = m_entitiesGrid.begin();
			while(iter != m_entitiesGrid.end())
			{
				(*iter)->draw();
				++iter;
			}
		}

		bool Entity2DGrid::input(const GS::InputNS::Input & a_input, bool & a_moDone, bool & a_kbDone)
		{
			_UtilitiesNSTable<Entity2D *>::iter iter = m_entitiesGrid.begin();
			while(iter != m_entitiesGrid.end())
			{
				(*iter)->input(a_input, a_moDone, a_kbDone);
				++iter;
			}
			return false;
		}

		void Entity2DGrid::update(_DOUBLE a_dt)
		{
			_UtilitiesNSTable<Entity2D *>::iter iter = m_entitiesGrid.begin();
			while(iter != m_entitiesGrid.end())
			{
				(*iter)->update(a_dt);
				++iter;
			}
		}

		void Entity2DGrid::shutdown()
		{
			_UtilitiesNSTable<Entity2D *>::iter iter = m_entitiesGrid.begin();
			while(iter != m_entitiesGrid.end())
			{
				(*iter)->shutdown();
				++iter;
			}
		}

		void Entity2DGrid::onScreenResize()
		{
			_UtilitiesNSTable<Entity2D *>::iter iter = m_entitiesGrid.begin();
			while(iter != m_entitiesGrid.end())
			{
				(*iter)->onScreenResize();
				++iter;
			}
		}

		void Entity2DGrid::entityRescale()
		{
			_UtilitiesNSTable<Entity2D *>::iter iter = m_entitiesGrid.begin();
			while(iter != m_entitiesGrid.end())
			{
				(*iter)->entityRescale();
				++iter;
			}
		}
		*/

};
};