#ifndef __TEST2STAGE_H_
#define __TEST2STAGE_H_

#include <Utilities/definitions_types.h>
#include "../allstage.h"
#include "../../stage/stagetransitioner.h"

namespace GS {
namespace Stage {

class Test2Stage : public GS::State::IState<AllStage>, public GS::Transition::IHasTransitioner
{
	IMPLEMENT_ISTATE(AllStage);
	IMPLEMENT_IHASTRANSITIONER(AllStage);
};

};
};

#endif