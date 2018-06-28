#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "OgrePrerequisites.h"
#include "igamestate.h"

// MOVABLETEXT :: 
#include "textblip/MovableText.h"

namespace Ogre
{
	namespace v1
	{
		class TextAreaOverlayElement;
	}
};

namespace OGraphics
{

class GraphicsSystem;
class CameraController;

class GameState : public IGameState
{
protected:
	GraphicsSystem      *mpGraphicsSystem;

	/// Optional, for controlling the camera with WASD and the mouse
	CameraController    *mpCameraController;

	Ogre::String        mHelpDescription;
	Ogre::uint16        mDisplayHelpMode;
	Ogre::uint16        mNumDisplayHelpModes;

	Ogre::v1::TextAreaOverlayElement *mpDebugText;
	Ogre::v1::TextAreaOverlayElement *mpDebugTextShadow;

	// TEXT :: 
	Ogre::MovableText * mpMovableText;
	Ogre::SceneNode * mpTextNode;

	Ogre::MovableText * mpMovableTexts[1024];
	Ogre::SceneNode * mpTextNodes[1024];

	virtual void createDebugTextOverlay(void);
	virtual void generateDebugText(float timeSinceLast, Ogre::String &outText);

public:
	GameState(const Ogre::String &helpDescription);
	virtual ~GameState();

	void _notifyGraphicsSystem(GraphicsSystem *graphicsSystem);

	virtual void createScene01(void);

	virtual void update(float timeSinceLast);

	virtual void keyPressed(const SDL_KeyboardEvent &arg);
	virtual void keyReleased(const SDL_KeyboardEvent &arg);

	virtual void mouseMoved(const SDL_Event &arg);
};

};

#endif