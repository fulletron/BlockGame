#ifndef _GAMEITEM_H_
#define _GAMEITEM_H_

#include "gameentity.h"
#include <mutex>

namespace OGraphics
{
	class ItemDefinition : public GameEntityDefinition
	{
	public:
		Ogre::String        meshName;
		Ogre::String        resourceGroup;
		Ogre::StringVector  submeshMaterials;
	};

	class ItemUpdateBlock : public GameEntityUpdateBlock
	{
	public:
		bool castShadows;
	};

	class ItemUpdateBlockGroup
	{
	public:
		ItemUpdateBlock mUpdateBlocks[NUM_GAME_ENTITY_BUFFERS];
	};

	class GameItem : public GameEntity
	{
	public:
		static std::mutex								sUnusedUpdateBlockGroupsMutex;
		static std::vector<ItemUpdateBlockGroup *>		sUnusedUpdateBlockGroups;

	public:
		ItemDefinition * mpItemDefinition;
		ItemUpdateBlockGroup * mpItemUpdateBlockGroup;

		GameItem(Ogre::uint32 id,
			Ogre::SceneMemoryMgrTypes a_sceneType,
			ItemDefinition *pItemDefinition,
			ItemUpdateBlockGroup * pItemUpdateBlockGroup) :
			GameEntity(id, a_sceneType),
			mpItemDefinition(pItemDefinition),
			mpItemUpdateBlockGroup(pItemUpdateBlockGroup)
		{
			mpItemDefinition->mMoType = MoTypeItem;
//			for (int i = 0; i<NUM_GAME_ENTITY_BUFFERS; ++i)
//				mTransform[i] = 0;
		}

		/*
		* Logic add
		*/
		virtual int onGameEntityAdd();

		/*
		* Graphics Add
		*/
		//virtual int onGameEntityAdded(Ogre::SceneManager * pSceneManager, const GameEntityTransform & initialTransform);
		//virtual int onGameEntityAdded(Ogre::SceneManager * pSceneManager);
		virtual int onGameEntityAdded(OGraphics::GraphicsSystem * pGraphicsSystem);

		/*
		* Graphics Update
		*/
		virtual int updateGraphics(const size_t & currentIdx, float interpolationWeight);

		/*
		* Logic Update
		*/
		virtual int updateLogic(float timeSinceLast, const size_t & currentIdx);

		/*
		* Logic Remove
		*/
		virtual int onGameEntityRemove();

		/*
		* Graphics Remove
		*/
		virtual int onGameEntityRemoved(Ogre::SceneManager * pSceneManager);

		/*
		* Copy one block to all blocks in the block group
		*/
		virtual int overwriteAllUpdateBlocks(int master_index);

		/*
		* Get a pointer to the update block specified.
		*/
		virtual void * getUpdateBlock(int idx);

		/*
		* returns a free ItemUpdateBlockGroup
		*/ 
		static ItemUpdateBlockGroup * getNewUpdateBlockGroup();
	};
};

#endif