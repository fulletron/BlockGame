#ifndef __SELECTSTAGE_H_
#define __SELECTSTAGE_H_

#include <Utilities/definitions_types.h>
#include "../overstage.h"
#include <Launchpad/stage/stagetransitioner.h>
#include <Launchpad/stage/ihasstagetransitioner.h>


namespace GS {
namespace Stage {

class SelectStage : public GS::State::IState<OverStage>, public GS::Stage::IHasStageTransitioner
{
	IMPLEMENT_ISTATE(OverStage);
	IMPLEMENT_IHASSTAGETRANSITIONER(OverStage);
};

};
};

#endif