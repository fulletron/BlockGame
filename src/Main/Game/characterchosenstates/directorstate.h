#ifndef __DIRECTORSTATE_H_
#define __DIRECTORSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../characterchosenstate.h"

namespace GS {
namespace State {

class DirectorState : public IState<CharacterChosenState>
{
#pragma region STATE FUNCTIONALITY
	typedef CharacterChosenState CURRENT_ISTATE_TEMPLATE;
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