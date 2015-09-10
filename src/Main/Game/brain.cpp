#include "brain.h"

namespace GS { 
namespace Game {

void Brain::shutdown()
{

}

/**
* Determines how to handle input for the PaneAsset
*/
//_BOOL handleInput();

/**
* Updates all game logic by a_dt
*/
void Brain::update(const _DOUBLE a_dt)
{
	m_fpsCounter.update(a_dt);
}

/**
* Init the brain
*/
_INT32 Brain::init ()
{
	m_fpsCounter.init();
	return 0;
}

};
};
