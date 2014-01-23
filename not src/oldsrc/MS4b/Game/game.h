#ifndef __GAME_H_
#define __GAME_H_

#include "definitions.h"
#include <Graphics\graphics.h>
#include <Input\input.h>
#include <Utilities\Table.h>
#include <State\state.h>
#include <Library\library.h>

class IState;

namespace GS
{
	static EventNS::EventDictionary * g_events;

	class Game
	{
	private:
		bool						m_running;
		_DOUBLE						m_lifetime;
		_DOUBLE						m_thisTickDelta;

		GraphicsNS::Graphics		m_graphics;
		InputNS::Input				m_input;
		StateNS::IState *			m_pState;
		LibraryNS::Library			m_library;

	public:
		Game() :	m_running(false), 
					m_lifetime(0), 
					m_thisTickDelta(0) 
		{}
		~Game(){}
	
		_UINT32		init();
		void		render();
		void		input();
		void		update(const _DOUBLE & a_time);
		void		shutdown();

		bool		isRunning(){return m_running;}
		void		flagForQuit();

		GraphicsNS::Graphics * getGraphics(){return &m_graphics;}
		InputNS::Input * getInput(){return &m_input;}
		StateNS::IState * getState(){return m_pState;}
		LibraryNS::Library * getLibrary(){return &m_library;}
	};

	bool LoadState(Game * const a_g, const IState & a_state);

};

#endif