#ifndef _GAMEENTITYMANAGER_H_
#define _GAMEENTITYMANAGER_H_

#include "othreading/messagequeuesystem.h"
#include "gameents/gameentity.h"

namespace OGraphics
{

class GraphicsSystem;
class LogicSystem;

class GameEntityManager
{
public:
	struct CreatedGameEntity
	{
		GameEntity *pGameEntity;
//		GameEntityTransform initialTransform;
	};

	typedef std::vector<GameEntityVec> GameEntityVecVec;
private:
	/*
	* a Region is a struct of information
	* regarding a matching(?) slot in the
	* mTransformBuffers that is currently
	* unused
	*/
	struct Region
	{
		size_t slotOffset;
		size_t count;
		size_t bufferIdx;

		Region(size_t _slotOffset, size_t _count, size_t _bufferIdx) :
			slotOffset(_slotOffset),
			count(_count),
			bufferIdx(_bufferIdx)
		{
		}
	};

	//We assume mCurrentId never wraps
	Ogre::uint32    mCurrentId;
	GameEntityVec   mGameEntities[Ogre::NUM_SCENE_MEMORY_MANAGER_TYPES];

	// This is just a way to minimize the new/delete functions.
	// Game entities will have a pointer to a place in mTransformBuffers
//	std::vector<GameEntityTransform*>   mTransformBuffers;
//	std::vector<Region>                 mAvailableTransforms;

	GameEntityVecVec    mScheduledForRemoval;
	size_t              mScheduledForRemovalCurrentSlot;
	std::vector<size_t> mScheduledForRemovalAvailableSlots;

	Mq::MessageQueueSystem  *mGraphicsSystem;
	LogicSystem             *mLogicSystem;

	Ogre::uint32 getScheduledForRemovalAvailableSlot(void);
	void destroyAllGameEntitiesIn(GameEntityVec &container);

	/*
	* Acquires the last element in mAvailableTransforms and
	* returns the slot and bufferId which corresponds to an
	* index in the mTransformBuffers List
	*/
//	void aquireTransformSlot(size_t &outSlot, size_t &outBufferIdx);
//	void releaseTransformSlot(size_t bufferIdx, GameEntityTransform *transform);

public:
	GameEntityManager(Mq::MessageQueueSystem *graphicsSystem,
		LogicSystem *logicSystem);

	~GameEntityManager();

	/*
	* Adds a newly created game entity to the manager, scheduling for graphics to be updated
	*/
	void addGameEntity(GameEntity * pGameEntity);

	/*
	* Adds a newly created game entity to the manager, scheduling for graphics to be updated
	*/
/*
	void addGameEntity(
		GameEntity *gameEntity, 
		const GameEntityTransform & initialTransform);
*/

	/** Creates a GameEntity, adding it to the world, and scheduling for the Graphics
	thread to create the appropiate SceneNode and Item pointers.
	MUST BE CALLED FROM LOGIC THREAD.
	@param type
	Whether this GameEntity is dynamic (going to change transform frequently), or
	static (will move/rotate/scale very, very infrequently)
	@param initialPos
	Starting position of the GameEntity
	@param initialRot
	Starting orientation of the GameEntity
	@param initialScale
	Starting scale of the GameEntity
	@return
	Pointer of GameEntity ready to be used by the Logic thread. Take in mind
	not all of its pointers may filled yet (the ones that are not meant to
	be used by the logic thread)
	*/
/* ORIG
	GameEntity* addGameEntity(Ogre::SceneMemoryMgrTypes type,
		const MovableObjectDefinition *moDefinition,
		const Ogre::Vector3 &initialPos,
		const Ogre::Quaternion &initialRot,
		const Ogre::Vector3 &initialScale);
*/

	/** Removes the GameEntity from the world. The pointer is not immediately destroyed,
	we first need to release data in other threads (i.e. Graphics).
	It will be destroyed after the Render thread confirms it is done with it
	(via a Mq::GAME_ENTITY_SCHEDULED_FOR_REMOVAL_SLOT message)
	*/
	void removeGameEntity(GameEntity *toRemove);

	/// Must be called by LogicSystem when Mq::GAME_ENTITY_SCHEDULED_FOR_REMOVAL_SLOT message arrives
	void _notifyGameEntitiesRemoved(size_t slot);

	/// Must be called every frame from the LOGIC THREAD.
	void finishFrameParallel(void);

	// returns a valid id, and increases the current ID
	Ogre::uint32 popAssignableId(void);
};
};

#endif