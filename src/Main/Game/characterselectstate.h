#ifndef __CHARACTERSELECTSTATE_H_
#define __CHARACTERSELECTSTATE_H_

#include <Utilities/typedefinitions.h>
#include "state.h"
#include "game.h"

namespace GS {
namespace State {

class CharacterSelectState : public GS::State::IState<Game>
{
selective:
public:
	virtual _INT32 onEnter(Game * a_g);
	virtual _INT32 onUpdate(Game * a_g);
	virtual _INT32 onExit(Game * a_g);
};

};
};

#endif