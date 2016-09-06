#ifndef __QUESTSSTATE_H_
#define __QUESTSSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../menustate.h"

namespace GS {
namespace State {

class QuestsState : public IState<MenuState>
{
#pragma region STATE FUNCTIONALITY
selective :
public:
	virtual _INT32 onEnter(MenuState *);
	virtual _INT32 onUpdate(MenuState *);
	virtual _INT32 onExit(MenuState *);
#pragma endregion

};

};
};

#endif