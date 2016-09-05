#ifndef __STATE_H_
#define __STATE_H_

#include <Utilities/typedefinitions.h>

namespace GS {
namespace State {

template <class T>
class IFSMachine
{
public:
	virtual ~IFSMachine(){}
	virtual IState<T> * getState() = 0;
	virtual void changeState(const IState<T> *) = 0;
};

};
};

#endif