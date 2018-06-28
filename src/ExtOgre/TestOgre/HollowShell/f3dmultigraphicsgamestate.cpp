#include "graphicssystem.h"
#include "cameracontroller.h"

#include "f3dmultigraphicsgamestate.h"
#include "CameraController.h"
#include "GraphicsSystem.h"
#include "OgreForward3D.h"

#include "OgreSceneManager.h"
#include "OgreItem.h"

#include "OgreMeshManager.h"
#include "OgreMeshManager2.h"
#include "OgreMesh2.h"

#include "OgreCamera.h"
#include "OgreRenderWindow.h"

#include "Hlms/Unlit/OgreHlmsUnlitDatablock.h"
#include "OgreHlmsSamplerblock.h"

#include "OgreRoot.h"
#include "OgreHlmsManager.h"
#include "OgreHlms.h"
#include "Compositor/OgreCompositorWorkspace.h"
#include "Compositor/OgreCompositorShadowNode.h"

#include "Hlms/Pbs/OgreHlmsPbs.h"
#include "Hlms/Pbs/OgreHlmsPbsDatablock.h"

#include "Hlms/Unlit/OgreHlmsUnlit.h"
#include "Hlms/Unlit/OgreHlmsUnlitDatablock.h"

#include "Overlay/OgreTextAreaOverlayElement.h"

#include "Overlay/OgreOverlayManager.h"
#include "Overlay/OgreOverlayContainer.h"
#include "Overlay/OgreOverlay.h"

#include <iostream>

using namespace OGraphics;

extern const double cFrametime;
extern bool gFakeSlowmo;
extern bool gFakeFrameskip;

namespace OGraphics {

	//-------- FOR F3D -------------------------------
	struct Presets
	{
		Ogre::uint32 width;
		Ogre::uint32 height;
		Ogre::uint32 numSlices;
		Ogre::uint32 lightsPerCell;
		float minDistance;
		float maxDistance;
	};
	const Presets c_presets[] =
	{
		{ 4, 4, 5, 96, 3.0f, 200.0f },
		{ 4, 4, 4, 32, 3.0f, 100.0f },
		{ 4, 4, 4, 64, 3.0f, 200.0f },
		{ 4, 4, 4, 32, 3.0f, 200.0f },
		{ 4, 4, 7, 64, 3.0f, 150.0f },
		{ 4, 4, 3, 128, 3.0f, 200.0f },
	};
	//--------------------------------------------------

	F3DMultiGraphicsGameState::F3DMultiGraphicsGameState(const Ogre::String & helpDescription) :
		GameState(helpDescription),
		mEnableInterpolation(true)
	{
	}

	void F3DMultiGraphicsGameState::createScene01(void)
	{
		Ogre::SceneManager * pSceneManager = this->mpGraphicsSystem->getSceneManager();

		mpCameraController = new CameraController(mpGraphicsSystem, false);

		mpGraphicsSystem->getCamera()->setPosition(Ogre::Vector3(0, 30, 100));
		mpGraphicsSystem->getCamera()->lookAt(-5.0f, 0.0f, 0.0f);

		// KYLE :: setup FORWARD3D here
		const Presets &preset = c_presets[0];
		pSceneManager->setForward3D(true, preset.width, preset.height,
			preset.numSlices, preset.lightsPerCell,
			preset.minDistance, preset.maxDistance);

		// Smooth booms?
		pSceneManager->getForwardPlus()->setFadeAttenuationRange(true);

		//pSceneManager->setForwardClustered(true, 16, 8, 24, 96, 5, 500);

		// ===========================================================================
		// DOES THIS CONTROL WHAT KIND OF SHADOWS ARE BUILT INTO INITTED THINGS?
		//This sample is too taxing on pixel shaders. Use the fastest PCF filter. 		
		Ogre::Hlms *hlms = mpGraphicsSystem->getRoot()->getHlmsManager()->getHlms(Ogre::HLMS_PBS);
		assert(dynamic_cast<Ogre::HlmsPbs*>(hlms));
		Ogre::HlmsPbs *pbs = static_cast<Ogre::HlmsPbs*>(hlms);
		//pbs->setShadowSettings(Ogre::HlmsPbs::PCF_2x2);
		//pbs->setShadowSettings(Ogre::HlmsPbs::PCF_3x3);
		pbs->setShadowSettings(Ogre::HlmsPbs::PCF_4x4);
		//pbs->setShadowSettings(Ogre::HlmsPbs::ExponentialShadowMaps);
		//pbs->setEsmK(120000);

		//Change the roughness of the default datablock to something prettier.
		Ogre::HlmsPbsDatablock * pbsDatablock = static_cast<Ogre::HlmsPbsDatablock*>(pbs->getDefaultDatablock());
		pbsDatablock->setRoughness(0.1f);
		//pbsDatablock->mShadowConstantBias = 9000000.00000000000000000000001; // LOOKS LIKE ORIG == 0.01
		// KYLE :: TEST :: 
		hlms->getHlmsManager()->setShadowMappingUseBackFaces(true);
		//
		//===========================================================================

		// setFog() doesn't work out of the box, look at links
		// https://forums.ogre3d.org/viewtopic.php?f=25&t=83081#p518819
		// https://forums.ogre3d.org/viewtopic.php?f=25&t=82878#p515450
		//Ogre::ColourValue fogColor(0.22f,1.0f,0.22f,1.0f);
		//pSceneManager->setFog(Ogre::FOG_EXP2, fogColor, 1.001f, 0.0f, 0.0000001f);
		//pSceneManager->setFog(Ogre::FOG_LINEAR, Ogre::ColourValue(1.0f, 1.0f, 0.8f), 0, 15, 100);

/*
		{
			Ogre::NameValuePairList params;
			params["name"] = "TXT_TEST";
			params["caption"] = "THIS IS A TEST!";
			params["fontName"] = "DebugFont";
			params["isBillboard"] = "true";
			mpMovableText = static_cast<Ogre::MovableText*>(pSceneManager->createMovableObject(Ogre::MovableTextFactory::FACTORY_TYPE_NAME,
				&pSceneManager->_getEntityMemoryManager(Ogre::SCENE_DYNAMIC), &params));

			mpMovableText->setTextAlignment(Ogre::MovableText::H_CENTER, Ogre::MovableText::V_ABOVE); // Center horizontally and display above the node
			// / msg->setAdditionalHeight( 2.0f ); //msg->setAdditionalHeight( ei.getRadius() ) // apparently not needed from 1.7 /

			mpTextNode = mpGraphicsSystem->getSceneNodeWorld()->createChildSceneNode(Ogre::SCENE_DYNAMIC);
			mpTextNode->attachObject(mpMovableText);
			mpTextNode->setPosition(Ogre::Vector3(0.0f, 15.0f, 0.0f));

			mpMovableText->setRenderQueueGroup(2);
			mpMovableText->setVisibilityFlags(1);
		}
*/
/*
		for (int i = 0; i < 1024; i++)
		{
			Ogre::NameValuePairList params;
			Ogre::String name = "TXT_" + Ogre::StringConverter::toString(i);
			params["name"] = name;
			Ogre::String caption = "Here is text " + Ogre::StringConverter::toString(i);
			params["caption"] = caption;
			params["fontName"] = "DebugFont";
			params["isBillboard"] = "false";
			params["textSize"] = 1.0f;
			mpMovableTexts[i] = static_cast<Ogre::MovableText*>(pSceneManager->createMovableObject(Ogre::MovableTextFactory::FACTORY_TYPE_NAME,
				&pSceneManager->_getEntityMemoryManager(Ogre::SCENE_DYNAMIC), &params));

			mpMovableTexts[i]->setTextAlignment(Ogre::MovableText::H_CENTER, Ogre::MovableText::V_ABOVE); // Center horizontally and display above the node
			// / msg->setAdditionalHeight( 2.0f ); //msg->setAdditionalHeight( ei.getRadius() ) // apparently not needed from 1.7 /

			mpTextNodes[i] = mpGraphicsSystem->getSceneNodeWorld()->createChildSceneNode(Ogre::SCENE_DYNAMIC);
			mpTextNodes[i]->attachObject(mpMovableTexts[i]);
			mpTextNodes[i]->setPosition(Ogre::Vector3(i + 0.0f, i + 20.0f, 0.0f));

			mpTextNodes[i]->setScale(Ogre::Vector3(1.0f,
				(((Ogre::Real)((i % 5) + 1)) * 0.1f) + 0.5f,
				1.0f));

			//Ogre::Quaternion nodeRot = mpTextNodes[i]->getOrientation();
			//nodeRot.FromAngleAxis(Ogre::Radian(0.125f * i), Ogre::Vector3::UNIT_Y);
			//mpTextNodes[i]->setOrientation(nodeRot);
			mpMovableTexts[i]->setRenderQueueGroup(2);
			mpMovableTexts[i]->setVisibilityFlags(1);
		}
*/

		GameState::createScene01();
	}

	//-----------------------------------------------------------------------------------
	void F3DMultiGraphicsGameState::generateDebugText(float timeSinceLast, Ogre::String &outText)
	{
		GameState::generateDebugText(timeSinceLast, outText);
		outText += "\nPress B to fake a GPU bottleneck (frame skip). ";
		outText += gFakeFrameskip ? "[On]" : "[Off]";
		outText += "\nPress N to fake a CPU Logic bottleneck. ";
		outText += gFakeSlowmo ? "[On]" : "[Off]";
		outText += "\nPress M to enable interpolation. ";
		outText += mEnableInterpolation ? "[On]" : "[Off]";

		//Show the current weight.
		//The text doesn't get updated every frame while displaying
		//help, so don't show the weight as it is inaccurate.
		if (mDisplayHelpMode != 0)
		{
			float weight = mpGraphicsSystem->getAccumTimeSinceLastLogicFrame() / cFrametime;
			weight = std::min(1.0f, weight);

			if (!mEnableInterpolation)
				weight = 0;

			outText += "\nBlend weight: ";
			outText += Ogre::StringConverter::toString(weight);
		}
	}
	//-----------------------------------------------------------------------------------
	void F3DMultiGraphicsGameState::update(float timeSinceLast)
	{
		float weight = mpGraphicsSystem->getAccumTimeSinceLastLogicFrame() / cFrametime;
		weight = std::min(1.0f, weight);

		if (!mEnableInterpolation)
			weight = 0;

		mpGraphicsSystem->updateGameEntities(mpGraphicsSystem->getGameEntities(Ogre::SCENE_DYNAMIC),
			weight);

		GameState::update(timeSinceLast);
	}
	//-----------------------------------------------------------------------------------
	void F3DMultiGraphicsGameState::keyReleased(const SDL_KeyboardEvent &arg)
	{
		if ((arg.keysym.mod & ~(KMOD_NUM | KMOD_CAPS)) != 0)
		{
			GameState::keyReleased(arg);
			return;
		}

		if (arg.keysym.sym == SDLK_b)
		{
			gFakeFrameskip = !gFakeFrameskip;
		}
		else if (arg.keysym.sym == SDLK_n)
		{
			gFakeSlowmo = !gFakeSlowmo;
		}
		else if (arg.keysym.sym == SDLK_m)
		{
			mEnableInterpolation = !mEnableInterpolation;
		}
		else if (arg.keysym.sym == SDLK_ESCAPE)
		{
			mpGraphicsSystem->setQuit();
		}
		else
		{
			GameState::keyReleased(arg);
		}
	}


};