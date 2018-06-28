#include "gameentitymanager.h"
#include "gameents/gameentity.h"

#include "logicsystem.h"

namespace OGraphics
{
	const size_t cNumTransforms = 250;

	GameEntityManager::GameEntityManager(Mq::MessageQueueSystem *graphicsSystem,
		LogicSystem *logicSystem) :
		mCurrentId(0),
		mScheduledForRemovalCurrentSlot((size_t)-1),
		mGraphicsSystem(graphicsSystem),
		mLogicSystem(logicSystem)
	{
		mLogicSystem->_notifyGameEntityManager(this);
	}
	//-----------------------------------------------------------------------------------
	GameEntityManager::~GameEntityManager()
	{
		mLogicSystem->_notifyGameEntityManager(0);

		{
			GameEntityVecVec::iterator itor = mScheduledForRemoval.begin();
			GameEntityVecVec::iterator end = mScheduledForRemoval.end();
			while (itor != end)
				destroyAllGameEntitiesIn(*itor++);
			mScheduledForRemoval.clear();
			mScheduledForRemovalAvailableSlots.clear();
		}

		destroyAllGameEntitiesIn(mGameEntities[Ogre::SCENE_DYNAMIC]);
		destroyAllGameEntitiesIn(mGameEntities[Ogre::SCENE_STATIC]);
/*
		std::vector<GameEntityTransform*>::const_iterator itor = mTransformBuffers.begin();
		std::vector<GameEntityTransform*>::const_iterator end = mTransformBuffers.end();

		while (itor != end)
		{
			OGRE_FREE_SIMD(*itor, Ogre::MEMCATEGORY_SCENE_OBJECTS);
			++itor;
		}

		mTransformBuffers.clear();
		mAvailableTransforms.clear();
*/
	}

	//-----------------------------------------------------------------------------------
	void GameEntityManager::addGameEntity(GameEntity * pGameEntity)
	{
		// Add the new entity to the appropriate entitymanager list
		mGameEntities[pGameEntity->mSceneType].push_back(pGameEntity);

		//CreatedGameEntity * pCGE = new CreatedGameEntity();
		//pCGE->pGameEntity = pGameEntity;

		// Notify the graphics system that a game entity was added.
//		mLogicSystem->queueSendMessage(mGraphicsSystem, Mq::GAME_ENTITY_ADDED, pCGE);
		mLogicSystem->queueSendMessage(mGraphicsSystem, Mq::GAME_ENTITY_ADDED, pGameEntity);

		// KYLE :: THERE DOESN'T APPEAR TO BE A REASON TO CALL onGameEntityAdd();
		pGameEntity->onGameEntityAdd();
	}

/*
	//-----------------------------------------------------------------------------------
	void GameEntityManager::addGameEntity(GameEntity *gameEntity, const GameEntityTransform & initialTransform)
	{
		// Fill in the CGE struct with information that was passed in.
		CreatedGameEntity cge;
		cge.gameEntity = gameEntity;
		cge.initialTransform.vPos = initialTransform.vPos;
		cge.initialTransform.qRot = initialTransform.qRot;
		cge.initialTransform.vScale = initialTransform.vScale;

		//// acquire a slot that is available
		//size_t slot, bufferIdx;
		//aquireTransformSlot(slot, bufferIdx);

		//gameEntity->mTransformBufferIdx = bufferIdx;

		//// Assign the mTransforms to the gameEntity
		//for (int i = 0; i < NUM_GAME_ENTITY_BUFFERS; ++i)
		//{
		//	gameEntity->mTransform[i] = mTransformBuffers[bufferIdx] + slot + cNumTransforms * i;
		//	memcpy(gameEntity->mTransform[i], &cge.initialTransform, sizeof(GameEntityTransform));
		//}

		// Add the new entity to the appropriate entitymanager list
		mGameEntities[gameEntity->mSceneType].push_back(gameEntity);

		// Notify the graphics system that a game entity was added.
		mLogicSystem->queueSendMessage(mGraphicsSystem, Mq::GAME_ENTITY_ADDED, cge);


		// KYLE :: THERE DOESN'T APPEAR TO BE A REASON TO CALL onGameEntityAdd();
		gameEntity->onGameEntityAdd();
	}
*/
	/*
	//-----------------------------------------------------------------------------------
	GameEntity* GameEntityManager::addGameEntity(Ogre::SceneMemoryMgrTypes type,
	const MovableObjectDefinition *moDefinition,
	const Ogre::Vector3 &initialPos,
	const Ogre::Quaternion &initialRot,
	const Ogre::Vector3 &initialScale)
	{
	// Create a new GameEntity with the passed in information.
	GameEntity *gameEntity = new GameEntity(mCurrentId++, moDefinition, type);

	// Fill in the CGE struct with information that was passed in.
	CreatedGameEntity cge;
	cge.gameEntity = gameEntity;
	cge.initialTransform.vPos = initialPos;
	cge.initialTransform.qRot = initialRot;
	cge.initialTransform.vScale = initialScale;

	// acquire a slot that is available
	size_t slot, bufferIdx;
	aquireTransformSlot(slot, bufferIdx);


	gameEntity->mTransformBufferIdx = bufferIdx;
	// Assign the mTransforms to the gameEntity
	for (int i = 0; i<NUM_GAME_ENTITY_BUFFERS; ++i)
	{
	gameEntity->mTransform[i] = mTransformBuffers[bufferIdx] + slot + cNumTransforms * i;
	memcpy(gameEntity->mTransform[i], &cge.initialTransform, sizeof(GameEntityTransform));
	}

	// Add the new entity to the appropriate entitymanager list
	mGameEntities[type].push_back(gameEntity);

	// Notify the graphics system that a game entity was added.
	mLogicSystem->queueSendMessage(mGraphicsSystem, Mq::GAME_ENTITY_ADDED, cge);

	return gameEntity;
	}
	*/
	//-----------------------------------------------------------------------------------
	void GameEntityManager::removeGameEntity(GameEntity *toRemove)
	{
		Ogre::uint32 slot = getScheduledForRemovalAvailableSlot();
		mScheduledForRemoval[slot].push_back(toRemove);
		GameEntityVec::iterator itor = std::lower_bound(mGameEntities[toRemove->mSceneType].begin(),
			mGameEntities[toRemove->mSceneType].end(),
			toRemove, GameEntity::OrderById);
		assert(itor != mGameEntities[toRemove->mSceneType].end() && *itor == toRemove);
		mGameEntities[toRemove->mSceneType].erase(itor);
		mLogicSystem->queueSendMessage(mGraphicsSystem, Mq::GAME_ENTITY_REMOVED, toRemove);
	}
	//-----------------------------------------------------------------------------------
	void GameEntityManager::_notifyGameEntitiesRemoved(size_t slot)
	{
		destroyAllGameEntitiesIn(mScheduledForRemoval[slot]);

		mScheduledForRemoval[slot].clear();
		mScheduledForRemovalAvailableSlots.push_back(slot);
	}
	//-----------------------------------------------------------------------------------
	void GameEntityManager::destroyAllGameEntitiesIn(GameEntityVec &container)
	{
		GameEntityVec::const_iterator itor = container.begin();
		GameEntityVec::const_iterator end = container.end();

		while (itor != end)
		{
			(*itor)->onGameEntityRemove();
//			releaseTransformSlot((*itor)->mTransformBufferIdx, (*itor)->mTransform[0]);
			delete *itor;
			++itor;
		}
	}
	//-----------------------------------------------------------------------------------
/*
	void GameEntityManager::aquireTransformSlot(size_t &outSlot, size_t &outBufferIdx)
	{
		// If there never have been available transforms
		if (mAvailableTransforms.empty())
		{
			// Create a buffer to put in the transformBuffers list.
			GameEntityTransform *buffer = reinterpret_cast<GameEntityTransform*>(OGRE_MALLOC_SIMD(
				sizeof(GameEntityTransform) * cNumTransforms * NUM_GAME_ENTITY_BUFFERS,
				Ogre::MEMCATEGORY_SCENE_OBJECTS));
			mTransformBuffers.push_back(buffer);
			// put a matching region in the region list that describes where the transform buffer is
			mAvailableTransforms.push_back(Region(0, cNumTransforms, mTransformBuffers.size() - 1));
		}

		Region &region = mAvailableTransforms.back();
		outSlot = region.slotOffset++;
		--region.count;
		outBufferIdx = region.bufferIdx;

		if (region.count == 0)
			mAvailableTransforms.pop_back();
	}
	//-----------------------------------------------------------------------------------
	void GameEntityManager::releaseTransformSlot(size_t bufferIdx, GameEntityTransform *transform)
	{
		//Try to prevent a lot of fragmentation by adding the slot to an existing region.
		//It won't fully avoid it, but this is good/simple enough. If you want to fully
		//prevent fragmentation, see StagingBuffer::mergeContiguousBlocks implementation.
		const size_t slot = transform - mTransformBuffers[bufferIdx];

		std::vector<Region>::iterator itor = mAvailableTransforms.begin();
		std::vector<Region>::iterator end = mAvailableTransforms.end();

		while (itor != end)
		{
			if (itor->bufferIdx == bufferIdx &&
				(itor->slotOffset == slot + 1 || slot == itor->slotOffset + itor->count))
			{
				break;
			}

			++itor;
		}

		if (itor != end)
		{
			if (itor->slotOffset == slot + 1)
				--itor->slotOffset;
			else //if( slot == itor->slot + itor->count )
				++itor->count;
		}
		else
		{
			mAvailableTransforms.push_back(Region(slot, 1, bufferIdx));
		}
	}
*/
	//-----------------------------------------------------------------------------------
	Ogre::uint32 GameEntityManager::getScheduledForRemovalAvailableSlot(void)
	{
		if (mScheduledForRemovalCurrentSlot >= mScheduledForRemoval.size())
		{
			if (mScheduledForRemovalAvailableSlots.empty())
			{
				mScheduledForRemovalAvailableSlots.push_back(mScheduledForRemoval.size());
				mScheduledForRemoval.push_back(GameEntityVec());
			}

			mScheduledForRemovalCurrentSlot = mScheduledForRemovalAvailableSlots.back();
			mScheduledForRemovalAvailableSlots.pop_back();
		}

		return mScheduledForRemovalCurrentSlot;
	}
	//-----------------------------------------------------------------------------------
	void GameEntityManager::finishFrameParallel(void)
	{
		if (mScheduledForRemovalCurrentSlot < mScheduledForRemoval.size())
		{
			mLogicSystem->queueSendMessage(mGraphicsSystem, Mq::GAME_ENTITY_SCHEDULED_FOR_REMOVAL_SLOT,
				mScheduledForRemovalCurrentSlot);

			mScheduledForRemovalCurrentSlot = (size_t)-1;
		}
	}

	Ogre::uint32 GameEntityManager::popAssignableId(void)
	{
		Ogre::uint32 returnable = mCurrentId;
		mCurrentId++;
		return returnable;
	}

};