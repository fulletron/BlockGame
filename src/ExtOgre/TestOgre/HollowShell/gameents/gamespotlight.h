#ifndef _GAMESPOTLIGHT_H_
#define _GAMESPOTLIGHT_H_

#include "gameentity.h"
#include <mutex>

namespace OGraphics
{
	class SpotLightUpdateBlock : public GameEntityUpdateBlock
	{
	public:
		// Directional and Spot Specific
		Ogre::Vector3				direction;

		// Point and Spot Specific
		Ogre::ColourValue			diffuse;
		Ogre::ColourValue			specular;
		Ogre::Real					attenRadius;
		Ogre::Real					attenLumThresh;

		// All Lights
		Ogre::Real					powerScale;
		bool						castShadows;
	};

	class SpotLightUpdateBlockGroup
	{
	public:
		SpotLightUpdateBlock mUpdateBlocks[NUM_GAME_ENTITY_BUFFERS];
	};

	class GameSpotLight : public GameEntity
	{
	public:
		static std::mutex								sUnusedUpdateBlockGroupsMutex;
		static std::vector<SpotLightUpdateBlockGroup *>		sUnusedUpdateBlockGroups;

	public:
		BasicLightDefinition * mpLightDefinition;
		SpotLightUpdateBlockGroup * mpUpdateBlockGroup;

		GameSpotLight(Ogre::uint32 id,
			Ogre::SceneMemoryMgrTypes a_sceneType,
			BasicLightDefinition *pDefinition,
			SpotLightUpdateBlockGroup * pUpdateBlockGroup) :
			GameEntity(id, a_sceneType),
			mpLightDefinition(pDefinition),
			mpUpdateBlockGroup(pUpdateBlockGroup)
		{
			mpLightDefinition->mMoType = MoTypeSpotLight;
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
		static SpotLightUpdateBlockGroup * getNewUpdateBlockGroup();
	};
};

#endif