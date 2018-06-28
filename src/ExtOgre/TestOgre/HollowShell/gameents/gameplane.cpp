#include "gameplane.h"

#include "OgreSceneManager.h"
#include "OgreSceneNode.h"

// Planes are still items
#include "OgreItem.h"

// For the plane building and V1->V2
#include "OgreMeshManager.h"
#include "OgreMeshManager2.h"
#include "OgreMesh2.h"

#include "../graphicssystem.h"

namespace OGraphics
{
	std::mutex GamePlane::sUnusedUpdateBlockGroupsMutex;
	std::vector<PlaneUpdateBlockGroup *> GamePlane::sUnusedUpdateBlockGroups;

	/*
	* Logic add (DOES NOT NEED TO EXIST)
	*/
	int GamePlane::onGameEntityAdd()
	{
		return 0;
	}

	int GamePlane::overwriteAllUpdateBlocks(int master_index)
	{ 
		Ogre::Real test = mpUpdateBlockGroup->mUpdateBlocks[0].mTransform.vPos.z;
		PlaneUpdateBlock * pUpdateBlockMaster = &(mpUpdateBlockGroup->mUpdateBlocks[master_index]);
		for (int i = 0; i < NUM_GAME_ENTITY_BUFFERS; ++i)
		{
			if (master_index != i)
			{
				PlaneUpdateBlock * pUpdateBlockTarget = &(mpUpdateBlockGroup->mUpdateBlocks[i]);
				memcpy(pUpdateBlockTarget, pUpdateBlockMaster, sizeof(PlaneUpdateBlock));
			}
		}

		return 0;
	}

	/*
	* This could be templated out
	*/
	PlaneUpdateBlockGroup * GamePlane::getNewUpdateBlockGroup()
	{
		sUnusedUpdateBlockGroupsMutex.lock();

		static PlaneUpdateBlockGroup * ret_updateBlockGroup = 0;

		if (sUnusedUpdateBlockGroups.size() == 0)
		{
			ret_updateBlockGroup = new PlaneUpdateBlockGroup();
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
	//int GamePlane::onGameEntityAdded(Ogre::SceneManager * pSceneManager)
	int GamePlane::onGameEntityAdded(OGraphics::GraphicsSystem * pGraphicsSystem)
	{
		Ogre::SceneManager * pSceneManager = pGraphicsSystem->getSceneManager();
		// mpPlaneUpdateBlock->getParentEntity()->getSceneNode()->

		// This appears to be fairly generic
		PlaneUpdateBlock * pInitialBlock = &(mpUpdateBlockGroup->mUpdateBlocks[0]);

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

		const PlaneDefinition & def = *mpDefinition;

		Ogre::v1::MeshPtr planeMeshV1 = Ogre::v1::MeshManager::getSingleton().createPlane(
			def.meshV1Name, 
			def.resourceGroup,
			def.plane,
			pInitialBlock->length,
			pInitialBlock->width,
			def.xsegments, 
			def.ysegments, 
			def.normals, 
			def.numTexCoordSets, 
			def.uTile, 
			def.vTile, 
			def.upVector,
			Ogre::v1::HardwareBuffer::HBU_STATIC,
			Ogre::v1::HardwareBuffer::HBU_STATIC);

		Ogre::MeshPtr planeMesh = Ogre::MeshManager::getSingleton().createManual(
			def.meshName, 
			def.resourceGroup);

		planeMesh->importV1(planeMeshV1.get(), true, true, true);;

		planeMeshV1->unload();

		// A plane is just a fancy item
		Ogre::Item *item = pSceneManager->createItem(planeMesh,
			mSceneType);

		Ogre::StringVector materialNames = mpDefinition->submeshMaterials;
		size_t minMaterials = std::min(materialNames.size(), item->getNumSubItems());

		for (size_t i = 0; i<minMaterials; ++i)
		{
			item->getSubItem(i)->setDatablockOrMaterialName(materialNames[i],
				mpDefinition->resourceGroup);
		}

		item->setCastShadows(false);
		item->setRenderQueueGroup(pInitialBlock->renderGroupQueue);
		item->setVisibilityFlags(pInitialBlock->visibilityFlags);
		mpDefinition->mMovableObject = item;
		mSceneNode->attachObject(mpDefinition->mMovableObject);

		return 0;
	}

	/*
	* Graphics Update
	*/
	int GamePlane::updateGraphics(const size_t & currentIdx, float a_interpolationWeight)
	{
		if (mpUpdateBlockGroup == 0)
		{
			// SHOULD NEVER GET HERE
			return 0;
		}

		float interpolationWeight = a_interpolationWeight;
		size_t currIdx = currentIdx;
		size_t prevIdx = (currIdx + NUM_GAME_ENTITY_BUFFERS - 1) % NUM_GAME_ENTITY_BUFFERS;

		const PlaneUpdateBlock & pPrevBlock = (mpUpdateBlockGroup->mUpdateBlocks[prevIdx]);
		const PlaneUpdateBlock & pCurrBlock = (mpUpdateBlockGroup->mUpdateBlocks[currIdx]);
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
	int GamePlane::updateLogic(float timeSinceLast, const size_t & currentIdx)
	{
		return 0;
	}

	void * GamePlane::getUpdateBlock(int idx)
	{
		return &(mpUpdateBlockGroup->mUpdateBlocks[idx]);
	}

	/*
	* Logic Remove
	*/
	int GamePlane::onGameEntityRemove()
	{
		sUnusedUpdateBlockGroupsMutex.lock();
		GamePlane::sUnusedUpdateBlockGroups.push_back(mpUpdateBlockGroup);
		mpUpdateBlockGroup = 0;
		sUnusedUpdateBlockGroupsMutex.unlock();
		return 0;
	}

	/*
	* Graphics Remove
	*/
	int GamePlane::onGameEntityRemoved(Ogre::SceneManager * pSceneManager)
	{
		pSceneManager->destroyItem(static_cast<Ogre::Item*>(mpDefinition->mMovableObject));
		mpDefinition->mMovableObject = 0;

		return 0;
	}
};