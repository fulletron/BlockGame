#ifndef __CHOOSEDISCIPLINESTATE_H_
#define __CHOOSEDISCIPLINESTATE_H_

#include <Utilities/typedefinitions.h>
#include "../charactercreationstate.h"

namespace GS {
namespace State {

class ChooseDisciplineState : public IState<CharacterCreationState>
{
	IMPLEMENT_ISTATE(CharacterCreationState);
};

};
};

#endif