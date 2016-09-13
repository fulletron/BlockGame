#ifndef __GAME_H_
#define __GAME_H_

#include <Utilities/typedefinitions.h>
#include "statemachine.h"

namespace GS {

class Game : public State::IStateMachine<Game>
{
selective:
	// I also will need a second thread for loading/unloading
	// This second thread needs to talk to opengl to share contexts
	// if I don't want my game knowing about opengl, then I can't put it here.

	// Because of my fsm, i can't chain pass the dt unless all FSMs 
	// have dt in their update. Best to just save it at the top and 
	// access it when necessary
	_DOUBLE dt;

public:
	// SET the initial state. load basic loading screen assets.
	_INT32 init();

// =============== BASIC LOOP ======================
public:
	void draw ();
	void input ();
	void update (const _DOUBLE a_dt)
	{
		dt = a_dt;
		m_pCurrentState->onUpdate(this);
	}
// ==================================================

	IMPLEMENT_ISTATEMACHINE(Game);
};

};

#endif