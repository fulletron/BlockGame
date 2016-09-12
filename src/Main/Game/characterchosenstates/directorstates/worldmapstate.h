#ifndef __WORLDMAPSTATE_H_
#define __WORLDMAPSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../directorstate.h"

namespace GS {
namespace State {

class WorldMapState : public IState<DirectorState>
{
#pragma region STATE FUNCTIONALITY
	typedef DirectorState CURRENT_ISTATE_TEMPLATE;
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