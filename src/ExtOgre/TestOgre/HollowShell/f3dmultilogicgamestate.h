#ifndef _F3DMULTILOGICGAMESTATE_H_
#define _F3DMULTILOGICGAMESTATE_H_

#include "OgrePrerequisites.h"
#include "gamestate.h"

// INPUT
#include "sdlemulationlayer.h"

#if OGRE_USE_SDL2
#include <SDL.h>
#endif

#include <deque>

namespace OGraphics
{
	class LogicSystem;
	class GameEntity;
	class GameEntityTransform;

	class F3DMultiLogicGameState : public IGameState
	{
		float               mDisplacement;

		std::deque<GameEntity*> mCubeEntities;

		LogicSystem         *mpLogicSystem;

		Ogre::uint32				mCurrentForward3DPreset;

		GameEntity *				mpPlane;
		GameEntity *				mpMovingCube;
		GameEntity *				mpCubes[16];
		GameEntity *				mpSetCubes[64];
		GameEntity *				mpLightNodes[3];
		Ogre::uint32				mNumLights;
		std::vector<GameEntity*>	mGeneratedLights;
		GameEntity *				mpTextZ;

		float						mLightRadius;
		bool						mLowThreshold;


	public:
		F3DMultiLogicGameState();
		~F3DMultiLogicGameState();

		void _notifyLogicSystem(LogicSystem *pLogicSystem)     { mpLogicSystem = pLogicSystem; }

		/*
		* Creation of actual game entities happens here.
		*/
		virtual void createScene01(void);

		/*
		* The moving of objects happens here
		*/
		virtual void update(float timeSinceLast);

		/*
		* ADDED KYLE ::
		*/
		virtual void keyReleased(const SDL_KeyboardEvent &arg);

		/*
		* ADDED KYLE :: 
		*/
		GameEntity * createTestCube();
		//GameEntity * createTestCube(GameEntityTransform * geT);
	};
}

#endif