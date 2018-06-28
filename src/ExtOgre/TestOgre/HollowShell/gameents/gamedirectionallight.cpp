#include "gamedirectionallight.h"

#include "OgreSceneManager.h"
#include "OgreItem.h"
#include "OgreSceneNode.h"

#include "../graphicssystem.h"

namespace OGraphics
{
	std::mutex GameDirectionalLight::sUnusedUpdateBlockGroupsMutex;
	std::vector<DirectionalLightUpdateBlockGroup *> GameDirectionalLight::sUnusedUpdateBlockGroups;

	/*
	* Logic add (DOES NOT NEED TO EXIST)
	*/
	int GameDirectionalLight::onGameEntityAdd()
	{
		return 0;
	}

	int GameDirectionalLight::overwriteAllUpdateBlocks(int master_index)
	{
		DirectionalLightUpdateBlock * pUpdateBlockMaster = &(mpUpdateBlockGroup->mUpdateBlocks[master_index]);
		for (int i = 0; i < NUM_GAME_ENTITY_BUFFERS; ++i)
		{
			if (master_index != i)
			{
				DirectionalLightUpdateBlock * pUpdateBlockTarget = &(mpUpdateBlockGroup->mUpdateBlocks[i]);
				memcpy(pUpdateBlockTarget, pUpdateBlockMaster, sizeof(DirectionalLightUpdateBlock));
			}
		}

		return 0;
	}

	DirectionalLightUpdateBlockGroup * GameDirectionalLight::getNewUpdateBlockGroup()
	{
		sUnusedUpdateBlockGroupsMutex.lock();

		static DirectionalLightUpdateBlockGroup * ret_updateBlockGroup = 0;

		if (sUnusedUpdateBlockGroups.size() == 0)
		{
			ret_updateBlockGroup = new DirectionalLightUpdateBlockGroup();
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
	//int GameDirectionalLight::onGameEntityAdded(Ogre::SceneManager * pSceneManager)
	int GameDirectionalLight::onGameEntityAdded(OGraphics::GraphicsSystem * pGraphicsSystem)
	{
		Ogre::SceneManager * pSceneManager = pGraphicsSystem->getSceneManager();

		DirectionalLightUpdateBlock * pInitialBlock = &(mpUpdateBlockGroup->mUpdateBlocks[0]);

		Ogre::Light * pLight = pSceneManager->createLight();
		if (mpParentEntity)
		{
			mSceneNode = mpParentEntity->mSceneNode->createChildSceneNode(mSceneType);
		}
		else
		{
			mSceneNode = pGraphicsSystem->getSceneNodeWorld()->createChildSceneNode(mSceneType);
		}
		// pLight needs to be attached before setDirection can be called
		mSceneNode->attachObject(pLight);

		mSceneNode->setPosition(pInitialBlock->mTransform.vPos);
		mSceneNode->setOrientation(pInitialBlock->mTransform.qRot);

		pLight->setRenderQueueGroup(pInitialBlock->renderGroupQueue);
		pLight->setVisibilityFlags(pInitialBlock->visibilityFlags);
		pLight->setPowerScale(pInitialBlock->powerScale);
		pLight->setType(mpLightDefinition->lightType);
		pLight->setDirection(pInitialBlock->direction);
		pLight->setCastShadows(pInitialBlock->castShadows);
		pLight->setSpecularColour(pInitialBlock->specular);
		pLight->setDiffuseColour(pInitialBlock->diffuse);

		mpLightDefinition->mMovableObject = pLight;

		pSceneManager->setAmbientLight(
			pInitialBlock->ambientLight.upperHemisphere,
			pInitialBlock->ambientLight.lowerHemisphere,
			pInitialBlock->ambientLight.hemisphereDir,
			pInitialBlock->ambientLight.envMapScale);

		return 0;
	}

	/*
	* Graphics Update
	*/
	int GameDirectionalLight::updateGraphics(const size_t & currentIdx, float a_interpolationWeight)
	{
		if (mpUpdateBlockGroup == 0)
		{
			// SHOULD NEVER GET HERE
			return 0;
		}

		float interpolationWeight = a_interpolationWeight;
		size_t currIdx = currentIdx;
		size_t prevIdx = (currIdx + NUM_GAME_ENTITY_BUFFERS - 1) % NUM_GAME_ENTITY_BUFFERS;

		const DirectionalLightUpdateBlock & pPrevBlock = (mpUpdateBlockGroup->mUpdateBlocks[prevIdx]);
		const DirectionalLightUpdateBlock & pCurrBlock = (mpUpdateBlockGroup->mUpdateBlocks[currIdx]);
		if (!pCurrBlock.interpolateByDefault)
			interpolationWeight = 0.0f;
		/*
		Ogre::Vector3 interpVec = Ogre::Math::lerp(pPrevBlock.mTransform.vPos,
			pCurrBlock.mTransform.vPos, interpolationWeight);
		mSceneNode->setPosition(interpVec);

		interpVec = Ogre::Math::lerp(pPrevBlock.mTransform.vScale,
			pCurrBlock.mTransform.vScale, interpolationWeight);
		mSceneNode->setScale(interpVec);

		Ogre::Quaternion interpQ = Ogre::Math::lerp(pPrevBlock.mTransform.qRot,
			pCurrBlock.mTransform.qRot, interpolationWeight);
		mSceneNode->setOrientation(interpQ);
		*/
		return 0;
	}

	/*
	* Logic Update
	*/
	int GameDirectionalLight::updateLogic(float timeSinceLast, const size_t & currentIdx)
	{
		return 0;
	}

	void * GameDirectionalLight::getUpdateBlock(int idx)
	{
		return &(mpUpdateBlockGroup->mUpdateBlocks[idx]);
	}

	/*
	* Logic Remove
	*/
	int GameDirectionalLight::onGameEntityRemove()
	{
		sUnusedUpdateBlockGroupsMutex.lock();
		GameDirectionalLight::sUnusedUpdateBlockGroups.push_back(mpUpdateBlockGroup);
		mpUpdateBlockGroup = 0;
		sUnusedUpdateBlockGroupsMutex.unlock();
		return 0;
	}

	/*
	* Graphics Remove
	*/
	int GameDirectionalLight::onGameEntityRemoved(Ogre::SceneManager * pSceneManager)
	{
		pSceneManager->destroyLight(static_cast<Ogre::Light*>(mpLightDefinition->mMovableObject));
		mpLightDefinition->mMovableObject = 0;

		return 0;
	}
};