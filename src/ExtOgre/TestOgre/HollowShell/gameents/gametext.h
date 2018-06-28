#ifndef _GAMETEXT_H_
#define _GAMETEXT_H_

#include "gameentity.h"
#include <mutex>

#include "../textblip/MovableText.h"

namespace OGraphics
{
	class TextDefinition : public GameEntityDefinition
	{
	public:
		Ogre::String name;
		Ogre::String fontName;
		Ogre::Real textSize;
		bool isBillboard;
	};

	class TextUpdateBlock : public GameEntityUpdateBlock
	{
	public:
		Ogre::String caption;
		// Doubt these ever cast shadows
		// bool castShadows;

		Ogre::MovableText::HorizontalAlignment alignmentHoriz;
		Ogre::MovableText::VerticalAlignment alignmentVert;
	};

	class TextUpdateBlockGroup
	{
	public:
		TextUpdateBlock mUpdateBlocks[NUM_GAME_ENTITY_BUFFERS];
	};

	class GameText : public GameEntity
	{
	public:
		static std::mutex								sUnusedUpdateBlockGroupsMutex;
		static std::vector<TextUpdateBlockGroup *>		sUnusedUpdateBlockGroups;
		Ogre::MovableText * mpMovableText;

	public:
		TextDefinition * mpDefinition;
		TextUpdateBlockGroup * mpUpdateBlockGroup;

		GameText(Ogre::uint32 id,
			Ogre::SceneMemoryMgrTypes a_sceneType,
			TextDefinition *pDefinition,
			TextUpdateBlockGroup * pUpdateBlockGroup) :
			GameEntity(id, a_sceneType),
			mpDefinition(pDefinition),
			mpUpdateBlockGroup(pUpdateBlockGroup)
		{
			mpDefinition->mMoType = MoTypeText;
//			for (int i = 0; i<NUM_GAME_ENTITY_BUFFERS; ++i)
//				mTransform[i] = 0;
		}

		/*
		* Logic add
		*/
		virtual int onGameEntityAdd();

		/*
		* Graphics Add
		*/
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
		static TextUpdateBlockGroup * getNewUpdateBlockGroup();
	};
};

#endif