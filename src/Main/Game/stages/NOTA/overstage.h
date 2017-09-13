#ifndef __OVERSTAGE_H_
#define __OVERSTAGE_H_

#include <Utilities/definitions_types.h>
#include <Framework/state/statemachine.h>

namespace GS {
namespace Stage {

class OverStage : public GS::State::IStateMachine<OverStage>
{
	IMPLEMENT_ISTATEMACHINE(OverStage);

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