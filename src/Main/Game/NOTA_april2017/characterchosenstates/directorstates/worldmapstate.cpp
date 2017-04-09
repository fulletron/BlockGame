#include "worldmapstate.h"

namespace GS {
namespace State {

_INT32 WorldMapState::onEnter(DirectorState * a_g)
{
	return 0;
}

_INT32 WorldMapState::onUpdate(DirectorState * a_g)
{
// if the menu is not open,
	// Add all the World Map displayables to the displaylist
	// Handle input
	// DISMISS - changestate to WorldMapState
	// MISSION_SELECT - changestate to 

// if menu is open
	// do nothing?

	return 0;
}

_INT32 WorldMapState::onExit(DirectorState * a_g)
{
	return 0;
}

};
};