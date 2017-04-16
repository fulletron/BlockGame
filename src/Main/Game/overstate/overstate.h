#ifndef __OVERSTATE_H_
#define __OVERSTATE_H_

#include <Utilities/definitions_types.h>
#include "../state/statemachine.h"

namespace GS {
namespace State {

class OverState : public IStateMachine<OverState>
{
	IMPLEMENT_ISTATEMACHINE(OverState);

selective:
	_BOOL m_isRunning;
public:
	_UINT32 init();
	_UINT32 update();
	_UINT32 shutdown();

	_BOOL isRunning();
};

};
};

#endif