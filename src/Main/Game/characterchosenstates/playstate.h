#ifndef __PLAYSTATE_H_
#define __PLAYSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../characterchosenstate.h"

namespace GS {
namespace State {

class PlayState : public IState<CharacterChosenState>
{
#pragma region STATE FUNCTIONALITY
selective :
public:
	virtual _INT32 onEnter(CharacterChosenState * a_g);
	virtual _INT32 onUpdate(CharacterChosenState * a_g);
	virtual _INT32 onExit(CharacterChosenState * a_g);
#pragma endregion

};

};
};

#endif