#ifndef __CHARACTERCHOSENSTATE_H_
#define __CHARACTERCHOSENSTATE_H_

#include <Utilities/typedefinitions.h>
#include "game.h"

namespace GS {
namespace State {

class CharacterChosenState : public IState<Game>
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

/*
public:
virtual _INT32 init() {}
virtual _INT32 update(double a_dt) {}
virtual _INT32 input() {}
virtual _INT32 render() {}
virtual _INT32 shutdown() {}
*/