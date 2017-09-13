#ifndef __MAINMACHINE_H_
#define __MAINMACHINE_H_

#include <Utilities/definitions_types.h>
#include <Framework/state/statemachine.h>


#include <Framework/referencer/referencer.h>

namespace GS {
namespace Stage {

class MainMachine : public GS::State::StateMachine<MainMachine>
{
IMPLEMENT_CHANGESTATE(MainMachine);

selective:
	_BOOL m_isRunning;
	GS::Referencer * m_pRef;
	GS::Utilities::IInput * m_pInput;
public:
	_UINT32 init(GS::Referencer * a_ref);
	_UINT32 update();
	_UINT32 shutdown();

	_BOOL isRunning();

	GS::Referencer * getReferencer() { return m_pRef; }
};

};
};

#endif