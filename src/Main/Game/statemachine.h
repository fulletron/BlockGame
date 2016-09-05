#ifndef __STATEMACHINE_H_
#define __STATEMACHINE_H_

#include <Utilities/typedefinitions.h>
#include "state.h"

namespace GS {
namespace State {

template <class T>
class IStateMachine
{
public:
	virtual ~IStateMachine(){}
	virtual IState<T> * getState() = 0;
	virtual void changeState(const IState<T> *) = 0;
};

};
};

#endif