#ifndef _LOGICSYSTEM_H_
#define _LOGICSYSTEM_H_

#include "basesystem.h"
#include "OgrePrerequisites.h"
#include "sdl_events.h"

namespace OGraphics
{
class GameEntityManager;

class LogicSystem : public BaseSystem
{
protected:
	BaseSystem *mpGraphicsSystem;
	GameEntityManager *mpGameEntityManager;
	IGameState * mpLogicGameState;

	static Ogre::uint32 mCurrentTransformIdx;
	std::deque<Ogre::uint32> mAvailableTransformIdx;

	virtual void processIncomingMessage( Mq::MessageId messageId, const void *data );

public:
	LogicSystem( IGameState * gameState );
	virtual ~LogicSystem();

	void _notifyGraphicsSystem(BaseSystem * graphicsSystem) { mpGraphicsSystem = graphicsSystem; }
	void _notifyGameEntityManager(GameEntityManager * mgr) { mpGameEntityManager = mgr; }
	void _notifyLogicGameState(IGameState * pLogicGameState) { mpLogicGameState = pLogicGameState; }

	void finishFrameParallel(void);

	GameEntityManager * getGameEntityManager(void) { return mpGameEntityManager; }
	static const Ogre::uint32 getCurrentTransformIdx(void) /* const */ { return mCurrentTransformIdx; }

	/* KYLE :: ADD :: 
	* Handle the input on the logic side.
	*/
	void handleInput(const SDL_Event & evt);
};

};

#endif