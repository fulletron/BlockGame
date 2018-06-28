#ifndef _FORWARD3DGAMESTATE_H_
#define _FORWARD3DGAMESTATE_H_

#include "OgrePrerequisites.h"
#include "Overlay/OgreOverlayPrerequisites.h"
#include "gamestate.h"

#include "OgreCommon.h"

#define USE_BASEWORLDNODE 1

#define USE_RQGROUP_VISFLAGS 0
#define D_VISIBILITYFLAG_1 0x000000001
#define D_VISIBILITYFLAG_2 0x000000002

namespace OGraphics
{
	class Forward3DGameState : public GameState
	{
		Ogre::SceneNode     *mSceneNode[16];

		Ogre::SceneNode     *mLightNodes[3];
		Ogre::SceneNode     *mLightNode4;

		bool                mAnimateObjects;

		Ogre::uint32				mCurrentForward3DPreset;
		static const Ogre::uint8	mNumPresets;

		Ogre::LightArray    mGeneratedLights;
		Ogre::uint32        mNumLights;
		float               mLightRadius;
		bool                mLowThreshold;

		virtual void generateDebugText(float timeSinceLast, Ogre::String &outText);

		void changeForward3DPreset(bool goForward);

		void generateLights(void);

		// KYLE :: 
		Ogre::SceneNode		*mUIQUAD;
		void generateUIQuad(void);

	public:
		Forward3DGameState(const Ogre::String &helpDescription);

		virtual void createScene01(void);

		virtual void update(float timeSinceLast);

		virtual void keyReleased(const SDL_KeyboardEvent &arg);
	};
}

#endif
