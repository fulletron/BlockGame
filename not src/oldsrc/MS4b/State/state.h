#ifndef __STATE_H_
#define __STATE_H_

#include "..\..\Game\definitions.h"
#include "Graphics\actor.h"


namespace GS { class Game;
namespace InputNS { class Input; };
namespace StateNS {
	class IState
	{
	public:
		virtual _UINT32 init(GS::Game*) = 0;
		virtual void update(const _DOUBLE & dt) = 0;
		virtual void render() = 0;
		virtual void input(GS::InputNS::Input * const) = 0;
		virtual void shutdown() = 0;
		virtual void onScreenResize() = 0;
	};

	class StateBase : public IState
	{
	protected:
		GS::Game *							m_rpGame;
		GS::GraphicsNS::ActorManager		m_actorManager;
	public:
		StateBase()
		: m_rpGame(0)
		{}

		virtual _UINT32 init(GS::Game*) = 0;
		void update(const _DOUBLE & dt);
		void render();
		void input(GS::InputNS::Input * const a_input);
		void shutdown();
		void onScreenResize();
	};

};
};
#endif