#ifndef __MENUSTATE_H_
#define __MENUSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../characterchosenstate.h"

namespace GS {
namespace State {

class MenuState : public IState<CharacterChosenState>
{
#pragma region STATE FUNCTIONALITY
selective:
public:
	virtual _INT32 onEnter(CharacterChosenState * a_g);
	virtual _INT32 onUpdate(CharacterChosenState * a_g);
	virtual _INT32 onExit(CharacterChosenState * a_g);
#pragma endregion

};

};
};

#endif