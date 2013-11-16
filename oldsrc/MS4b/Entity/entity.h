#ifndef __ENTITY_H_
#define __ENTITY_H_

#include "..\..\Game\definitions.h"
#include "..\..\Utilities\Table.h"
#include <Graphics\actor.h>

namespace GS { class Game;
namespace InputNS { class Input; };
namespace EntityNS {

	static _UINT32 s_latestID = 1;

	class Entity : public GS::GraphicsNS::ActorBase
	{
	public:
		virtual void setID() = 0;
		virtual _UINT32 getID() = 0;
		virtual _UINT32 getNetID() = 0;
	};

	class EntityBase : public Entity
	{
	protected:
		GS::Game *			m_rpGame;
		_UINT32				m_id, m_netId;

	public:
		void setID(){m_id = GS::EntityNS::s_latestID++;}
		_UINT32 getNetID(){return m_netId;}
		_UINT32 getID(){return m_id;}
	};

	class Entity2D : public EntityBase
	{
	protected:
		_2DFLOATVEC			m_position, 
							m_scale, 
							m_rotation;
		_RECT<_INT32>		m_srcRect;
	public:
		_2DFLOATVEC getPos(){return m_position;}
		_2DFLOATVEC getScale(){return m_scale;}
		_2DFLOATVEC getRot(){return m_rotation;}
		void setPos(const _2DFLOATVEC & a_pos){ m_position = a_pos; }
		void setScale(const _2DFLOATVEC & a_scale){ m_scale = a_scale; }
		void setRot(const _2DFLOATVEC & a_rot){ m_rotation = a_rot; }
		void addPos(const _2DFLOATVEC & a_pos){ m_position += a_pos; }
		void addScale(const _2DFLOATVEC & a_scale){ m_scale += a_scale;}
		void addRot(const _2DFLOATVEC & a_rot){ m_rotation += a_rot; }

		void setSrcRect(const _RECT<_INT32> & a_rect){ m_srcRect = a_rect; }
		_RECT<_INT32> getSrcRect(){ return m_srcRect;}
	};

	/*
	class Entity3D : public Entity
	{
	protected:
		GS::Game *			m_rpGame;
		_3DFLOATVEC			m_position, m_scale, m_rotation;
		_UINT32				m_id, m_netId;
		float				m_opacity;		
	public:
		//virtual _UINT32 init(GS::Game * const a_rpGame, void const * const a_data) = 0;
		virtual void draw() = 0;
		virtual bool input(const GS::InputNS::Input & a_input, bool &, bool &) = 0;
		virtual void update(_DOUBLE a_dt) = 0;
		virtual void shutdown() = 0;
		virtual void onScreenResize() = 0;
		//virtual void entityRescale() = 0;

		void setID(){m_id = GS::EntityNS::s_latestID++;}
		_UINT32 getNetID(){return m_netId;}
		_UINT32 getID(){return m_id;}
		float getOpacity() const {return m_opacity;}
		_3DFLOATVEC getPos(){return m_position;}
		_3DFLOATVEC getScale(){return m_scale;}
		_3DFLOATVEC getRot(){return m_rotation;}
		void setPos(const _3DFLOATVEC & a_pos){ m_position = a_pos; }
		void setScale(const _3DFLOATVEC & a_scale){ m_scale = a_scale; }
		void setRot(const _3DFLOATVEC & a_rot){ m_rotation = a_rot; }
		void addPos(const _3DFLOATVEC & a_pos){ m_position += a_pos; }
		void addScale(const _3DFLOATVEC & a_scale){ m_scale += a_scale;}
		void addRot(const _3DFLOATVEC & a_rot){ m_rotation += a_rot; }
	};
	*/
};
};

#endif