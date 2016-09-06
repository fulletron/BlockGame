#ifndef __SETTINGSSTATE_H_
#define __SETTINGSSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../menustate.h"

namespace GS {
namespace State {

class SettingsState : public IState<MenuState>
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