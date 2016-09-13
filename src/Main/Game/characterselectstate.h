#ifndef __CHARACTERSELECTSTATE_H_
#define __CHARACTERSELECTSTATE_H_

#include <Utilities/typedefinitions.h>
#include "state.h"
#include "game.h"

namespace GS {
namespace State  {

class CharacterSelectState : public IState<Game>
{
	IMPLEMENT_ISTATE(Game);
};

};
};
#endif