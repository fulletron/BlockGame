#include "gamepointlight.h"

#include "OgreSceneManager.h"
#include "OgreItem.h"
#include "OgreSceneNode.h"

#include "../graphicssystem.h"

namespace OGraphics
{
	std::mutex GamePointLight::sUnusedUpdateBlockGroupsMutex;
	std::vector<PointLightUpdateBlockGroup *> GamePointLight::sUnusedUpdateBlockGroups;

	/*
	* Logic add (DOES NOT NEED TO EXIST)
	*/
	int GamePointLight::onGameEntityAdd()
	{
		return 0;
	}

	int GamePointLight::overwriteAllUpdateBlocks(int master_index)
	{ 
		PointLightUpdateBlock * pUpdateBlockMaster = &(mpUpdateBlockGroup->mUpdateBlocks[master_index]);
		for (int i = 0; i < NUM_GAME_ENTITY_BUFFERS; ++i)
		{
			if (master_index != i)
			{
				PointLightUpdateBlock * pUpdateBlockTarget = &(mpUpdateBlockGroup->mUpdateBlocks[i]);
				memcpy(pUpdateBlockTarget, pUpdateBlockMaster, sizeof(PointLightUpdateBlock));
			}
		}

		return 0;
	}

	PointLightUpdateBlockGroup * GamePointLight::getNewUpdateBlockGroup()
	{
		sUnusedUpdateBlockGroupsMutex.lock();

		static PointLightUpdateBlockGroup * ret_updateBlockGroup = 0;

		if (sUnusedUpdateBlockGroups.size() == 0)
		{
			ret_updateBlockGroup = new PointLightUpdateBlockGroup();
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
	//int GamePointLight::onGameEntityAdded(Ogre::SceneManager * pSceneManager)
	int GamePointLight::onGameEntityAdded(OGraphics::GraphicsSystem * pGraphicsSystem)
	{
		Ogre::SceneManager * pSceneManager = pGraphicsSystem->getSceneManager();
		// mpItemUpdateBlock->getParentEntity()->getSceneNode()->

		// This appears to be fairly generic
		PointLightUpdateBlock * pInitialBlock = &(mpUpdateBlockGroup->mUpdateBlocks[0]);

		// ENTITYMANAGER TODO :: Somehow make the parent node settable
		if (mpParentEntity)
		{
			mSceneNode = mpParentEntity->mSceneNode->createChildSceneNode(mSceneType);
		}
		else
		{
			mSceneNode = pGraphicsSystem->getSceneNodeWorld()->createChildSceneNode(mSceneType);
		}

		Ogre::Light * pLight = pSceneManager->createLight();
		mSceneNode->attachObject(pLight);

		mSceneNode->setPosition(pInitialBlock->mTransform.vPos);
		mSceneNode->setOrientation(pInitialBlock->mTransform.qRot);
		mSceneNode->setScale(pInitialBlock->mTransform.vScale);

		pLight->setRenderQueueGroup(pInitialBlock->renderGroupQueue);
		pLight->setVisibilityFlags(pInitialBlock->visibilityFlags);
		pLight->setDiffuseColour(pInitialBlock->diffuse);
		pLight->setSpecularColour(pInitialBlock->specular);
		pLight->setPowerScale(pInitialBlock->powerScale);
		pLight->setType(mpLightDefinition->lightType);
		pLight->setCastShadows(pInitialBlock->castShadows);
		pLight->setAttenuationBasedOnRadius(pInitialBlock->attenRadius, pInitialBlock->attenLumThresh);

		mpLightDefinition->mMovableObject = pLight;

		return 0;
	}

	/*
	* Graphics Update
	*/
	int GamePointLight::updateGraphics(const size_t & currentIdx, float a_interpolationWeight)
	{
		if (mpUpdateBlockGroup == 0)
		{
			// SHOULD NEVER GET HERE
			return 0;
		}

		float interpolationWeight = a_interpolationWeight;
		size_t currIdx = currentIdx;
		size_t prevIdx = (currIdx + NUM_GAME_ENTITY_BUFFERS - 1) % NUM_GAME_ENTITY_BUFFERS;

		const PointLightUpdateBlock & pPrevBlock = (mpUpdateBlockGroup->mUpdateBlocks[prevIdx]);
		const PointLightUpdateBlock & pCurrBlock = (mpUpdateBlockGroup->mUpdateBlocks[currIdx]);
		if (!pCurrBlock.interpolateByDefault)
			interpolationWeight = 0.0f;
		
		Ogre::Vector3 interpVec = Ogre::Math::lerp(pPrevBlock.mTransform.vPos,
			pCurrBlock.mTransform.vPos, interpolationWeight);
		mSceneNode->setPosition(interpVec);

		interpVec = Ogre::Math::lerp(pPrevBlock.mTransform.vScale,
			pCurrBlock.mTransform.vScale, interpolationWeight);
		mSceneNode->setScale(interpVec);

		Ogre::Quaternion interpQ = Ogre::Math::lerp(pPrevBlock.mTransform.qRot,
			pCurrBlock.mTransform.qRot, interpolationWeight);
		mSceneNode->setOrientation(interpQ);
		
		return 0;
	}

	/*
	* Logic Update
	*/
	int GamePointLight::updateLogic(float timeSinceLast, const size_t & currentIdx)
	{
		return 0;
	}


	void * GamePointLight::getUpdateBlock(int idx)
	{
		return &(mpUpdateBlockGroup->mUpdateBlocks[idx]);
	}

	/*
	* Logic Remove
	*/
	int GamePointLight::onGameEntityRemove()
	{
		sUnusedUpdateBlockGroupsMutex.lock();
		GamePointLight::sUnusedUpdateBlockGroups.push_back(mpUpdateBlockGroup);
		mpUpdateBlockGroup = 0;
		sUnusedUpdateBlockGroupsMutex.unlock();
		return 0;
	}

	/*
	* Graphics Remove
	*/
	int GamePointLight::onGameEntityRemoved(Ogre::SceneManager * pSceneManager)
	{
		pSceneManager->destroyLight(static_cast<Ogre::Light*>(mpLightDefinition->mMovableObject));
		mpLightDefinition->mMovableObject = 0;

		return 0;
	}
};