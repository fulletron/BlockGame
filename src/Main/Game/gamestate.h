#ifndef __STATE_H_
#define __STATE_H_

#include <Utilities/typedefinitions.h>

namespace GS {
namespace State {

template <class T>
class IState
{
public:
	virtual ~IState(){}
	virtual _INT32 onEnter(T *) = 0;
	virtual _INT32 onUpdate(T *) = 0;
	virtual _INT32 onExit(T *) = 0;
};

/*
class IGameState
{
public:
	virtual ~IGameState(){}

	virtual _INT32 onEnter( Game * a_g ) = 0;
	virtual _INT32 onUpdate( Game * a_g) = 0;
	virtual _INT32 onExit( Game * a_g ) = 0;
};
*/

};
};

#endif