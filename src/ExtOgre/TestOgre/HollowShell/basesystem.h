#ifndef _BASESYSTEM_H_
#define _BASESYSTEM_H_

#include "othreading/messagequeuesystem.h"

// Taken from ogre 2.1 tutorials

namespace OGraphics
{
class IGameState;

class BaseSystem : public Mq::MessageQueueSystem
{
protected:
	IGameState   *mCurrentGameState;

public:
	BaseSystem(IGameState *gameState);
	virtual ~BaseSystem();

	virtual void initialize(void);
	virtual void deinitialize(void);

	virtual void createScene01(void);
	virtual void createScene02(void);

	virtual void destroyScene(void);

	void beginFrameParallel(void);
	void update(float timeSinceLast);
	void finishFrameParallel(void);
	void finishFrame(void);
};
}

#endif