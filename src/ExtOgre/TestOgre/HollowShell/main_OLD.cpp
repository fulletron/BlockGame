
#define SDL_MAIN_HANDLED

#include "graphicssystem.h"
//#include "terraingamestate.h"
#include "forward3dgamestate.h"

#include "OgreRenderWindow.h"

#include "OgreRoot.h"
#include "Compositor/OgreCompositorManager2.h"
#include "OgreConfigFile.h"

#include "oterra/Hlms/OgreHlmsTerra.h"
#include "OgreHlmsManager.h"
#include "OgreArchiveManager.h"

//Declares WinMain / main
//#include "mainentrypointhelper.h"
//#include "osystem/mainentrypoints.h"

#include "logicsystem.h"
#include "sdlinputhandler.h"
#include "OgreTimer.h"

#include <iostream>

#define KYLE_TUTORIAL_GAME_LOOP 1

#define USE_TERRAIN 0
#define USE_F3D 0
#define USE_F3DMULTI 1
#define USE_ST 0

namespace OGraphics {
	const double FRAMETIME = 1.0 / 240.0;
	const char* getWindowTitle(void){
		return "Tutorial: THIS";
	}
}

#if USE_F3DMULTI 1
namespace OGraphics
{
	class F3DMultiGraphicsSystem : public GraphicsSystem
	{
		virtual Ogre::CompositorWorkspace* setupCompositor()
		{
			//We reuse the ShadowMapDebugging sample's workspace. Pretty handful.
			Ogre::CompositorManager2 *compositorManager = mpRoot->getCompositorManager2();
			return compositorManager->addWorkspace(mpSceneManager, mpRenderWindow, mpCamera,
				"Test2Workspace",
				//				"ShadowMapDebuggingWorkspace", // KYLE :: ORIG 
				true);
		}

	public:
		F3DMultiGraphicsSystem(GameState *gameState) :
			GraphicsSystem(gameState)
		{
		}

		virtual void setupResources(void)
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
	};
};

#endif

#if USE_F3D 1
namespace OGraphics
{
	class Forward3DGraphicsSystem : public GraphicsSystem
	{
		virtual Ogre::CompositorWorkspace* setupCompositor()
		{
			//We reuse the ShadowMapDebugging sample's workspace. Pretty handful.
			Ogre::CompositorManager2 *compositorManager = mpRoot->getCompositorManager2();
			return compositorManager->addWorkspace(mpSceneManager, mpRenderWindow, mpCamera,
				"Test2Workspace",
				//				"ShadowMapDebuggingWorkspace", // KYLE :: ORIG 
				true);
		}

	public:
		Forward3DGraphicsSystem(GameState *gameState) :
			GraphicsSystem(gameState)
		{
		}

		virtual void setupResources(void)
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
	};
};
#endif

#if USE_TERRAIN 1
namespace OGraphics 
{
	class Tutorial_TerrainGraphicsSystem : public GraphicsSystem
	{
	virtual Ogre::CompositorWorkspace* setupCompositor()
	{
	//Delegate compositor creation to the game state. We need terra's shadow texture
	//to be passed to the compositor so Ogre can insert the proper barriers.
	assert(dynamic_cast<Tutorial_TerrainGameState*>(mCurrentGameState));
	return static_cast<Tutorial_TerrainGameState*>(mCurrentGameState)->setupCompositor();
	}

	virtual void setupResources(void)
	{
	GraphicsSystem::setupResources();

	Ogre::ConfigFile cf;
	cf.load(mResourcePath + "resources2.cfg");

	Ogre::String originalDataFolder = cf.getSetting("DoNotUseAsResource", "Hlms", "");

	if (originalDataFolder.empty())
	originalDataFolder = "./";
	else if (*(originalDataFolder.end() - 1) != '/')
	originalDataFolder += "/";

	const char *c_locations[4] =
	{
	"2.0/scripts/materials/Tutorial_Terrain",
	"2.0/scripts/materials/Tutorial_Terrain/GLSL",
	"2.0/scripts/materials/Tutorial_Terrain/HLSL",
	"2.0/scripts/materials/Postprocessing/SceneAssets"
	};

	for (size_t i = 0; i<4; ++i)
	{
	Ogre::String dataFolder = originalDataFolder + c_locations[i];
	addResourceLocation(dataFolder, "FileSystem", "General");
	}
	}

	virtual void registerHlms(void)
	{
	GraphicsSystem::registerHlms();

	Ogre::ConfigFile cf;
	cf.load(mResourcePath + "resources2.cfg");

	Ogre::String dataFolder = cf.getSetting("DoNotUseAsResource", "Hlms", "");

	if (dataFolder.empty())
	dataFolder = "./";
	else if (*(dataFolder.end() - 1) != '/')
	dataFolder += "/";

	Ogre::RenderSystem *renderSystem = mpRoot->getRenderSystem();

	Ogre::String shaderSyntax = "GLSL";
	if (renderSystem->getName() == "Direct3D11 Rendering Subsystem")
	shaderSyntax = "HLSL";

	Ogre::Archive *archiveLibrary = Ogre::ArchiveManager::getSingletonPtr()->load(
	dataFolder + "Hlms/Common/" + shaderSyntax,
	"FileSystem", true);
	Ogre::Archive *archiveLibraryAny = Ogre::ArchiveManager::getSingletonPtr()->load(
	dataFolder + "Hlms/Common/Any",
	"FileSystem", true);
	Ogre::Archive *archivePbsLibraryAny = Ogre::ArchiveManager::getSingletonPtr()->load(
	dataFolder + "Hlms/Pbs/Any",
	"FileSystem", true);
	Ogre::Archive *pbsLibrary = Ogre::ArchiveManager::getSingletonPtr()->load(
	dataFolder + "Hlms/Pbs/" + shaderSyntax,
	"FileSystem", true);

	Ogre::ArchiveVec library;
	library.push_back(archiveLibrary);
	library.push_back(archiveLibraryAny);
	library.push_back(archivePbsLibraryAny);
	library.push_back(pbsLibrary);

	Ogre::Archive *archiveTerra = Ogre::ArchiveManager::getSingletonPtr()->load(
	dataFolder + "Hlms/Terra/" + shaderSyntax,
	"FileSystem", true);
	Ogre::HlmsTerra *hlmsTerra = OGRE_NEW Ogre::HlmsTerra(archiveTerra, &library);
	Ogre::HlmsManager *hlmsManager = mpRoot->getHlmsManager();
	hlmsManager->registerHlms(hlmsTerra);

	//Add Terra's piece files that customize the PBS implementation.
	//These pieces are coded so that they will be activated when
	//we set the HlmsPbsTerraShadows listener and there's an active Terra
	//(see Tutorial_TerrainGameState::createScene01)
	Ogre::Hlms *hlmsPbs = hlmsManager->getHlms(Ogre::HLMS_PBS);
	Ogre::Archive *archivePbs = hlmsPbs->getDataFolder();
	Ogre::ArchiveVec libraryPbs = hlmsPbs->getPiecesLibraryAsArchiveVec();
	libraryPbs.push_back(Ogre::ArchiveManager::getSingletonPtr()->load(
	dataFolder + "Hlms/Terra/" + shaderSyntax + "/PbsTerraShadows",
	"FileSystem", true));
	hlmsPbs->reloadFrom(archivePbs, &libraryPbs);
	}

	public:
	Tutorial_TerrainGraphicsSystem(GameState *gameState) :
	GraphicsSystem(gameState)
	{
	}

	virtual void createScene01()
	{
	GraphicsSystem::createScene01();
	//The first time setupCompositor got called, Terra wasn't ready yet.
	//Create the workspace again (will destroy previous workspace).
	mpWorkspace = setupCompositor();
	}
	};
};
#endif

#if USE_ST 1
int main(int argc, const char *argv[])
{
	//GameState *graphicsGameState = 0;
	//GraphicsSystem *graphicsSystem = 0;
	//GameState *logicGameState = 0;
	OGraphics::LogicSystem *logicSystem = 0;
#if USE_F3D 1
	OGraphics::Forward3DGameState *graphicsGameState = new OGraphics::Forward3DGameState(
		"Forward3D & Clustered are techniques capable of rendering many lights. It is required in order\n"
		"to render non-shadow casting non-directional lights with the PBS implementation.\n"
		"Deferred shading has a lot of problems (transparency, antialiasing, multiple BDRF). Besides,\n"
		"it uses a lot of bandwidth. Forward+/Forward2.5 is great, but requires DX11 HW (needs UAV) and\n"
		"a Z-Prepass. This Z-prepass is often a turn off for many (even though in some cases it may\n"
		"improve performance, i.e. if you’re heavily pixel shader or ROP [Raster OPeration] bound).\n"
		"It’s not superior on all accounts, but it can work on DX10 hardware and doesn’t require a\n"
		"Z-prepass. The result is a nice generic algorithm that can run on a lot of hardware and can\n"
		"handle a lot of lights. Whether it performs better or worse than Deferred or Forward+ depends\n"
		"on the scene.\n"
		"\n\n"
		"Like its alternatives Defered & Forward+, it works best with many small lights, or few big\n"
		"lights.\n"
		"Forward3D & Clustered have many parameters, and this demo shows different presets that often\n"
		"trade quality for speed; but sometimes some presets work better on some scenarios than others.\n"
		"This demo stresses the implementation, showing you both its strengths and limitations\n"
		"   1. Increase the number of lights to show the artifacts.\n"
		"   2. Decrease the lights' radius to alleviate the artifacts.\n"
		"   3. Switch profiles to see the differences. Often profile 0 & 5 work best.\n"
		"   4. Repeat steps 1 through 3 using a High threshold.\n"
		"   5. It may be better to have fewer but bigger lights in outdoor scenes\n"
		"   6. Lights are 'lodded' based on distance to camera as a side effect of how the algorithm works\n"
		"It is quite unrealistic that all lights to have the same parameters. Heterogenous\n"
		"light parameters will give you better results.\n"
		"Also avoid keeping too many lights tight in the same place. If we increase the distance\n"
		"between each light in this sample, the artifacts begin to disappear.\n"
		"Light's size has a direct impact on quality. Theoretically all lights have an unlimited\n"
		"range. However we cut it off after certain threshold for performance reasons. Very low\n"
		"thresholds stress the F3D system, but very high thresholds will cut the light too early.\n"
		"\n"
		"Forward+ and Deferred as alternative implementations are planned in the future.\n"
		"\n"
		"This sample depends on the media files:\n"
		"   * Samples/Media/2.0/scripts/Compositors/ShadowMapDebugging.compositor");

	OGraphics::Forward3DGraphicsSystem *graphicsSystem = new OGraphics::Forward3DGraphicsSystem(graphicsGameState);
#endif
#if USE_TERRIAN 1
	OGraphics::Tutorial_TerrainGameState *graphicsGameState = new OGraphics::Tutorial_TerrainGameState(
		"--- !!! NOTE: THIS SAMPLE IS A WORK IN PROGRESS !!! ---\n"
		"This is an advanced tutorial that shows several things working together:\n"
		"   * Own Hlms implementation to render the terrain\n"
		"   * Vertex buffer-less rendering: The terrain is generated purely using SV_VertexID "
		"tricks and a heightmap texture\n"
		"   * Hlms customizations to PBS to make terrain shadows affect regular objects\n"
		"   * Compute Shaders to generate terrain shadows every frame\n"
		"   * Common terrain functionality such as loading the heightmap, generating normals, LOD.\n"
		"The Terrain system is called 'Terra' and has been isolated under the Terra folder like\n"
		"a component for easier copy-pasting into your own projects.\n\n"
		"Because every project has its own needs regarding terrain rendering, we're not providing\n"
		"Terra as an official Component, but rather as a tutorial; where users can copy paste our\n"
		"implementation and use it as is, or make their own tweaks or enhancements.\n\n"
		"This sample depends on the media files:\n"
		"   * Samples/Media/2.0/scripts/Compositors/Tutorial_Terrain.compositor\n"
		"   * Samples/Media/2.0/materials/Tutorial_Terrain/*.*\n"
		"   * Samples/Media/2.0/materials/Common/GLSL/GaussianBlurBase_cs.glsl\n"
		"   * Samples/Media/2.0/materials/Common/HLSL/GaussianBlurBase_cs.hlsl\n"
		"   * Samples/Media/Hlms/Terra/*.*\n");

	OGraphics::Tutorial_TerrainGraphicsSystem *graphicsSystem =
		new OGraphics::Tutorial_TerrainGraphicsSystem(graphicsGameState);
#endif

	graphicsGameState->_notifyGraphicsSystem(graphicsSystem);

	graphicsSystem->initialize(OGraphics::getWindowTitle());
	if (logicSystem)
		logicSystem->initialize();

	if (graphicsSystem->getQuit())
	{
		if (logicSystem)
			logicSystem->deinitialize();
		graphicsSystem->deinitialize();

		if (graphicsSystem)
			delete graphicsSystem;
		if (graphicsGameState)
			delete graphicsGameState;

		return 0; //User cancelled config
	}

	Ogre::RenderWindow *renderWindow = graphicsSystem->getRenderWindow();

	graphicsSystem->createScene01();
	if (logicSystem)
		logicSystem->createScene01();

	graphicsSystem->createScene02();
	if (logicSystem)
		logicSystem->createScene02();

#if OGRE_USE_SDL2
	//Do this after creating the scene for easier the debugging (the mouse doesn't hide itself)
	OGraphics::SdlInputHandler *inputHandler = graphicsSystem->getInputHandler();
	inputHandler->setGrabMousePointer(true);
	inputHandler->setMouseVisible(false);
#endif

	Ogre::Timer timer;
#if KYLE_TUTORIAL_GAME_LOOP 1
	unsigned long startTime = timer.getMicroseconds();
	double accumulator = OGraphics::FRAMETIME;
	double timeSinceLast = OGraphics::FRAMETIME;

	while (!graphicsSystem->getQuit())
	{
		while (accumulator >= OGraphics::FRAMETIME && logicSystem)
		{
			logicSystem->beginFrameParallel();
			logicSystem->update(static_cast<float>(OGraphics::FRAMETIME));
			logicSystem->finishFrameParallel();

			logicSystem->finishFrame();
			graphicsSystem->finishFrame();

			accumulator -= OGraphics::FRAMETIME;
		}

		graphicsSystem->beginFrameParallel();
		graphicsSystem->update(static_cast<float>(timeSinceLast));
		graphicsSystem->finishFrameParallel();
		if (!logicSystem)
			graphicsSystem->finishFrame();

		if (!renderWindow->isVisible())
		{
			//Don't burn CPU cycles unnecessary when we're minimized.
			Ogre::Threads::Sleep(500);
		}

		unsigned long endTime = timer.getMicroseconds();
		timeSinceLast = (endTime - startTime) / 1000000.0; // Presumably puts it in milliseconds
		timeSinceLast  = std::min(1.0, timeSinceLast); //Prevent from going haywire.
		accumulator += timeSinceLast;
		startTime = endTime;
	}
#else
	double dt = OGraphics::FRAMETIME;
	unsigned long startTime = timer.getMicroseconds();
	unsigned long nowTime = 0;
	while (!graphicsSystem->getQuit())
	{
		graphicsSystem->beginFrameParallel();
		graphicsSystem->update(static_cast<float>(dt));
		graphicsSystem->finishFrameParallel();
		// KYLE :: WHAT THE HELL IS THIS?
		if (!logicSystem)
			graphicsSystem->finishFrame();

		do {
			nowTime = timer.getMicroseconds();
			dt = ((nowTime - startTime) / 1000000.0);
			dt = std::min(1.0, dt);
		} while (dt < OGraphics::FRAMETIME);
		startTime = nowTime;
	}
#endif

	graphicsSystem->destroyScene();
	if (logicSystem)
	{
		logicSystem->destroyScene();
		logicSystem->deinitialize();
	}
	graphicsSystem->deinitialize();

	if (graphicsSystem)
		delete graphicsSystem;
	if (graphicsGameState)
		delete graphicsGameState;

	return 0;
}

#endif