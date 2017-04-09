#ifndef __CHOOSELOOKSSTATE_H_
#define __CHOOSELOOKSSTATE_H_

#include <Utilities/typedefinitions.h>
#include "../charactercreationstate.h"

namespace GS {
namespace State {

class ChooseLooksState : public IState<CharacterCreationState>
{
	IMPLEMENT_ISTATE(CharacterCreationState);
};

};
};

#endif