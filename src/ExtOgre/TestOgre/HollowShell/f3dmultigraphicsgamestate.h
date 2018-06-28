#ifndef _F3DMULTIGRAPHICSGAMESTATE_H_
#define _F3DMULTIGRAPHICSGAMESTATE_H_

#include "OgrePrerequisites.h"
#include "gamestate.h"

#include "OgreVector3.h"

namespace OGraphics
{

	class GraphicsSystem;

	class F3DMultiGraphicsGameState : public GameState
	{

		bool			mEnableInterpolation;
		virtual void generateDebugText(float timeSinceLast, Ogre::String &outText);

	public:
		F3DMultiGraphicsGameState(const Ogre::String &helpDescription);

		virtual void createScene01(void);

		virtual void update(float timeSinceLast);

		virtual void keyReleased(const SDL_KeyboardEvent &arg);

	};

};

#endif