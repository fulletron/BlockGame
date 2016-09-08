#ifndef __CHARACTERSELECTSTATE_H_
#define __CHARACTERSELECTSTATE_H_

#include <Utilities/typedefinitions.h>
#include "state.h"
#include "game.h"

namespace GS {
namespace State  {

class CharacterSelectState : public IState<Game> //GS::State::IState<Game>
{
#pragma region STATE FUNCTIONALITY
	typedef Game CURRENT_ISTATE_TEMPLATE;
	// This is itself a state for the CURRENT_ISTATE_TEMPLATE State Machine.
selective:
public:
	virtual _INT32 onEnter(CURRENT_ISTATE_TEMPLATE *);
	virtual _INT32 onUpdate(CURRENT_ISTATE_TEMPLATE *);
	virtual _INT32 onExit(CURRENT_ISTATE_TEMPLATE *);
#pragma endregion

};

};
};
#endif