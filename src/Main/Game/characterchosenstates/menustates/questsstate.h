#ifndef __QUESTSSTATE_H_
#define __QUESTSSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../menustate.h"

namespace GS {
namespace State {

class QuestsState : public IState<MenuState>
{
#pragma region STATE FUNCTIONALITY
	typedef MenuState CURRENT_ISTATE_TEMPLATE;
	// This is itself a state for the CURRENT_ISTATE_TEMPLATE State Machine.
selective:
public:
	virtual _INT32 onEnter(CURRENT_ISTATE_TEMPLATE *);
	virtual _INT32 onUpdate(CURRENT_ISTATE_TEMPLATE *);
	virtual _INT32 onExit(CURRENT_ISTATE_TEMPLATE *);
#pragma endregion

};

};
};

#endif