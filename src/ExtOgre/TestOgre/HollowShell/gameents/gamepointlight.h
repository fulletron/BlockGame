#ifndef _GAMEPOINTLIGHT_H_
#define _GAMEPOINTLIGHT_H_

#include "gameentity.h"
#include <mutex>

namespace OGraphics
{

	class PointLightUpdateBlock : public GameEntityUpdateBlock
	{
	public:
		// Point and Spot Specific
		Ogre::ColourValue			diffuse;
		Ogre::ColourValue			specular;
		Ogre::Real					attenRadius;
		Ogre::Real					attenLumThresh;

		// All Lights
		Ogre::Real					powerScale;
		bool						castShadows;
	};

	class PointLightUpdateBlockGroup
	{
	public:
		PointLightUpdateBlock mUpdateBlocks[NUM_GAME_ENTITY_BUFFERS];
	};

	class GamePointLight : public GameEntity
	{
	public:
		static std::mutex										sUnusedUpdateBlockGroupsMutex;
		static std::vector<PointLightUpdateBlockGroup *>		sUnusedUpdateBlockGroups;

	public:
		BasicLightDefinition * mpLightDefinition;
		PointLightUpdateBlockGroup * mpUpdateBlockGroup;

		GamePointLight(Ogre::uint32 id,
			Ogre::SceneMemoryMgrTypes a_sceneType,
			BasicLightDefinition *pDefinition,
			PointLightUpdateBlockGroup * pUpdateBlockGroup) :
			GameEntity(id, a_sceneType),
			mpLightDefinition(pDefinition),
			mpUpdateBlockGroup(pUpdateBlockGroup)
		{
			mpLightDefinition->mMoType = MoTypePointLight;
		}

		/*
		* Logic add
		*/
		virtual int onGameEntityAdd();

		/*
		* Graphics Add
		*/
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
		static PointLightUpdateBlockGroup * getNewUpdateBlockGroup();
	};
};

#endif