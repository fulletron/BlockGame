#include "playstage.h"

// Target states

#include "Utilities/input/iinput.h"
extern GS::Utilities::IInput * g_pInput;

namespace GS {
namespace Stage {

PlayStage::PlayStage()
{
}

PlayStage::~PlayStage()
{
}

_UINT32 PlayStage::__createActorsAndPanels(_VECTOR<GS::Actor::IActor *> * this_requiredActors, _VECTOR<GS::Panel::IPanel *> * this_panels)
{
	GS::Actor::IActor * test_actor = new GS::Actor::TestActor();

	// Create all of the panels for this stage
	GS::Panel::IPanel * test_panel = new GS::Panel::TestPanel();

	// push all of the actors into their appropriate panels.
	test_panel->getActors()->push_back(test_actor);

	// push all of the created panels into the stages list of panels
	this_panels->push_back(test_panel);

	// Tell the stage which actors are REQUIRED before the stage can
	// transition in.
	this_requiredActors->push_back(test_actor);

	return 0;
}

};
};