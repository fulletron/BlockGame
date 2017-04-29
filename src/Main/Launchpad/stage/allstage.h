#ifndef __ALLSTAGE_H_
#define __ALLSTAGE_H_

#include <Utilities/definitions_types.h>
#include "../state/statemachine.h"

namespace GS {
namespace Stage {

class AllStage : public GS::State::IStateMachine<AllStage>
{
	IMPLEMENT_ISTATEMACHINE(AllStage);

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