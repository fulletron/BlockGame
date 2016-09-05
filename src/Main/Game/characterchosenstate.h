#ifndef __STATE_H_
#define __STATE_H_

#include <Utilities/typedefinitions.h>

namespace GS {
namespace State {

class CharacterChosenState : public IState<Game>
{
selective:
public:
	virtual _INT32 onEnter(Game * a_g)
	{
		return 0;
	}

	virtual _INT32 onUpdate(Game * a_g, double a_dt)
	{
		return 0;
	}

	virtual _INT32 onExit(Game * a_g)
	{
		return 0;
	}

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