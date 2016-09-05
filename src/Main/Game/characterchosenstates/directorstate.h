#ifndef __DIRECTORSTATE_H_
#define __DIRECTORSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../characterchosenstate.h"

namespace GS {
namespace State {

class DirectorState : public IState<CharacterChosenState>
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