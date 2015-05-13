#ifndef __STATE_H_
#define __STATE_H_

#include <Utilities/typedefinitions.h>

namespace GS {
namespace State {

class IState
{
public:
	virtual _INT32 init() = 0;
	virtual _INT32 update(double a_dt) = 0;
	virtual _INT32 input() = 0;
	virtual _INT32 render() = 0;
	virtual _INT32 shutdown() = 0;
};

};
};

#endif