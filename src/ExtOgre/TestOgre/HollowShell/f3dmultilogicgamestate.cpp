#include "f3dmultilogicgamestate.h"

#include "logicsystem.h"
#include "gameentitymanager.h"

#include "OgreVector3.h"
#include "OgreResourceGroupManager.h"

#include "gameents/gameitem.h"
#include "gameents/gameplane.h"
#include "gameents/gamedirectionallight.h"
#include "gameents/gamespotlight.h"
#include "gameents/gamepointlight.h"
#include "gameents/gametext.h"

using namespace OGraphics;

namespace OGraphics {

	F3DMultiLogicGameState::F3DMultiLogicGameState() :
		mDisplacement(0),
		mpLogicSystem(0)
	{
	}
	//-----------------------------------------------------------------------------------
	F3DMultiLogicGameState::~F3DMultiLogicGameState()
	{
		// DELETING THE cubeEntity HERE CAUSES A CRASH
	}
	//-----------------------------------------------------------------------------------
	void F3DMultiLogicGameState::createScene01(void)
	{
		GameEntityManager *geMgr = mpLogicSystem->getGameEntityManager();



		//=======================================================================
		{
			PlaneUpdateBlockGroup * pPlaneUpdateBlockGroup = GamePlane::getNewUpdateBlockGroup();
			PlaneUpdateBlock * pPlaneUpdateBlock = &(pPlaneUpdateBlockGroup->mUpdateBlocks[0]);
			pPlaneUpdateBlock->length = 5000.0f;
			pPlaneUpdateBlock->width = 5000.0f;
			pPlaneUpdateBlock->mTransform._reset();
			pPlaneUpdateBlock->mTransform.vPos = Ogre::Vector3(0, -1, 0);
			pPlaneUpdateBlock->renderGroupQueue = 1;
			pPlaneUpdateBlock->visibilityFlags = 1;
			pPlaneUpdateBlock->interpolateByDefault = false;
			pPlaneUpdateBlock->interpolateNextDraw = true;

			PlaneDefinition * pPlaneDefinition = new PlaneDefinition();
			pPlaneDefinition->meshName = "Plane";
			pPlaneDefinition->meshV1Name = "Plane v1";
			pPlaneDefinition->mMoType = MoTypePlane;
			pPlaneDefinition->plane = Ogre::Plane(Ogre::Vector3::UNIT_Y, 1.0f);
			pPlaneDefinition->normals = true;
			pPlaneDefinition->resourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
			pPlaneDefinition->submeshMaterials.clear();
			pPlaneDefinition->numTexCoordSets = 1;
			pPlaneDefinition->upVector = Ogre::Vector3::UNIT_Z;
			pPlaneDefinition->uTile = 4.0f;
			pPlaneDefinition->vTile = 4.0f;
			pPlaneDefinition->xsegments = 1;
			pPlaneDefinition->ysegments = 1;

			mpPlane = new GamePlane(
				geMgr->popAssignableId(),
				Ogre::SCENE_DYNAMIC,
				pPlaneDefinition,
				pPlaneUpdateBlockGroup);

			mpPlane->overwriteAllUpdateBlocks(0);

			geMgr->addGameEntity(mpPlane);
		}

		//==============================================================
		{
			ItemUpdateBlockGroup * pItemUpdateBlockGroup = GameItem::getNewUpdateBlockGroup();
			ItemUpdateBlock * pItemUpdateBlock = &(pItemUpdateBlockGroup->mUpdateBlocks[0]);
			pItemUpdateBlock->mTransform.vPos = Ogre::Vector3(0.0f, 5.0f, 0.0f);
			pItemUpdateBlock->mTransform.qRot = Ogre::Quaternion((Ogre::Radian((Ogre::Real)0)), Ogre::Vector3::UNIT_Z);
			pItemUpdateBlock->mTransform.vScale = Ogre::Vector3(0.65f, 0.65f, 0.65f);
			pItemUpdateBlock->castShadows = true;
			pItemUpdateBlock->renderGroupQueue = 1;
			pItemUpdateBlock->visibilityFlags = 1;
			pItemUpdateBlock->interpolateByDefault = false;
			pItemUpdateBlock->interpolateNextDraw = true;

			ItemDefinition * pItemDefinition = new ItemDefinition;
			pItemDefinition->meshName = "Cube_d.mesh";
			pItemDefinition->resourceGroup = Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME;
			pItemDefinition->mMoType = MoTypeItem;
			pItemDefinition->submeshMaterials.push_back("Rocks");

			mpMovingCube = new OGraphics::GameItem(
				geMgr->popAssignableId(),
				Ogre::SCENE_DYNAMIC,
				pItemDefinition,
				pItemUpdateBlockGroup);

			mpMovingCube->overwriteAllUpdateBlocks(0);

			geMgr->addGameEntity(mpMovingCube);
		}
		//==============================================================
		float armsLength = 2.5f;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				size_t idx = i * 4 + j;

				ItemUpdateBlockGroup * pItemUpdateBlockGroup = GameItem::getNewUpdateBlockGroup();
				ItemUpdateBlock * pItemUpdateBlock = &(pItemUpdateBlockGroup->mUpdateBlocks[0]);
				pItemUpdateBlock->mTransform.vPos = Ogre::Vector3((i - 1.5f) * armsLength, 2.0f, (j - 1.5f) * armsLength);
				pItemUpdateBlock->mTransform.qRot = Ogre::Quaternion((Ogre::Radian((Ogre::Real)idx)), Ogre::Vector3::UNIT_Z);
				pItemUpdateBlock->mTransform.vScale = Ogre::Vector3(0.65f, 0.65f, 0.65f);
				pItemUpdateBlock->castShadows = true;
				pItemUpdateBlock->renderGroupQueue = 1;
				pItemUpdateBlock->visibilityFlags = 1;
				pItemUpdateBlock->interpolateByDefault = false;
				pItemUpdateBlock->interpolateNextDraw = true;

				ItemDefinition * pItemDefinition = new ItemDefinition;
				pItemDefinition->meshName = "Cube_d.mesh";
				pItemDefinition->resourceGroup = Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME;
				pItemDefinition->mMoType = MoTypeItem;
				pItemDefinition->submeshMaterials.push_back("Rocks");

				mpCubes[idx] = new OGraphics::GameItem(
					geMgr->popAssignableId(),
					Ogre::SCENE_DYNAMIC,
					pItemDefinition,
					pItemUpdateBlockGroup);

				mpCubes[idx]->overwriteAllUpdateBlocks(0);

				geMgr->addGameEntity(mpCubes[idx]);
			}
		}
		//==============================================================
		for (int i = 0; i < 64; ++i)
		{
			ItemUpdateBlockGroup * pItemUpdateBlockGroup = GameItem::getNewUpdateBlockGroup();
			ItemUpdateBlock * pItemUpdateBlock = &(pItemUpdateBlockGroup->mUpdateBlocks[0]);

			//pItemUpdateBlock->mTransform.qRot = Ogre::Quaternion((Ogre::Radian((Ogre::Real)i)), Ogre::Vector3::UNIT_Y);
			pItemUpdateBlock->mTransform.vScale =
				Ogre::Vector3(Ogre::Math::RangeRandom(0.5f, 10.0f),
				Ogre::Math::RangeRandom(5.0f, 15.0f),
				Ogre::Math::RangeRandom(0.5f, 10.0f));
			pItemUpdateBlock->mTransform.vPos = Ogre::Vector3(
				Ogre::Math::RangeRandom(-250, 250),
				pItemUpdateBlock->mTransform.vScale.y * 0.5f - 1.0f,
				Ogre::Math::RangeRandom(-250, 250));
			pItemUpdateBlock->renderGroupQueue = 1;
			pItemUpdateBlock->visibilityFlags = 1;
			pItemUpdateBlock->interpolateByDefault = false;
			pItemUpdateBlock->interpolateNextDraw = true;
			pItemUpdateBlock->castShadows = true;

			ItemDefinition * pItemDefinition = new ItemDefinition;
			pItemDefinition->meshName = "Cube_d.mesh";
			pItemDefinition->resourceGroup = Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME;
			pItemDefinition->mMoType = MoTypeItem;

			mpSetCubes[i] = new OGraphics::GameItem(
				geMgr->popAssignableId(),
				Ogre::SCENE_STATIC,
				pItemDefinition,
				pItemUpdateBlockGroup);

			mpSetCubes[i]->overwriteAllUpdateBlocks(0);

			geMgr->addGameEntity(mpSetCubes[i]);
		}
		//==============================================================
		{
			DirectionalLightUpdateBlockGroup * pUpdateBlockGroup = GameDirectionalLight::getNewUpdateBlockGroup();
			DirectionalLightUpdateBlock * pUpdateBlock = &(pUpdateBlockGroup->mUpdateBlocks[0]);
			pUpdateBlock->mTransform._reset();
			pUpdateBlock->powerScale = 1.0f;
			pUpdateBlock->direction = Ogre::Vector3(-1, -1, -1).normalisedCopy();
			pUpdateBlock->castShadows = true;
			pUpdateBlock->specular = Ogre::ColourValue(0.0008f, 0.0004f, 0.0002f);
			pUpdateBlock->diffuse = Ogre::ColourValue(1.0f, 0.8f, 0.8f); // SUN GOING DOWN? Ogre::ColourValue(1.0f, 0.4f, 0.2f); powerScale = 6.0f;
			pUpdateBlock->renderGroupQueue = 1;
			pUpdateBlock->visibilityFlags = 1;
			pUpdateBlock->interpolateByDefault = false;
			pUpdateBlock->interpolateNextDraw = true;
			pUpdateBlock->ambientLight.envMapScale = 1.0f;
			pUpdateBlock->ambientLight.hemisphereDir = -Ogre::Vector3(-1, -1, -1).normalisedCopy() + Ogre::Vector3::UNIT_Y * 0.2f;
			pUpdateBlock->ambientLight.lowerHemisphere = Ogre::ColourValue(0.6f, 0.45f, 0.3f) * 0.065f * 0.75f;
			pUpdateBlock->ambientLight.upperHemisphere = Ogre::ColourValue(0.3f, 0.5f, 0.7f) * 0.1f * 0.75f;

			BasicLightDefinition * pDefinition = new BasicLightDefinition;
			pDefinition->lightType = Ogre::Light::LT_DIRECTIONAL;

			mpLightNodes[0] = new OGraphics::GameDirectionalLight(
				geMgr->popAssignableId(),
				Ogre::SCENE_DYNAMIC,
				pDefinition,
				pUpdateBlockGroup);

			mpLightNodes[0]->overwriteAllUpdateBlocks(0);

			geMgr->addGameEntity(mpLightNodes[0]);
		}
		//==============================================================
		{
			SpotLightUpdateBlockGroup * pUpdateBlockGroup = GameSpotLight::getNewUpdateBlockGroup();
			SpotLightUpdateBlock * pUpdateBlock = &(pUpdateBlockGroup->mUpdateBlocks[0]);
			pUpdateBlock->mTransform._reset();
			pUpdateBlock->powerScale = Ogre::Math::PI;
			pUpdateBlock->diffuse = Ogre::ColourValue(0.8f,0.4f,0.2f);
			pUpdateBlock->specular = Ogre::ColourValue(0.00008f, 0.00004f, 0.00002f);
			pUpdateBlock->direction = Ogre::Vector3(1, -1, -1).normalisedCopy();
			pUpdateBlock->castShadows = true;
			pUpdateBlock->attenRadius = 10.0f;
			pUpdateBlock->attenLumThresh = 0.01f;
			pUpdateBlock->renderGroupQueue = 1;
			pUpdateBlock->visibilityFlags = 1;
			pUpdateBlock->interpolateByDefault = false;
			pUpdateBlock->interpolateNextDraw = true;
			pUpdateBlock->mTransform.vPos = Ogre::Vector3(-10.0f, 10.0f, 10.0f);

			BasicLightDefinition * pDefinition = new BasicLightDefinition;
			pDefinition->lightType = Ogre::Light::LT_SPOTLIGHT;

			mpLightNodes[1] = new OGraphics::GameSpotLight(
				geMgr->popAssignableId(),
				Ogre::SCENE_DYNAMIC,
				pDefinition,
				pUpdateBlockGroup);

			mpLightNodes[1]->overwriteAllUpdateBlocks(0);

			geMgr->addGameEntity(mpLightNodes[1]);
		}
		//==============================================================
		{
			SpotLightUpdateBlockGroup * pUpdateBlockGroup = GameSpotLight::getNewUpdateBlockGroup();
			SpotLightUpdateBlock * pUpdateBlock = &(pUpdateBlockGroup->mUpdateBlocks[0]);
			pUpdateBlock->mTransform._reset();
			pUpdateBlock->powerScale = Ogre::Math::PI;
			pUpdateBlock->diffuse = Ogre::ColourValue(0.2f, 0.4f, 0.8f);
			pUpdateBlock->specular = Ogre::ColourValue(0.00002f, 0.00004f, 0.00008f);
			pUpdateBlock->direction = Ogre::Vector3(-1, -1, 1).normalisedCopy();
			pUpdateBlock->castShadows = true;
			pUpdateBlock->attenRadius = 10.0f;
			pUpdateBlock->attenLumThresh = 0.01f;
			pUpdateBlock->renderGroupQueue = 1;
			pUpdateBlock->visibilityFlags = 1;
			pUpdateBlock->interpolateByDefault = false;
			pUpdateBlock->interpolateNextDraw = true;
			pUpdateBlock->mTransform.vPos = Ogre::Vector3(10.0f, 10.0f, -10.0f);

			BasicLightDefinition * pDefinition = new BasicLightDefinition;
			pDefinition->lightType = Ogre::Light::LT_SPOTLIGHT;

			mpLightNodes[2] = new OGraphics::GameSpotLight(
				geMgr->popAssignableId(),
				Ogre::SCENE_DYNAMIC,
				pDefinition,
				pUpdateBlockGroup);

			mpLightNodes[2]->overwriteAllUpdateBlocks(0);

			geMgr->addGameEntity(mpLightNodes[2]);
		}
		//==============================================================
		{
			SpotLightUpdateBlockGroup * pUpdateBlockGroup = GameSpotLight::getNewUpdateBlockGroup();
			SpotLightUpdateBlock * pUpdateBlock = &(pUpdateBlockGroup->mUpdateBlocks[0]);
			pUpdateBlock->mTransform._reset();
			pUpdateBlock->powerScale = Ogre::Math::PI;
			pUpdateBlock->diffuse = Ogre::ColourValue(1.0f, 0.0f, 1.0f);
			pUpdateBlock->specular = Ogre::ColourValue(0.00002f, 0.00004f, 0.00008f);
			pUpdateBlock->direction = Ogre::Vector3(0, 0, 0).normalisedCopy();
			pUpdateBlock->attenRadius = 10.0f;
			pUpdateBlock->attenLumThresh = 0.01f;
			pUpdateBlock->castShadows = true;
			pUpdateBlock->renderGroupQueue = 1;
			pUpdateBlock->visibilityFlags = 1;
			pUpdateBlock->interpolateByDefault = false;
			pUpdateBlock->interpolateNextDraw = true;
			pUpdateBlock->mTransform.vPos = Ogre::Vector3(0.0f, 2.0f, 1.0f);

			BasicLightDefinition * pDefinition = new BasicLightDefinition;
			pDefinition->lightType = Ogre::Light::LT_SPOTLIGHT;

			mpLightNodes[3] = new OGraphics::GameSpotLight(
				geMgr->popAssignableId(),
				Ogre::SCENE_DYNAMIC,
				pDefinition,
				pUpdateBlockGroup);

			mpLightNodes[3]->overwriteAllUpdateBlocks(0);

			geMgr->addGameEntity(mpLightNodes[3]);
		}
		//==============================================================
		{
			mNumLights = 32;
			mLightRadius = 10.0f;
			mLowThreshold = false;

			std::vector<GameEntity*>::iterator itor = mGeneratedLights.begin();
			std::vector<GameEntity*>::iterator end = mGeneratedLights.end();
			while (itor != end)
			{
				geMgr->removeGameEntity(*itor);
				++itor;
			}
			mGeneratedLights.clear();

			//Deterministic randomness
			srand(101);

			for (Ogre::uint32 i = 0; i < mNumLights; ++i)
			{
				PointLightUpdateBlockGroup * pUpdateBlockGroup = GamePointLight::getNewUpdateBlockGroup();
				PointLightUpdateBlock * pUpdateBlock = &(pUpdateBlockGroup->mUpdateBlocks[0]);
				pUpdateBlock->mTransform._reset();
				pUpdateBlock->powerScale = Ogre::Math::PI;
				pUpdateBlock->attenRadius = mLightRadius;
				pUpdateBlock->attenLumThresh = mLowThreshold ? 0.00192f : 0.0192f;
				pUpdateBlock->castShadows = false;
				pUpdateBlock->renderGroupQueue = 1;
				pUpdateBlock->visibilityFlags = 1;
				pUpdateBlock->interpolateByDefault = false;
				pUpdateBlock->interpolateNextDraw = true;
				pUpdateBlock->mTransform.vPos = Ogre::Vector3(
					Ogre::Math::RangeRandom(-250, 250),
					Ogre::Math::RangeRandom(2.0f, 10.0f),
					Ogre::Math::RangeRandom(-250, 250));

				BasicLightDefinition * pDefinition = new BasicLightDefinition;
				pDefinition->lightType = Ogre::Light::LT_POINT;

				if (i & 1)
				{
					pUpdateBlock->diffuse = Ogre::ColourValue(0.2f, 0.4f, 0.8f); //Cold
//					pUpdateBlock->specular = Ogre::ColourValue(0.2f, 0.4f, 0.8f);
					pUpdateBlock->specular = Ogre::ColourValue(0.00002f, 0.00004f, 0.00008f);
				}
				else
				{
					pUpdateBlock->diffuse = Ogre::ColourValue(0.8f, 0.4f, 0.2f); //Warm
//					pUpdateBlock->specular = Ogre::ColourValue(0.8f, 0.4f, 0.2f);
					pUpdateBlock->specular = Ogre::ColourValue(0.00008f, 0.00004f, 0.00002f);
				}

				GameEntity * pLight = new OGraphics::GamePointLight(
					geMgr->popAssignableId(),
					Ogre::SCENE_DYNAMIC,
					pDefinition,
					pUpdateBlockGroup);

				pLight->overwriteAllUpdateBlocks(0);

				geMgr->addGameEntity(pLight);
				mGeneratedLights.push_back(pLight);
			}
		}
		//==============================================================
		{
			TextUpdateBlockGroup * pUpdateBlockGroup = GameText::getNewUpdateBlockGroup();
			TextUpdateBlock * pUpdateBlock = &(pUpdateBlockGroup->mUpdateBlocks[0]);
			pUpdateBlock->mTransform._reset();
			pUpdateBlock->renderGroupQueue = 2;
			pUpdateBlock->visibilityFlags = 1;
			pUpdateBlock->interpolateByDefault = true;

			pUpdateBlock->mTransform.vPos = Ogre::Vector3(0.0f, 15.0f, 0.0f);

//			pUpdateBlock->mTransform.vPos = Ogre::Vector3(
//				Ogre::Math::RangeRandom(-250, 250),
//				Ogre::Math::RangeRandom(2.0f, 10.0f),
//				Ogre::Math::RangeRandom(-250, 250));

//			pUpdateBlock->mTransform.vScale = Ogre::Vector3(
//				Ogre::Math::RangeRandom(-250, 250),
//				Ogre::Math::RangeRandom(2.0f, 10.0f),
//				Ogre::Math::RangeRandom(-250, 250));


			pUpdateBlock->caption = "This is a test 2";
			pUpdateBlock->alignmentHoriz = Ogre::MovableText::H_CENTER;
			pUpdateBlock->alignmentVert = Ogre::MovableText::V_ABOVE;

			TextDefinition * pDefinition = new TextDefinition;
			pDefinition->name = "TXT_EX_Z";
			pDefinition->fontName = "DebugFont";
			pDefinition->isBillboard = true;
			pDefinition->textSize = 1.0f;

			mpTextZ = new OGraphics::GameText(
				geMgr->popAssignableId(),
				Ogre::SCENE_DYNAMIC,
				pDefinition,
				pUpdateBlockGroup);

			mpTextZ->overwriteAllUpdateBlocks(0);
			geMgr->addGameEntity(mpTextZ);
		}
	}

//===========================================================================
	GameEntity * F3DMultiLogicGameState::createTestCube()
	{
		const Ogre::Vector3 origin(-5.0f + mCubeEntities.size(), 0.0f, 0.0f);
		GameEntityManager *geMgr = mpLogicSystem->getGameEntityManager();

		ItemDefinition * pItemDefinition = new ItemDefinition;
		pItemDefinition->meshName = "Cube_d.mesh";
		pItemDefinition->resourceGroup = Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME;
		pItemDefinition->mMoType = MoTypeItem;

		ItemUpdateBlockGroup * pItemUpdateBlockGroup = GameItem::getNewUpdateBlockGroup();

		GameEntity * pCubeEntity =
			new OGraphics::GameItem(
			geMgr->popAssignableId(),
			Ogre::SCENE_DYNAMIC,
			pItemDefinition,
			pItemUpdateBlockGroup);

		ItemUpdateBlock * pUpdateBlock = &(pItemUpdateBlockGroup->mUpdateBlocks[0]);
		pUpdateBlock->renderGroupQueue = 1;
		pUpdateBlock->visibilityFlags = 1;
		pUpdateBlock->interpolateByDefault = false;
		pUpdateBlock->interpolateNextDraw = true;
		pUpdateBlock->castShadows = false;

		GameEntityTransform * pTransform = &(pItemUpdateBlockGroup->mUpdateBlocks[0].mTransform);  
		pTransform->vPos = origin;
		pTransform->qRot = Ogre::Quaternion::IDENTITY;
		pTransform->vScale = Ogre::Vector3::UNIT_SCALE;

		pCubeEntity->overwriteAllUpdateBlocks(0);

		return pCubeEntity;
	}

	//-----------------------------------------------------------------------------------
	void F3DMultiLogicGameState::update(float timeSinceLast)
	{
		const size_t currIdx = mpLogicSystem->getCurrentTransformIdx();

		if (true)
		{
			for (int i = 0; i < 16; ++i)
			{
				ItemUpdateBlock * pUpdateBlock = static_cast<ItemUpdateBlock*>(mpCubes[i]->getUpdateBlock(currIdx));
				pUpdateBlock->mTransform.qRot.FromAngleAxis(pUpdateBlock->mTransform.qRot.getYaw() + Ogre::Radian(timeSinceLast * i * 0.125f), Ogre::Vector3::UNIT_Y);
				mpCubes[i]->updateLogic(timeSinceLast, currIdx);
			}

			{
				ItemUpdateBlock * pUpdateBlock = static_cast<ItemUpdateBlock*>(mpMovingCube->getUpdateBlock(currIdx));
				float xPos = pUpdateBlock->mTransform.vPos.x;
				pUpdateBlock->mTransform.vPos.x = xPos + (2.0f * timeSinceLast);
				if (pUpdateBlock->mTransform.vPos.x > 5.0f)
				{
					pUpdateBlock->mTransform.vPos.x = -5.0f;
				}
				mpMovingCube->updateLogic(timeSinceLast, currIdx);
			}
		}

		if (mCubeEntities.size() > 0)
		{
			mDisplacement += timeSinceLast * 4.0f;
			mDisplacement = fmodf(mDisplacement, 10.0f);

			for (int i = 0; i < mCubeEntities.size(); ++i)
			{
				mCubeEntities.at(i)->updateLogic(timeSinceLast, currIdx);
			}
		}
		IGameState::update(timeSinceLast);
	}

	void F3DMultiLogicGameState::keyReleased(const SDL_KeyboardEvent &arg)
	{
		if (arg.keysym.sym == SDLK_z)
		{
			GameEntityManager *geMgr = mpLogicSystem->getGameEntityManager();
			if (mCubeEntities.size())
			{
				GameEntity * pEnt = mCubeEntities.back();
				mCubeEntities.pop_back();
				geMgr->removeGameEntity(pEnt);
			}
		}
		if (arg.keysym.sym == SDLK_v)
		{
			GameEntityManager *geMgr = mpLogicSystem->getGameEntityManager();
			GameEntity * pCubeEntity = createTestCube();
			mCubeEntities.push_front(pCubeEntity);
			geMgr->addGameEntity(pCubeEntity);
		}
	}

};