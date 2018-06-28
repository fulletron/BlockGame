#ifndef _GAMEENTITY_H_
#define _GAMEENTITY_H_

#include "OgreVector3.h"
#include "OgreQuaternion.h"
#include "OgreStringVector.h"

// Ogre::Light::LightTypes, Ogre::ColourValue
#include "OgreLight.h"

class Ogre::SceneManager;

namespace OGraphics
{
	class GraphicsSystem;

#define NUM_GAME_ENTITY_BUFFERS 4

	enum MovableObjectType
	{
		MoTypeItem,
		MoTypeEntity,
		MoTypePointLight,
		MoTypeSpotLight,
		MoTypeDirectionalLight,
		MoTypePlane,
		MoTypeText,
		NumMovableObjectType
	};

	/*
	* All Game Entities will have a 
	* GameEntityTransform
	*/
	class GameEntityTransform
	{
	public:
		Ogre::Vector3       vPos;
		Ogre::Quaternion    qRot;
		Ogre::Vector3       vScale;

		GameEntityTransform(){ _reset(); }

		void _reset(){
			vPos = Ogre::Vector3::ZERO;
			qRot = Ogre::Quaternion::IDENTITY;
			vScale = Ogre::Vector3::UNIT_SCALE;
		}
	};

	class GameEntityDefinition
	{
	public:
		// KYLE :: can also be a light
		Ogre::MovableObject     *mMovableObject; //Could be Entity, InstancedEntity, Item.

		// KYLE :: Might not be necessary
		MovableObjectType				mMoType;

		// TODO :: KYLE :: moved from GameEntity
		//Ogre::SceneMemoryMgrTypes       mSceneType;
	};

	class GameEntityUpdateBlock
	{
	public:
		Ogre::uint8 renderGroupQueue;
		Ogre::uint32 visibilityFlags;

		// While directional lights don't have an initial transform, they still
		// belong to a sceneNode, which NEEDS one
		// In fact, everything that is a GameEntity attaches to a sceneNode,
		// and they all need a transform.
		GameEntityTransform mTransform;

		bool interpolateByDefault;
		bool interpolateNextDraw;

		bool isDirty;
	};

	class BasicLightDefinition : public GameEntityDefinition
	{
	public:
		// Basic
		Ogre::Light::LightTypes lightType;
	};

	class GameEntity
	{
	private:
		Ogre::uint32 mId;

		// KYLE :: Copy Constructors not needed
		//GameEntity(const GameEntity& that);
		//GameEntity& operator=(GameEntity const&);

	public:
		//----------------------------------------
		// Only used by Graphics thread
		//----------------------------------------
		Ogre::SceneNode         *mSceneNode;


		GameEntity * mpParentEntity;

		//Your custom pointers go here, i.e. physics representation.
		//used only by Logic thread (hkpEntity, btRigidBody, etc)

		//----------------------------------------
		// Used by both Logic and Graphics threads
		//----------------------------------------
//		GameEntityUpdateBlock   *mUpdateBlock;
//		GameEntityTransform     *mTransform[NUM_GAME_ENTITY_BUFFERS];
		Ogre::SceneMemoryMgrTypes       mSceneType;
		// ENTITY_MANAGER_TODO :: Parent Entity, Tag Point?

		//----------------------------------------
		// Read-only
		//----------------------------------------
		//MovableObjectDefinition const   *mMoDefinition;

//		size_t                   mTransformBufferIdx;
		GameEntity(Ogre::uint32 id, 
			Ogre::SceneMemoryMgrTypes a_scenetype)
			:
			mId(id),
			mSceneNode(0),
			mpParentEntity(0),
			//mMovableObject(0),
			mSceneType(a_scenetype)
//			,
//			mTransformBufferIdx(0)
		{
//			for (int i = 0; i<NUM_GAME_ENTITY_BUFFERS; ++i)
//				mTransform[i] = 0;
		}

		Ogre::uint32 getId(void) const          { return mId; }
		//MovableObjectType getMoType(void) const { return mMoType; }

		/*
		* Logic add
		*/
		virtual int onGameEntityAdd() = 0;

		/*
		* Graphics Add
		*/
		//virtual int onGameEntityAdded(Ogre::SceneManager * pSceneManager, const GameEntityTransform & initialTransform) = 0;
		//virtual int onGameEntityAdded(Ogre::SceneManager * pSceneManager) = 0;
		virtual int onGameEntityAdded(OGraphics::GraphicsSystem * pGraphicsSystem) = 0;

		/*
		* GraphicsUpdate
		*/
		virtual int updateGraphics(const size_t & currentIdx, float interpolationWeight) = 0;

		/*
		* Logic Update
		*/
		virtual int updateLogic(float timeSinceLast, const size_t & currentIdx) = 0;

		/*
		* Logic Remove
		*/
		virtual int onGameEntityRemove() = 0;

		/*
		* Graphics Remove
		*/
		virtual int onGameEntityRemoved(Ogre::SceneManager * pSceneManager) = 0;

		virtual int overwriteAllUpdateBlocks(int master_index) = 0;

		virtual void * getUpdateBlock(int idx) = 0;

		bool operator < (const GameEntity *_r) const
		{
			return mId < _r->mId;
		}

		static bool OrderById(const GameEntity *_l, const GameEntity *_r)
		{
			return _l->mId < _r->mId;
		}
	};

	typedef std::vector<GameEntity*> GameEntityVec;
/*

	class GamePointLight : public GameEntity
	{
	public:
		PointLightDefinition const * mpDefinition;

		GamePointLight(Ogre::uint32 id,
			Ogre::SceneMemoryMgrTypes a_sceneType,
			const PointLightDefinition *pPointLightDefinition) :
			GameEntity(id, a_sceneType),
			mpDefinition(pPointLightDefinition)
		{
			mMoType = MoTypeLight;
			for (int i = 0; i<NUM_GAME_ENTITY_BUFFERS; ++i)
				mTransform[i] = 0;
		}
	};
*/

};

#endif