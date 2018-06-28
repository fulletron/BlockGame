#ifndef _GAMEDIRECTIONALLIGHT_H_
#define _GAMEDIRECTIONALLIGHT_H_

#include "gameentity.h"
#include <mutex>

namespace OGraphics
{

	/*
	* This calls sceneManager->setAmbientLight,
	* which means only one can be in effect at
	* any given time.
	*/
	struct AmbientDirectionalLight
	{
	Ogre::ColourValue upperHemisphere;
	Ogre::ColourValue lowerHemisphere;
	Ogre::Vector3 hemisphereDir;
	Ogre::Real envMapScale;
	};

	class DirectionalLightUpdateBlock : public GameEntityUpdateBlock
	{
	public:
		// Directional Specific
		AmbientDirectionalLight		ambientLight;

		// Directional and Spot Specific
		Ogre::Vector3				direction;

		// These weren't in the tutorial, but appear to have an effect on the light
		Ogre::ColourValue			diffuse;
		Ogre::ColourValue			specular;

		// All Lights
		Ogre::Real					powerScale;
		bool						castShadows;
	};

	class DirectionalLightUpdateBlockGroup
	{
	public:
		DirectionalLightUpdateBlock mUpdateBlocks[NUM_GAME_ENTITY_BUFFERS];
	};

	class GameDirectionalLight : public GameEntity
	{
	public:
		static std::mutex												sUnusedUpdateBlockGroupsMutex;
		static std::vector<DirectionalLightUpdateBlockGroup *>			sUnusedUpdateBlockGroups;

	public:
		BasicLightDefinition * mpLightDefinition;
		DirectionalLightUpdateBlockGroup * mpUpdateBlockGroup;

		GameDirectionalLight(Ogre::uint32 id,
			Ogre::SceneMemoryMgrTypes a_sceneType,
			BasicLightDefinition *pDefinition,
			DirectionalLightUpdateBlockGroup * pUpdateBlockGroup) :
			GameEntity(id, a_sceneType),
			mpLightDefinition(pDefinition),
			mpUpdateBlockGroup(pUpdateBlockGroup)
		{
			mpLightDefinition->mMoType = MoTypeItem;
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
		static DirectionalLightUpdateBlockGroup * getNewUpdateBlockGroup();
	};
};

#endif