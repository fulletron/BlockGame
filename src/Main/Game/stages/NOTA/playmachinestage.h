#ifndef __PLAYSTAGE_H_
#define __PLAYSTAGE_H_

#include <Utilities/definitions_types.h>
#include "../mainstage.h"

#include <Framework/stage/stage.h>

namespace GS {
namespace Stage {

class PlayStage : public GS::Stage::Stage<MainMachine>
{
public:
	PlayStage();
	~PlayStage();

selective :
	virtual _UINT32 __createActorsAndPanels(_VECTOR<GS::Actor::IActor *> *, _VECTOR<GS::Panel::IPanel *> *);
};


};
};

#endif