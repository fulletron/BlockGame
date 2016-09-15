#include "launchpadstate.h"

namespace GS {
namespace State {

_INT32 LaunchPadState::onEnter(DirectorState * a_g)
{
	return 0;
}

_INT32 LaunchPadState::onUpdate(DirectorState * a_dir)
{
	// if menu isn't open
	// Based on DirectorState's current selected mission
	a_dir->getSelectedMission();
	return 0;
}

_INT32 LaunchPadState::onExit(DirectorState * a_g)
{
	return 0;
}

};
};