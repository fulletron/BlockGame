#include "gamestate.h"
#include "cameracontroller.h"

#include "graphicssystem.h"

#include "OgreSceneManager.h"
#include "Overlay/OgreOverlay.h"
#include "Overlay/OgreOverlayContainer.h"
#include "Overlay/OgreTextAreaOverlayElement.h"
#include "Overlay/OgreOverlayManager.h"

#include "OgreRoot.h"
#include "OgreFrameStats.h"

#include "OgreHlmsManager.h"
#include "OgreHlms.h"
#include "OgreHlmsCompute.h"
#include "OgreGpuProgramManager.h"

using namespace OGraphics;

namespace OGraphics
{

GameState::GameState(const Ogre::String &helpDescription ) :
	mpGraphicsSystem(0),
	mpCameraController(0),
	mHelpDescription(helpDescription),
	mDisplayHelpMode(1),
	mNumDisplayHelpModes(2),
	mpDebugText(0)
	{
	}

GameState::~GameState()
{
	delete mpCameraController;
	mpCameraController = 0;
}

void GameState::_notifyGraphicsSystem(GraphicsSystem * pGraphicsSystem)
{
	mpGraphicsSystem = pGraphicsSystem;
}

void GameState::createScene01(void)
{
	createDebugTextOverlay();
}

void GameState::createDebugTextOverlay(void)
{
	Ogre::v1::OverlayManager &overlayManager = Ogre::v1::OverlayManager::getSingleton();
	Ogre::v1::Overlay *overlay = overlayManager.create("DebugText");

	Ogre::v1::OverlayContainer *panel = static_cast<Ogre::v1::OverlayContainer*>(
		overlayManager.createOverlayElement("Panel","DebugPanel"));
	mpDebugText = static_cast<Ogre::v1::TextAreaOverlayElement*>(
		overlayManager.createOverlayElement("TextArea", "DebugText"));
	mpDebugText->setFontName("DebugFont");
	mpDebugText->setCharHeight( 0.025f );

	mpDebugTextShadow = static_cast<Ogre::v1::TextAreaOverlayElement*>(
		overlayManager.createOverlayElement("TextArea","0DebugTextShadow"));
	mpDebugTextShadow->setFontName("DebugFont");
	mpDebugTextShadow->setCharHeight(0.025f);
	mpDebugTextShadow->setColour(Ogre::ColourValue::Black);
	mpDebugTextShadow->setPosition( 0.002f, 0.002f );

	panel->addChild( mpDebugTextShadow );
	panel->addChild( mpDebugText );
	overlay->add2D( panel );
	overlay->show();
}

void GameState::generateDebugText(float timeSinceLast, Ogre::String &outText)
{
	if (mDisplayHelpMode == 0)
	{
		outText = mHelpDescription;
		outText += "\n\nPress F1 to toggle help";
		outText += "\n\nProtip: Ctrl+F1 will reload PBS shaders (for real time template editing).\n"
			"Ctrl+F2 reloads Unlit shaders.\n"
			"Ctrl+F3 reloads Compute shaders.\n"
			"Note: If the modified templates produce invalid shader code, "
			"crashes or exceptions can happen.\n";
		return;
	}

	const Ogre::FrameStats *frameStats = mpGraphicsSystem->getRoot()->getFrameStats();

	Ogre::String finalText;
	finalText.reserve(128);
	finalText = "Frame time:\t";
	finalText += Ogre::StringConverter::toString(timeSinceLast * 1000.0f);
	finalText += " ms\n";
	finalText += "Frame FPS:\t";
	finalText += Ogre::StringConverter::toString(1.0f / timeSinceLast);
	finalText += "\nAvg time:\t";
	finalText += Ogre::StringConverter::toString(frameStats->getAvgTime());
	finalText += " ms\n";
	finalText += "Avg FPS:\t";
	finalText += Ogre::StringConverter::toString(1000.0f / frameStats->getAvgTime());
	finalText += "\n\nPress F1 to toggle help";

	outText.swap(finalText);

	mpDebugText->setCaption(finalText);
	mpDebugTextShadow->setCaption(finalText);
}

void GameState::update( float timeSinceLast )
{
	if (mDisplayHelpMode != 0)
	{
		//Show FPS
		Ogre::String finalText;
		generateDebugText(timeSinceLast, finalText);
		mpDebugText->setCaption(finalText);
		mpDebugTextShadow->setCaption(finalText);
	}

	if (mpCameraController)
		mpCameraController->update(timeSinceLast);
}

void GameState::keyPressed(const SDL_KeyboardEvent &arg)
{
	bool handledEvent = false;

	if (mpCameraController)
		handledEvent = mpCameraController->keyPressed(arg);

	if (!handledEvent)
		IGameState::keyPressed(arg);
}

void GameState::keyReleased(const SDL_KeyboardEvent &arg)
{
	if (arg.keysym.sym == SDLK_F1 && (arg.keysym.mod & ~(KMOD_NUM | KMOD_CAPS)) == 0)
	{
		mDisplayHelpMode = (mDisplayHelpMode + 1) % mNumDisplayHelpModes;

		Ogre::String finalText;
		generateDebugText(0, finalText);
		mpDebugText->setCaption(finalText);
		mpDebugTextShadow->setCaption(finalText);
	}
	else if (arg.keysym.sym == SDLK_F1 && (arg.keysym.mod & (KMOD_LCTRL | KMOD_RCTRL)))
	{
		//Hot reload of PBS shaders. We need to clear the microcode cache
		//to prevent using old compiled versions.
		Ogre::Root *root = mpGraphicsSystem->getRoot();
		Ogre::HlmsManager *hlmsManager = root->getHlmsManager();

		Ogre::Hlms *hlms = hlmsManager->getHlms(Ogre::HLMS_PBS);
		Ogre::GpuProgramManager::getSingleton().clearMicrocodeCache();
		hlms->reloadFrom(hlms->getDataFolder());
	}
	else if (arg.keysym.sym == SDLK_F2 && (arg.keysym.mod & (KMOD_LCTRL | KMOD_RCTRL)))
	{
		//Hot reload of Unlit shaders.
		Ogre::Root *root = mpGraphicsSystem->getRoot();
		Ogre::HlmsManager *hlmsManager = root->getHlmsManager();

		Ogre::Hlms *hlms = hlmsManager->getHlms(Ogre::HLMS_UNLIT);
		Ogre::GpuProgramManager::getSingleton().clearMicrocodeCache();
		hlms->reloadFrom(hlms->getDataFolder());
	}
	else if (arg.keysym.sym == SDLK_F3 && (arg.keysym.mod & (KMOD_LCTRL | KMOD_RCTRL)))
	{
		//Hot reload of Unlit shaders.
		Ogre::Root *root = mpGraphicsSystem->getRoot();
		Ogre::HlmsManager *hlmsManager = root->getHlmsManager();

		Ogre::Hlms *hlms = hlmsManager->getComputeHlms();
		Ogre::GpuProgramManager::getSingleton().clearMicrocodeCache();
		hlms->reloadFrom(hlms->getDataFolder());
	}
	else
	{
		bool handledEvent = false;

		if (mpCameraController)
			handledEvent = mpCameraController->keyReleased(arg);

		if (!handledEvent)
			IGameState::keyReleased(arg);
	}
}

void GameState::mouseMoved(const SDL_Event &arg)
{
	if (mpCameraController)
		mpCameraController->mouseMoved(arg);

	IGameState::mouseMoved(arg);
}

};