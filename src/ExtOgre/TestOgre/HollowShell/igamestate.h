#ifndef _IGAMESTATE_H_
#define _IGAMESTATE_H_

#include "iinputlisteners.h"

namespace OGraphics
{
/*
* The Basis of Game Objects (Scene Nodes, and the like).
*/
class IGameState : public IMouseListener, public IKeyboardListener, public IJoystickListener
{
public:
	virtual ~IGameState() {}

	virtual void initialize(void) {}
	virtual void deinitialize(void) {}

	virtual void createScene01(void) {}
	virtual void createScene02(void) {}

	virtual void destroyScene(void) {}

	virtual void update(float timeSinceLast) {}
	virtual void finishFrameParallel(void) {}
	virtual void finishFrame(void) {}
};
};

#endif