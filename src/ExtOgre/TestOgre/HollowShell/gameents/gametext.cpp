#include "gametext.h"

#include "OgreSceneManager.h"
#include "OgreSceneNode.h"

#include "../graphicssystem.h"

namespace OGraphics
{
	std::mutex GameText::sUnusedUpdateBlockGroupsMutex;
	std::vector<TextUpdateBlockGroup *> GameText::sUnusedUpdateBlockGroups;

	/*
	* Logic add (DOES NOT NEED TO EXIST)
	*/
	int GameText::onGameEntityAdd()
	{
		return 0;
	}

	int GameText::overwriteAllUpdateBlocks(int master_index)
	{ 
		TextUpdateBlock * pItemUpdateBlockMaster = &(mpUpdateBlockGroup->mUpdateBlocks[master_index]);
		for (int i = 0; i < NUM_GAME_ENTITY_BUFFERS; ++i)
		{
			if (master_index != i)
			{
				TextUpdateBlock * pUpdateBlockTarget = &(mpUpdateBlockGroup->mUpdateBlocks[i]);
				memcpy(pUpdateBlockTarget, pItemUpdateBlockMaster, sizeof(TextUpdateBlock));
			}
		}

		return 0;
	}

	/*
	* This could be templated out
	*/
	TextUpdateBlockGroup * GameText::getNewUpdateBlockGroup()
	{
		sUnusedUpdateBlockGroupsMutex.lock();

		static TextUpdateBlockGroup * ret_updateBlockGroup = 0;

		if (sUnusedUpdateBlockGroups.size() == 0)
		{
			ret_updateBlockGroup = new TextUpdateBlockGroup();
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
	//int GameText::onGameEntityAdded(Ogre::SceneManager * pSceneManager)
	int GameText::onGameEntityAdded(OGraphics::GraphicsSystem * pGraphicsSystem)
	{
		Ogre::SceneManager * pSceneManager = pGraphicsSystem->getSceneManager();
		// mpItemUpdateBlock->getParentEntity()->getSceneNode()->

		// This appears to be fairly generic
		TextUpdateBlock * pInitialBlock = &(mpUpdateBlockGroup->mUpdateBlocks[0]);

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

		Ogre::NameValuePairList params;
		params["name"] = mpDefinition->name;
		params["caption"] = pInitialBlock->caption;
		params["fontName"] = mpDefinition->fontName;
		params["isBillboard"] = Ogre::StringConverter::toString(mpDefinition->isBillboard);
		params["textSize"] = mpDefinition->textSize;
		mpMovableText = static_cast<Ogre::MovableText*>(pSceneManager->createMovableObject(Ogre::MovableTextFactory::FACTORY_TYPE_NAME,
			&pSceneManager->_getEntityMemoryManager(mSceneType), &params));

		mpMovableText->setTextAlignment(pInitialBlock->alignmentHoriz, pInitialBlock->alignmentVert); // Center horizontally and display above the node
		// / msg->setAdditionalHeight( 2.0f ); //msg->setAdditionalHeight( ei.getRadius() ) // apparently not needed from 1.7 /

		mpMovableText->setRenderQueueGroup(pInitialBlock->renderGroupQueue);
		mpMovableText->setVisibilityFlags(pInitialBlock->visibilityFlags);

		mpDefinition->mMovableObject = mpMovableText;
		mSceneNode->attachObject(mpMovableText);

		return 0;
	}

	/*
	* Graphics Update
	*/
	int GameText::updateGraphics(const size_t & currentIdx, float a_interpolationWeight)
	{
		if (mpUpdateBlockGroup == 0)
		{
			// SHOULD NEVER GET HERE
			return 0;
		}

		float interpolationWeight = a_interpolationWeight;
		size_t currIdx = currentIdx;
		size_t prevIdx = (currIdx + NUM_GAME_ENTITY_BUFFERS - 1) % NUM_GAME_ENTITY_BUFFERS;

		const TextUpdateBlock & pPrevBlock = (mpUpdateBlockGroup->mUpdateBlocks[prevIdx]);
		const TextUpdateBlock & pCurrBlock = (mpUpdateBlockGroup->mUpdateBlocks[currIdx]);
		if (!pCurrBlock.interpolateByDefault)
			interpolationWeight = 0.0f;
		
		Ogre::Vector3 interpVec = Ogre::Math::lerp(pPrevBlock.mTransform.vPos,
			pCurrBlock.mTransform.vPos, interpolationWeight);
		mSceneNode->setPosition(interpVec);

		interpVec = Ogre::Math::lerp(pPrevBlock.mTransform.vScale,
			pCurrBlock.mTransform.vScale, interpolationWeight);
		mSceneNode->setScale(interpVec);

		// FOR SOME REASON, setting the orientation changes the orientation of the billboard.
		if (!mpDefinition->isBillboard)
		{
			Ogre::Quaternion interpQ = pPrevBlock.mTransform.qRot.nlerp(interpolationWeight, pPrevBlock.mTransform.qRot, pCurrBlock.mTransform.qRot, true);
			mSceneNode->setOrientation(interpQ);
		}

		return 0;
	}

	/*
	* Logic Update
	*/
	int GameText::updateLogic(float timeSinceLast, const size_t & currentIdx)
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
		TextUpdateBlock * pUpdateBlock = &(mpUpdateBlockGroup->mUpdateBlocks[currentIdx]);
		if (!pUpdateBlock->isDirty)
		{
			const size_t prevIdx = (currentIdx + NUM_GAME_ENTITY_BUFFERS - 1) % NUM_GAME_ENTITY_BUFFERS;
			TextUpdateBlock * pUpdateBlockPrev = &(mpUpdateBlockGroup->mUpdateBlocks[prevIdx]);
			memcpy(pUpdateBlock, pUpdateBlockPrev, sizeof(TextUpdateBlock));
		}

		pUpdateBlock->isDirty = false;
		return 0;
	}

	/*
	* Logic Remove
	*/
	int GameText::onGameEntityRemove()
	{
		sUnusedUpdateBlockGroupsMutex.lock();
		GameText::sUnusedUpdateBlockGroups.push_back(mpUpdateBlockGroup);
		mpUpdateBlockGroup = 0;
		sUnusedUpdateBlockGroupsMutex.unlock();
		return 0;
	}

	void * GameText::getUpdateBlock(int idx)
	{
		TextUpdateBlock * pUpdateBlock = &(mpUpdateBlockGroup->mUpdateBlocks[idx]);
		if (!pUpdateBlock->isDirty)
		{
			const size_t prevIdx = (idx + NUM_GAME_ENTITY_BUFFERS - 1) % NUM_GAME_ENTITY_BUFFERS;
			TextUpdateBlock * pUpdateBlockPrev = &(mpUpdateBlockGroup->mUpdateBlocks[prevIdx]);
			memcpy(pUpdateBlock, pUpdateBlockPrev, sizeof(TextUpdateBlock));
			pUpdateBlock->isDirty = true;
		}
		return pUpdateBlock;
	}

	/*
	* Graphics Remove
	*/
	int GameText::onGameEntityRemoved(Ogre::SceneManager * pSceneManager)
	{
		pSceneManager->destroyMovableObject(static_cast<Ogre::MovableText*>(mpDefinition->mMovableObject));
		mpDefinition->mMovableObject = 0;

		return 0;
	}
};