#include "gameitem.h"

#include "OgreSceneManager.h"
#include "OgreItem.h"
#include "OgreSceneNode.h"

#include "../graphicssystem.h"

namespace OGraphics
{
	std::mutex GameItem::sUnusedUpdateBlockGroupsMutex;
	std::vector<ItemUpdateBlockGroup *> GameItem::sUnusedUpdateBlockGroups;

	/*
	* Logic add (DOES NOT NEED TO EXIST)
	*/
	int GameItem::onGameEntityAdd()
	{
		return 0;
	}

	int GameItem::overwriteAllUpdateBlocks(int master_index)
	{ 
		ItemUpdateBlock * pItemUpdateBlockMaster = &(mpItemUpdateBlockGroup->mUpdateBlocks[master_index]);
		for (int i = 0; i < NUM_GAME_ENTITY_BUFFERS; ++i)
		{
			if (master_index != i)
			{
				ItemUpdateBlock * pItemUpdateBlockTarget = &(mpItemUpdateBlockGroup->mUpdateBlocks[i]);
				memcpy(pItemUpdateBlockTarget, pItemUpdateBlockMaster, sizeof(ItemUpdateBlock));
			}
		}

		return 0;
	}

	/*
	* This could be templated out
	*/
	ItemUpdateBlockGroup * GameItem::getNewUpdateBlockGroup()
	{
		sUnusedUpdateBlockGroupsMutex.lock();

		static ItemUpdateBlockGroup * ret_updateBlockGroup = 0;

		if (sUnusedUpdateBlockGroups.size() == 0)
		{
			ret_updateBlockGroup = new ItemUpdateBlockGroup();
		}
		else
		{
			ret_updateBlockGroup = sUnusedUpdateBlockGroups.back();
			sUnusedUpdateBlockGroups.pop_back();
		}

		sUnusedUpdateBlockGroupsMutex.unlock();

		return ret_updateBlockGroup;
	}

	/*
	* Graphics Add
	* UpdateBlock and Definition should already have been added.
	*/
	//int GameItem::onGameEntityAdded(Ogre::SceneManager * pSceneManager)
	int GameItem::onGameEntityAdded(OGraphics::GraphicsSystem * pGraphicsSystem)
	{
		Ogre::SceneManager * pSceneManager = pGraphicsSystem->getSceneManager();
		// mpItemUpdateBlock->getParentEntity()->getSceneNode()->

		// This appears to be fairly generic
		ItemUpdateBlock * pInitialBlock = &(mpItemUpdateBlockGroup->mUpdateBlocks[0]);

		// ENTITYMANAGER TODO :: Somehow make the parent node settable
		if (mpParentEntity)
		{
			mSceneNode = mpParentEntity->mSceneNode->createChildSceneNode(mSceneType);
		}
		else
		{
			mSceneNode = pGraphicsSystem->getSceneNodeWorld()->createChildSceneNode(mSceneType);
		}

		mSceneNode->setPosition(pInitialBlock->mTransform.vPos);
		mSceneNode->setOrientation(pInitialBlock->mTransform.qRot);
		mSceneNode->setScale(pInitialBlock->mTransform.vScale);

		Ogre::Item *item = pSceneManager->createItem(mpItemDefinition->meshName,
			mpItemDefinition->resourceGroup,
			mSceneType);

		Ogre::StringVector materialNames = mpItemDefinition->submeshMaterials;
		size_t minMaterials = std::min(materialNames.size(), item->getNumSubItems());

		for (size_t i = 0; i<minMaterials; ++i)
		{
			item->getSubItem(i)->setDatablockOrMaterialName(materialNames[i],
				mpItemDefinition->resourceGroup);
		}

		item->setCastShadows(pInitialBlock->castShadows);
		item->setRenderQueueGroup(pInitialBlock->renderGroupQueue);
		item->setVisibilityFlags(pInitialBlock->visibilityFlags);

		mpItemDefinition->mMovableObject = item;
		mSceneNode->attachObject(mpItemDefinition->mMovableObject);

		return 0;
	}

	/*
	* Graphics Update
	*/
	int GameItem::updateGraphics(const size_t & currentIdx, float a_interpolationWeight)
	{
		if (mpItemUpdateBlockGroup == 0)
		{
			// SHOULD NEVER GET HERE
			return 0;
		}

		float interpolationWeight = a_interpolationWeight;
		size_t currIdx = currentIdx;
		size_t prevIdx = (currIdx + NUM_GAME_ENTITY_BUFFERS - 1) % NUM_GAME_ENTITY_BUFFERS;

		const ItemUpdateBlock & pPrevBlock = (mpItemUpdateBlockGroup->mUpdateBlocks[prevIdx]);
		const ItemUpdateBlock & pCurrBlock = (mpItemUpdateBlockGroup->mUpdateBlocks[currIdx]);
		if (!pCurrBlock.interpolateByDefault)
			interpolationWeight = 0.0f;

//		interpolationWeight = 0.0f;
		
		Ogre::Vector3 interpVec = Ogre::Math::lerp(pPrevBlock.mTransform.vPos,
			pCurrBlock.mTransform.vPos, interpolationWeight);
		mSceneNode->setPosition(interpVec);

		interpVec = Ogre::Math::lerp(pPrevBlock.mTransform.vScale,
			pCurrBlock.mTransform.vScale, interpolationWeight);
		mSceneNode->setScale(interpVec);

		Ogre::Quaternion interpQ = Ogre::Math::lerp(pPrevBlock.mTransform.qRot,
			pCurrBlock.mTransform.qRot, interpolationWeight);
// nlerp with "true" allows for the interpolation to not 'snap' when (presumably)
// passing the 180, -180 range.
//		Ogre::Quaternion interpQ = pPrevBlock.mTransform.qRot.nlerp(interpolationWeight, pPrevBlock.mTransform.qRot, pCurrBlock.mTransform.qRot, true);
		mSceneNode->setOrientation(interpQ);
		
		return 0;
	}

	/*
	* Logic Update
	*/
	int GameItem::updateLogic(float timeSinceLast, const size_t & currentIdx)
	{
// TODO ::
		// What goes in here?
		// If I want all of my entities to update differently, then I would need to know 
		// about what it is and what it does. All items, for example, will not update
		// the same. A tree needs to blow in the wind, while a fireball will need
		// to move towards a target.
		
		// Perhaps create a void * in the updateLogic() call for a pointer to an update block,
		// and simply dump that block into here.
		// If there is no block, copy the last block into the current block.


// I'm trying an isDirty functionality. When getUpdateBlock() is called, the block isDirty is set.
// After this call, 
		ItemUpdateBlock * pUpdateBlock = &(mpItemUpdateBlockGroup->mUpdateBlocks[currentIdx]);
		if (!pUpdateBlock->isDirty)
		{
			const size_t prevIdx = (currentIdx + NUM_GAME_ENTITY_BUFFERS - 1) % NUM_GAME_ENTITY_BUFFERS;
			ItemUpdateBlock * pItemUpdateBlockPrev = &(mpItemUpdateBlockGroup->mUpdateBlocks[prevIdx]);
			memcpy(pUpdateBlock, pItemUpdateBlockPrev, sizeof(ItemUpdateBlock));
		}

		pUpdateBlock->isDirty = false;
		return 0;
	}

	/*
	* Logic Remove
	*/
	int GameItem::onGameEntityRemove()
	{
		sUnusedUpdateBlockGroupsMutex.lock();
		GameItem::sUnusedUpdateBlockGroups.push_back(mpItemUpdateBlockGroup);
		mpItemUpdateBlockGroup = 0;
		sUnusedUpdateBlockGroupsMutex.unlock();
		return 0;
	}

	void * GameItem::getUpdateBlock(int idx)
	{
		ItemUpdateBlock * pUpdateBlock = &(mpItemUpdateBlockGroup->mUpdateBlocks[idx]);
		if (!pUpdateBlock->isDirty)
		{
			const size_t prevIdx = (idx + NUM_GAME_ENTITY_BUFFERS - 1) % NUM_GAME_ENTITY_BUFFERS;
			ItemUpdateBlock * pItemUpdateBlockPrev = &(mpItemUpdateBlockGroup->mUpdateBlocks[prevIdx]);
			memcpy(pUpdateBlock, pItemUpdateBlockPrev, sizeof(ItemUpdateBlock));
			pUpdateBlock->isDirty = true;
		}
		return pUpdateBlock;
	}

	/*
	* Graphics Remove
	*/
	int GameItem::onGameEntityRemoved(Ogre::SceneManager * pSceneManager)
	{
		pSceneManager->destroyItem(static_cast<Ogre::Item*>(mpItemDefinition->mMovableObject));
		mpItemDefinition->mMovableObject = 0;

		return 0;
	}
};