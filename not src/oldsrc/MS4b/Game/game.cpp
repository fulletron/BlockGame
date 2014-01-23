#include "game.h"
#include "inlines.h"

#include <State\menustate.h>
#include <Entity\entity.h>

namespace GS 
{
	_UINT32 Game::init()
	{
		m_pState = 0;
		/// set the game to running
		/// when running becomes false, the gameLoop in winmain ends
		m_running = true;

		/// init the graphics
		if(DBC(m_graphics.init(this), "FAILED TO INIT GRAPHICS"))
			return -1;

		/// RENDER A BLACK SCREEN
		GraphicsNS::render(this);
		/// INITIALIZE THE RESOURCE LIBRARY (NOT STATE BASED)
		if(DBC(m_library.init(this), "FAILED TO INIT THE RESOURCE LIBRARY"))
			return -2;
		/// Load A State
		m_pState = new GS::StateNS::MenuState();
		if(DBC(m_pState->init(this), "FAILED TO INIT STATE"))
			return -3;
		/// init the load screen vars
		//if(loadLib.initLoadingResources())
		//	return -3;

		/// draw the loading screen
		//graphics.render(p_ls);

		/// init the input
		if(DBC(m_input.init(this), "FAILED TO INIT INPUT"))
			return -4;
		/// init the initial state

		return 0;
	}

	void Game::render()
	{
		GraphicsNS::render(this);
		/// give the state to the graphics
	}

	void Game::input()
	{
		/// give the state to the input? NO!
		/// GIVE THE INPUT TO THE STATE!
		m_input.grabInput();
		m_pState->input(&m_input);
	}

	//void Game::update(const _UINT32 & a_time)
	void Game::update(const _DOUBLE & a_time)
	{
		m_lifetime += a_time;
		m_thisTickDelta = a_time;
		m_pState->update(a_time);
	}

	void Game::shutdown()
	{
		m_graphics.shutdown();
		m_input.shutdown();
		m_pState->shutdown();
		delete m_pState;
	}

	void Game::flagForQuit()
	{
		m_running = false;
	}

	bool LoadState(Game * const a_g, const IState & a_state)
	{
		return true;
	}

};