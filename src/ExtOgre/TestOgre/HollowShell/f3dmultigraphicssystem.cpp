#include "f3dmultigraphicssystem.h"

// Needed for addWorkspace() call
#include "OgreRenderWindow.h"

#include "OgreRoot.h"
#include "OgreConfigFile.h"
#include "Compositor/OgreCompositorManager2.h"

namespace OGraphics
{
	Ogre::CompositorWorkspace* F3DMultiGraphicsSystem::setupCompositor()
	{
		//We reuse the ShadowMapDebugging sample's workspace. Pretty handful.
		Ogre::CompositorManager2 *compositorManager = mpRoot->getCompositorManager2();
		return compositorManager->addWorkspace(
			mpSceneManager, 
			mpRenderWindow, 
			mpCamera,
//			"Test2BWorkspace",
			"Test3Workspace", // KYLE :: CUSTOM
//			"ShadowMapDebuggingWorkspace", // KYLE :: ORIG 
			true);
	}

	void F3DMultiGraphicsSystem::setupResources(void)
	{
		GraphicsSystem::setupResources();

		Ogre::ConfigFile cf;
		cf.load(mResourcePath + "resources2.cfg");

		Ogre::String dataFolder = cf.getSetting("DoNotUseAsResource", "Hlms", "");

		if (dataFolder.empty())
			dataFolder = "./";
		else if (*(dataFolder.end() - 1) != '/')
			dataFolder += "/";

		dataFolder += "2.0/scripts/materials/PbsMaterials";

		addResourceLocation(dataFolder, "FileSystem", "General");
	}

	const char* getWindowTitle(void)
	{
		return "Tutorial: THIS";
	}
};