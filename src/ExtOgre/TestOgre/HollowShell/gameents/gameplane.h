#ifndef _GAMEPLANE_H_
#define _GAMEPLANE_H_

#include "gameentity.h"
#include <mutex>

namespace OGraphics
{
	class PlaneDefinition : public GameEntityDefinition
	{
	public:
		Ogre::String        meshName;
		Ogre::String		meshV1Name;
		Ogre::String        resourceGroup;
		Ogre::StringVector  submeshMaterials;
		Ogre::Plane			plane;
		int					xsegments;
		int					ysegments;
		bool				normals;
		unsigned short		numTexCoordSets;
		Ogre::Real			uTile;
		Ogre::Real			vTile;
		Ogre::Vector3		upVector;
	};

	class PlaneUpdateBlock : public GameEntityUpdateBlock
	{
	public:
		Ogre::Real			length;
		Ogre::Real			width;
	};

	class PlaneUpdateBlockGroup
	{
	public:
		PlaneUpdateBlock mUpdateBlocks[NUM_GAME_ENTITY_BUFFERS];
	};

	class GamePlane : public GameEntity
	{
	public:
		static std::mutex								sUnusedUpdateBlockGroupsMutex;
		static std::vector<PlaneUpdateBlockGroup *>		sUnusedUpdateBlockGroups;

	public:
		PlaneDefinition * mpDefinition;
		PlaneUpdateBlockGroup * mpUpdateBlockGroup;

		GamePlane(Ogre::uint32 id,
			Ogre::SceneMemoryMgrTypes a_sceneType,
			PlaneDefinition *pDefinition,
			PlaneUpdateBlockGroup * pUpdateBlockGroup) :
			GameEntity(id, a_sceneType),
			mpDefinition(pDefinition),
			mpUpdateBlockGroup(pUpdateBlockGroup)
		{
			mpDefinition->mMoType = MoTypePlane;
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
		static PlaneUpdateBlockGroup * getNewUpdateBlockGroup();
	};
};

#endif