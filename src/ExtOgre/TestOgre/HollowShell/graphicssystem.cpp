#include "graphicssystem.h"
#include "gamestate.h"
#if OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS
#include "SdlInputHandler.h"
#endif
#include "gameents/gameentity.h"

#include "OgreRoot.h"
#include "OgreException.h"
#include "OgreConfigFile.h"

#include "OgreRenderWindow.h"
#include "OgreCamera.h"
#include "OgreItem.h"

#include "Hlms/Unlit/OgreHlmsUnlit.h"
#include "Hlms/Pbs/OgreHlmsPbs.h"
#include "OgreHlmsManager.h"
#include "OgreArchiveManager.h"

#include "Compositor/OgreCompositorManager2.h"

#include "Overlay/OgreOverlaySystem.h"
#include "Overlay/OgreOverlayManager.h"

#include "OgreWindowEventUtilities.h"

#include "OgreLogManager.h"

#include "OgreFileSystemLayer.h"

// KYLE :: 
// QUESTION2 ::
// http://wiki.ogre3d.org/Ogre+2.1+FAQ#Starting_my_app_takes_forever_particularly_Direct3D11_
#include "OgreGpuProgramManager.h"

#if OGRE_USE_SDL2
#include <SDL_syswm.h>
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
#include "OSX/macUtils.h"
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
#include "System/iOS/iOSUtils.h"
#else
#include "System/OSX/OSXUtils.h"
#endif
#endif

// KYLE :: 
#include <GL/gl3w.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "RenderSystems/GL3Plus/OgreGL3PlusPlugin.h"

#define USE_RQ_FAST 0

namespace OGraphics
{
	GraphicsSystem::GraphicsSystem(IGameState *gameState,
		Ogre::ColourValue backgroundColour) :
		BaseSystem(gameState),
		mpLogicSystem(0),
#if OGRE_USE_SDL2
		mpSdlWindow(0),
		mpInputHandler(0),
#endif
		mpRoot(0),
		mpRenderWindow(0),
		mpSceneManager(0),
		mpCamera(0),
		mpSceneNodeWorld(0),
		mpSceneNodeUI(0),
		mpCameraUI(0),
		mpWorkspace(0),
        mPluginsFolder( "./" ),
		mOverlaySystem(0),
		mAccumTimeSinceLastLogicFrame(0),
		mCurrentTransformIdx(0),
		mThreadGameEntityToUpdate(0),
		mThreadWeight(0),
		mQuit(false),
		mAlwaysAskForConfig(true),
		mBackgroundColour(backgroundColour)
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
        // Note:  macBundlePath works for iOS too. It's misnamed.
        mResourcePath = Ogre::macBundlePath() + "/Contents/Resources/";
#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
        mResourcePath = Ogre::macBundlePath() + "/";
#endif
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
        mPluginsFolder = mResourcePath;
#endif
        if( isWriteAccessFolder( mPluginsFolder, "Ogre.log" ) )
            mWriteAccessFolder = mPluginsFolder;
        else
        {
            Ogre::FileSystemLayer filesystemLayer( OGRE_VERSION_NAME );
            mWriteAccessFolder = filesystemLayer.getWritablePath( "" );
        }
	}
	//-----------------------------------------------------------------------------------
	GraphicsSystem::~GraphicsSystem()
	{
		if (mpRoot)
		{
			Ogre::LogManager::getSingleton().logMessage(
				"WARNING: GraphicsSystem::deinitialize() not called!!!", Ogre::LML_CRITICAL);
		}
	}
	//-----------------------------------------------------------------------------------
    bool GraphicsSystem::isWriteAccessFolder( const Ogre::String &folderPath,
                                              const Ogre::String &fileToSave )
    {
        if( !Ogre::FileSystemLayer::createDirectory( folderPath ) )
            return false;

        std::ofstream of( (folderPath + fileToSave).c_str(),
                          std::ios::out | std::ios::binary | std::ios::app );
        if( !of )
            return false;

        return true;
    }
	void GraphicsSystem::initialize(const Ogre::String &windowTitle, BaseSystem * pLogicSystem)
	{
#if OGRE_USE_SDL2
		//if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
		if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK |
			SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS) != 0)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot initialize SDL2!",
				"GraphicsSystem::initialize");
		}
#endif

        Ogre::String pluginsPath;
        // only use plugins.cfg if not static
    #ifndef OGRE_STATIC_LIB
    #if OGRE_DEBUG_MODE && !((OGRE_PLATFORM == OGRE_PLATFORM_APPLE) || (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS))
        pluginsPath = mPluginsFolder + "plugins_d.cfg";
    #else
        pluginsPath = mPluginsFolder + "plugins.cfg";
    #endif
    #endif

        mpRoot = OGRE_NEW Ogre::Root( pluginsPath,
                                     mWriteAccessFolder + "ogre.cfg",
                                     mWriteAccessFolder + "Ogre.log" );

		mStaticPluginLoader.install(mpRoot);

// KYLE :: STATIC ONLY
//Ogre::GL3PlusPlugin * GLPlugin = new Ogre::GL3PlusPlugin();
//GLPlugin->install();
//#define USE_OGRE_GRAPHICS_BOX 1
//#if USE_OGRE_GRAPHICS_BOX 1
		if (mAlwaysAskForConfig || !mpRoot->restoreConfig())
		{
			if (!mpRoot->showConfigDialog())
			{
				mQuit = true;
				return;
			}
		}
//#else
//		mpRoot->restoreConfig();
//#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
		{
			Ogre::RenderSystem *renderSystem =
				mRoot->getRenderSystemByName("Metal Rendering Subsystem");
			mRoot->setRenderSystem(renderSystem);
		}
#endif

		mpRoot->getRenderSystem()->setConfigOption("sRGB Gamma Conversion", "Yes");
		mpRoot->initialise(false);

		Ogre::ConfigOptionMap& cfgOpts = mpRoot->getRenderSystem()->getConfigOptions();

		int width = 1280;
		int height = 720;

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
		{
			Ogre::Vector2 screenRes = iOSUtils::getScreenResolutionInPoints();
			width = static_cast<int>(screenRes.x);
			height = static_cast<int>(screenRes.y);
		}
#endif

		Ogre::ConfigOptionMap::iterator opt = cfgOpts.find("Video Mode");
		if (opt != cfgOpts.end())
		{
			//Ignore leading space
			const Ogre::String::size_type start = opt->second.currentValue.find_first_of("012356789");
			//Get the width and height
			Ogre::String::size_type widthEnd = opt->second.currentValue.find(' ', start);
			// we know that the height starts 3 characters after the width and goes until the next space
			Ogre::String::size_type heightEnd = opt->second.currentValue.find(' ', widthEnd + 3);
			// Now we can parse out the values
			width = Ogre::StringConverter::parseInt(opt->second.currentValue.substr(0, widthEnd));
			height = Ogre::StringConverter::parseInt(opt->second.currentValue.substr(
				widthEnd + 3, heightEnd));
		}

		Ogre::NameValuePairList params;
		bool fullscreen = Ogre::StringConverter::parseBool(cfgOpts["Full Screen"].currentValue);
#if OGRE_USE_SDL2
		int screen = 0;
		int posX = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);
		int posY = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);

		if (fullscreen)
		{
			posX = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
			posY = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
		}

		mpSdlWindow = SDL_CreateWindow(
			windowTitle.c_str(),    // window title
			posX,               // initial x position
			posY,               // initial y position
			width,              // width, in pixels
			height,             // height, in pixels
			SDL_WINDOW_SHOWN
			| (fullscreen ? SDL_WINDOW_FULLSCREEN : 0) | SDL_WINDOW_RESIZABLE);

		//Get the native whnd
		SDL_SysWMinfo wmInfo;
		SDL_VERSION(&wmInfo.version);

		if (SDL_GetWindowWMInfo(mpSdlWindow, &wmInfo) == SDL_FALSE)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
				"Couldn't get WM Info! (SDL2)",
				"GraphicsSystem::initialize");
		}

		Ogre::String winHandle;
		switch (wmInfo.subsystem)
		{
#ifdef WIN32
		case SDL_SYSWM_WINDOWS:
			// Windows code
			winHandle = Ogre::StringConverter::toString((uintptr_t)wmInfo.info.win.window);
			break;
#elif __MACOSX__
		case SDL_SYSWM_COCOA:
			//required to make OGRE play nice with our window
			params.insert(std::make_pair("macAPI", "cocoa"));
			params.insert(std::make_pair("macAPICocoaUseNSView", "true"));

			winHandle = Ogre::StringConverter::toString(WindowContentViewHandle(wmInfo));
			break;
#else
		case SDL_SYSWM_X11:
			winHandle = Ogre::StringConverter::toString((uintptr_t)wmInfo.info.x11.window);
			break;
#endif
		default:
			OGRE_EXCEPT(Ogre::Exception::ERR_NOT_IMPLEMENTED,
				"Unexpected WM! (SDL2)",
				"GraphicsSystem::initialize");
			break;
		}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		params.insert(std::make_pair("externalWindowHandle", winHandle));
#else
		params.insert(std::make_pair("parentWindowHandle", winHandle));
#endif
#endif

		params.insert(std::make_pair("title", windowTitle));
		params.insert(std::make_pair("gamma", "true"));
		params.insert(std::make_pair("FSAA", cfgOpts["FSAA"].currentValue));
		params.insert(std::make_pair("vsync", cfgOpts["VSync"].currentValue));

		mpRenderWindow = Ogre::Root::getSingleton().createRenderWindow(windowTitle, width, height,
			fullscreen, &params);

		mOverlaySystem = OGRE_NEW Ogre::v1::OverlaySystem();

		setupResources();
		loadResources();
		chooseSceneManager();
		createCamera();

		// KYLE :: 
		buildBaseNodes();
//		buildSceneNodeUI();
//		buildCameraUI();

		mpWorkspace = setupCompositor();

		_notifyLogicSystem(pLogicSystem);

#if OGRE_USE_SDL2
		mpInputHandler = new SdlInputHandler(mpSdlWindow, mCurrentGameState,
			mCurrentGameState, mCurrentGameState);
		mpInputHandler->setMouseRelative(true);
		mpInputHandler->setMouseVisible(false);

		// Setup input piping
		mpInputHandler->setGraphicsSystem(this);
		mpInputHandler->setLogicSystem(pLogicSystem);
#endif

// TEXT :: MOVABLETEXT :: 
		mpMovableTextFactory = OGRE_NEW Ogre::MovableTextFactory();
		mpRoot->addMovableObjectFactory(mpMovableTextFactory);

		BaseSystem::initialize();

#if OGRE_PROFILING
		Ogre::Profiler::getSingleton().setEnabled(true);
		Ogre::Profiler::getSingleton().endProfile("");
#endif

		initMicrocodeCache();
	}

	//-----------------------------------------------------------------------------------
	void GraphicsSystem::deinitialize(void)
	{
		deinitMicrocodeCache();
		BaseSystem::deinitialize();

		if (mpSceneManager)
			mpSceneManager->removeRenderQueueListener(mOverlaySystem);

		OGRE_DELETE mOverlaySystem;
		mOverlaySystem = 0;

#if OGRE_USE_SDL2
		delete mpInputHandler;
		mpInputHandler = 0;
#endif

		OGRE_DELETE mpRoot;
		mpRoot = 0;

#if OGRE_USE_SDL2
		if (mpSdlWindow)
		{
			// Restore desktop resolution on exit
			SDL_SetWindowFullscreen(mpSdlWindow, 0);
			SDL_DestroyWindow(mpSdlWindow);
			mpSdlWindow = 0;
		}

		SDL_Quit();
#endif
	}
	//-----------------------------------------------------------------------------------
	void GraphicsSystem::initMicrocodeCache()
	{
		Ogre::GpuProgramManager::getSingleton().setSaveMicrocodesToCache(true); //Make sure it's enabled.
		Ogre::DataStreamPtr shaderCacheFile = mpRoot->openFileStream("D:/MyCache.cache");
		Ogre::GpuProgramManager::getSingleton().loadMicrocodeCache(shaderCacheFile);
	}
	void GraphicsSystem::deinitMicrocodeCache()
	{
		if (Ogre::GpuProgramManager::getSingleton().isCacheDirty())
		{
			Ogre::DataStreamPtr shaderCacheFile = mpRoot->createFileStream("D:/MyCache.cache", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
			Ogre::GpuProgramManager::getSingleton().saveMicrocodeCache(shaderCacheFile);
		}
	}
	void GraphicsSystem::update(float timeSinceLast)
	{
		Ogre::WindowEventUtilities::messagePump();

#if OGRE_USE_SDL2
		SDL_Event evt;
		while (SDL_PollEvent(&evt))
		{
			switch (evt.type)
			{
			case SDL_WINDOWEVENT:
				handleWindowEvent(evt);
				break;
			case SDL_QUIT:
				mQuit = true;
				break;
			default:
				break;
			}

			mpInputHandler->_handleSdlEvents(evt);
		}
#endif

		BaseSystem::update(timeSinceLast);

		if (mpRenderWindow->isVisible())
			mQuit |= !mpRoot->renderOneFrame();

		mAccumTimeSinceLastLogicFrame += timeSinceLast;

		//SDL_SetWindowPosition( mSdlWindow, 0, 0 );
		/*SDL_Rect rect;
		SDL_GetDisplayBounds( 0, &rect );
		SDL_GetDisplayBounds( 0, &rect );*/
	}
	//-----------------------------------------------------------------------------------
#if OGRE_USE_SDL2
	void GraphicsSystem::handleWindowEvent(const SDL_Event& evt)
	{
		switch (evt.window.event)
		{
			/*case SDL_WINDOWEVENT_MAXIMIZED:
			SDL_SetWindowBordered( mSdlWindow, SDL_FALSE );
			break;
			case SDL_WINDOWEVENT_MINIMIZED:
			case SDL_WINDOWEVENT_RESTORED:
			SDL_SetWindowBordered( mSdlWindow, SDL_TRUE );
			break;*/
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			int w, h;
			SDL_GetWindowSize(mpSdlWindow, &w, &h);
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
			mRenderWindow->resize(w, h);
#else
			mpRenderWindow->windowMovedOrResized();
#endif
			break;
		case SDL_WINDOWEVENT_RESIZED:
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
			mRenderWindow->resize(evt.window.data1, evt.window.data2);
#else
			mpRenderWindow->windowMovedOrResized();
#endif
			break;
		case SDL_WINDOWEVENT_CLOSE:
			break;
		case SDL_WINDOWEVENT_SHOWN:
			mpRenderWindow->setVisible(true);
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			mpRenderWindow->setVisible(false);
			break;
		}
	}
#endif
	//-----------------------------------------------------------------------------------
	void GraphicsSystem::processIncomingMessage(Mq::MessageId messageId, const void *data)
	{
		// THIS IS TEMP; REMOVE THIS
		const GameEntityManager::CreatedGameEntity * pCGE = 0;

		switch (messageId)
		{
		case Mq::LOGICFRAME_FINISHED:
		{
			Ogre::uint32 newIdx = *reinterpret_cast<const Ogre::uint32*>(data);

			if (newIdx != std::numeric_limits<Ogre::uint32>::max())
			{
				mAccumTimeSinceLastLogicFrame = 0;
				//Tell the LogicSystem we're no longer using the index previous to the current one.
				this->queueSendMessage(mpLogicSystem, Mq::LOGICFRAME_FINISHED,
					(mCurrentTransformIdx + NUM_GAME_ENTITY_BUFFERS - 1) %
					NUM_GAME_ENTITY_BUFFERS);

				assert((mCurrentTransformIdx + 1) % NUM_GAME_ENTITY_BUFFERS == newIdx &&
					"Graphics is receiving indices out of order!!!");

				//Get the new index the LogicSystem is telling us to use.
				mCurrentTransformIdx = newIdx;
			}
		}
		break;
		case Mq::GAME_ENTITY_ADDED:
			pCGE = reinterpret_cast<const GameEntityManager::CreatedGameEntity*>(data);
			gameEntityAdded(pCGE);
			break;
		case Mq::GAME_ENTITY_REMOVED:
			gameEntityRemoved(*reinterpret_cast<GameEntity * const *>(data));
			break;
		case Mq::GAME_ENTITY_SCHEDULED_FOR_REMOVAL_SLOT:
			//Acknowledge/notify back that we're done with this slot.
			this->queueSendMessage(mpLogicSystem, Mq::GAME_ENTITY_SCHEDULED_FOR_REMOVAL_SLOT,
				*reinterpret_cast<const Ogre::uint32*>(data));
			break;
		default:
			break;
		}
	}
	//-----------------------------------------------------------------------------------
	void GraphicsSystem::addResourceLocation(const Ogre::String &archName, const Ogre::String &typeName,
		const Ogre::String &secName)
	{
#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE) || (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS)
		// OS X does not set the working directory relative to the app,
		// In order to make things portable on OS X we need to provide
		// the loading with it's own bundle path location
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
			Ogre::String(Ogre::macBundlePath() + "/" + archName), typeName, secName);
#else
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
			archName, typeName, secName);
#endif
	}
	//-----------------------------------------------------------------------------------
	void GraphicsSystem::setupResources(void)
	{
		// Load resource paths from config file
		Ogre::ConfigFile cf;
		cf.load(mResourcePath + "resources2.cfg");

		// Go through all sections & settings in the file
		Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

		Ogre::String secName, typeName, archName;
		while (seci.hasMoreElements())
		{
			secName = seci.peekNextKey();
			Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();

			if (secName != "Hlms")
			{
				Ogre::ConfigFile::SettingsMultiMap::iterator i;
				for (i = settings->begin(); i != settings->end(); ++i)
				{
					typeName = i->first;
					archName = i->second;
					addResourceLocation(archName, typeName, secName);
				}
			}
		}
	}
	//-----------------------------------------------------------------------------------
	void GraphicsSystem::registerHlms(void)
	{
		Ogre::ConfigFile cf;
		cf.load(mResourcePath + "resources2.cfg");

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
		Ogre::String rootHlmsFolder = Ogre::macBundlePath() + '/' +
			cf.getSetting("DoNotUseAsResource", "Hlms", "");
#else
		Ogre::String rootHlmsFolder = mResourcePath + cf.getSetting("DoNotUseAsResource", "Hlms", "");
#endif

		if (rootHlmsFolder.empty())
			rootHlmsFolder = "./";
		else if (*(rootHlmsFolder.end() - 1) != '/')
			rootHlmsFolder += "/";

		//At this point rootHlmsFolder should be a valid path to the Hlms data folder

		Ogre::HlmsUnlit *hlmsUnlit = 0;
		Ogre::HlmsPbs *hlmsPbs = 0;

		//For retrieval of the paths to the different folders needed
		Ogre::String mainFolderPath;
		Ogre::StringVector libraryFoldersPaths;
		Ogre::StringVector::const_iterator libraryFolderPathIt;
		Ogre::StringVector::const_iterator libraryFolderPathEn;

		Ogre::ArchiveManager &archiveManager = Ogre::ArchiveManager::getSingleton();

		{
			//Create & Register HlmsUnlit
			//Get the path to all the subdirectories used by HlmsUnlit
			Ogre::HlmsUnlit::getDefaultPaths(mainFolderPath, libraryFoldersPaths);
			Ogre::Archive *archiveUnlit = archiveManager.load(rootHlmsFolder + mainFolderPath,
				"FileSystem", true);
			Ogre::ArchiveVec archiveUnlitLibraryFolders;
			libraryFolderPathIt = libraryFoldersPaths.begin();
			libraryFolderPathEn = libraryFoldersPaths.end();
			while (libraryFolderPathIt != libraryFolderPathEn)
			{
				Ogre::Archive *archiveLibrary =
					archiveManager.load(rootHlmsFolder + *libraryFolderPathIt, "FileSystem", true);
				archiveUnlitLibraryFolders.push_back(archiveLibrary);
				++libraryFolderPathIt;
			}

			//Create and register the unlit Hlms
			hlmsUnlit = OGRE_NEW Ogre::HlmsUnlit(archiveUnlit, &archiveUnlitLibraryFolders);
			Ogre::Root::getSingleton().getHlmsManager()->registerHlms(hlmsUnlit);
		}

		{
			//Create & Register HlmsPbs
			//Do the same for HlmsPbs:
			Ogre::HlmsPbs::getDefaultPaths(mainFolderPath, libraryFoldersPaths);
			Ogre::Archive *archivePbs = archiveManager.load(rootHlmsFolder + mainFolderPath,
				"FileSystem", true);

			//Get the library archive(s)
			Ogre::ArchiveVec archivePbsLibraryFolders;
			libraryFolderPathIt = libraryFoldersPaths.begin();
			libraryFolderPathEn = libraryFoldersPaths.end();
			while (libraryFolderPathIt != libraryFolderPathEn)
			{
				Ogre::Archive *archiveLibrary =
					archiveManager.load(rootHlmsFolder + *libraryFolderPathIt, "FileSystem", true);
				archivePbsLibraryFolders.push_back(archiveLibrary);
				++libraryFolderPathIt;
			}

			//Create and register
			hlmsPbs = OGRE_NEW Ogre::HlmsPbs(archivePbs, &archivePbsLibraryFolders);
			Ogre::Root::getSingleton().getHlmsManager()->registerHlms(hlmsPbs);
		}

		Ogre::RenderSystem *renderSystem = mpRoot->getRenderSystem();
		if (renderSystem->getName() == "Direct3D11 Rendering Subsystem")
		{
			//Set lower limits 512kb instead of the default 4MB per Hlms in D3D 11.0
			//and below to avoid saturating AMD's discard limit (8MB) or
			//saturate the PCIE bus in some low end machines.
			bool supportsNoOverwriteOnTextureBuffers;
			renderSystem->getCustomAttribute("MapNoOverwriteOnDynamicBufferSRV",
				&supportsNoOverwriteOnTextureBuffers);

			if (!supportsNoOverwriteOnTextureBuffers)
			{
				hlmsPbs->setTextureBufferDefaultSize(512 * 1024);
				hlmsUnlit->setTextureBufferDefaultSize(512 * 1024);
			}
		}
	}
	//-----------------------------------------------------------------------------------
	void GraphicsSystem::loadResources(void)
	{
		registerHlms();

		// Initialise, parse scripts etc
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups(true);
	}

	void GraphicsSystem::buildBaseNodes(void)
	{
		mpSceneNodeWorld = mpSceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)->
			createChildSceneNode(Ogre::SCENE_DYNAMIC);
		mpSceneNodeUI = mpSceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)->
			createChildSceneNode(Ogre::SCENE_DYNAMIC);
	}

	void GraphicsSystem::buildSceneNodeUI(void)
	{
		mpSceneNodeUI;
	}

	void GraphicsSystem::buildCameraUI(void)
	{
		mpCameraUI = mpSceneManager->createCamera("UI Camera");

		mpCameraUI->setProjectionType(Ogre::ProjectionType::PT_ORTHOGRAPHIC);

		mpCameraUI->setOrthoWindowHeight(2.0);

		// Position it at 
		mpCameraUI->setPosition(Ogre::Vector3(0, 0, 1));
		// Look back along -Z
		mpCameraUI->lookAt(Ogre::Vector3(0, 0, 0));
		mpCameraUI->setNearClipDistance(0.01f);
		mpCameraUI->setFarClipDistance(1000.0f);
		mpCameraUI->setAutoAspectRatio(true);
	}

	//-----------------------------------------------------------------------------------
	void GraphicsSystem::chooseSceneManager(void)
	{
		Ogre::InstancingThreadedCullingMethod threadedCullingMethod =
			Ogre::INSTANCING_CULLING_SINGLETHREAD;
#if OGRE_DEBUG_MODE
		//Debugging multithreaded code is a PITA, disable it.
		const size_t numThreads = 1;
#else
		//getNumLogicalCores() may return 0 if couldn't detect
		const size_t numThreads = std::max<size_t>(1, Ogre::PlatformInformation::getNumLogicalCores());
		//See doxygen documentation regarding culling methods.
		//In some cases you may still want to use single thread.
		//if( numThreads > 1 )
		//	threadedCullingMethod = Ogre::INSTANCING_CULLING_THREADED;
#endif
		// Create the SceneManager, in this case a generic one
		mpSceneManager = mpRoot->createSceneManager(Ogre::ST_GENERIC,
			numThreads,
			threadedCullingMethod,
			"ExampleSMInstance");

		mpSceneManager->addRenderQueueListener(mOverlaySystem);
		mpSceneManager->getRenderQueue()->setSortRenderQueue(
			Ogre::v1::OverlayManager::getSingleton().mDefaultRenderQueueId,
			Ogre::RenderQueue::StableSort);

		mpSceneManager->getRenderQueue()->setRenderQueueMode(1, Ogre::RenderQueue::FAST);
		mpSceneManager->getRenderQueue()->setRenderQueueMode(2, Ogre::RenderQueue::V1_FAST);
		//mpSceneManager->getRenderQueue()->setRenderQueueMode(3, Ogre::RenderQueue::FAST);

		//Set sane defaults for proper shadow mapping
		mpSceneManager->setShadowDirectionalLightExtrusionDistance(500.0f);
		mpSceneManager->setShadowFarDistance(250.0f); // 250 is good, 500 is probably farthest
	}
	//-----------------------------------------------------------------------------------
	void GraphicsSystem::createCamera(void)
	{
		mpCamera = mpSceneManager->createCamera("Main Camera");

		// Position it at 500 in Z direction
		mpCamera->setPosition(Ogre::Vector3(0, 5, 15));
		// Look back along -Z
		mpCamera->lookAt(Ogre::Vector3(0, 0, 0));
		mpCamera->setNearClipDistance(0.2f); // KYLE :: NEAR CLIP WAS LOW AS FUCK. 0.001f breaks things
		mpCamera->setFarClipDistance(1000.0f);
		mpCamera->setAutoAspectRatio(true);
	}
	//-----------------------------------------------------------------------------------
	Ogre::CompositorWorkspace* GraphicsSystem::setupCompositor(void)
	{
		// KYLE :: This function is completely overridden
/*
		Ogre::CompositorManager2 *compositorManager = mpRoot->getCompositorManager2();

		const Ogre::String workspaceName("Demo Workspace");
		if (!compositorManager->hasWorkspaceDefinition(workspaceName))
		{
			compositorManager->createBasicWorkspaceDef(workspaceName, mBackgroundColour,
				Ogre::IdString());
		}

		return compositorManager->addWorkspace(mpSceneManager, mpRenderWindow, mpCamera,
			workspaceName, true);
*/
		return 0;
	}
	//-----------------------------------------------------------------------------------
	void GraphicsSystem::stopCompositor(void)
	{
		if (mpWorkspace)
		{
			Ogre::CompositorManager2 *compositorManager = mpRoot->getCompositorManager2();
			compositorManager->removeWorkspace(mpWorkspace);
			mpWorkspace = 0;
		}
	}
	//-----------------------------------------------------------------------------------
	void GraphicsSystem::restartCompositor(void)
	{
		stopCompositor();
		mpWorkspace = setupCompositor();
	}
	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------
	struct GameEntityCmp
	{
		bool operator () (const GameEntity *_l, const Ogre::Matrix4 * RESTRICT_ALIAS _r) const
		{
			const Ogre::Transform &transform = _l->mSceneNode->_getTransform();
			return &transform.mDerivedTransform[transform.mIndex] < _r;
		}

		bool operator () (const Ogre::Matrix4 * RESTRICT_ALIAS _r, const GameEntity *_l) const
		{
			const Ogre::Transform &transform = _l->mSceneNode->_getTransform();
			return _r < &transform.mDerivedTransform[transform.mIndex];
		}

		bool operator () (const GameEntity *_l, const GameEntity *_r) const
		{
			const Ogre::Transform &lTransform = _l->mSceneNode->_getTransform();
			const Ogre::Transform &rTransform = _r->mSceneNode->_getTransform();
			return &lTransform.mDerivedTransform[lTransform.mIndex] < &rTransform.mDerivedTransform[rTransform.mIndex];
		}
	};
	//-----------------------------------------------------------------------------------
	void GraphicsSystem::gameEntityAdded(const GameEntityManager::CreatedGameEntity * pCGE)
	{
		GameEntity * pGameEntity = pCGE->pGameEntity;
		//		cge->gameEntity->onGameEntityAdded(mpSceneManager, cge->initialTransform);
		//pGameEntity->onGameEntityAdded(mpSceneManager);
		pGameEntity->onGameEntityAdded(this);

		//Keep them sorted on how Ogre's internal memory manager assigned them memory,
		//to avoid false cache sharing when we update the nodes concurrently.
		const Ogre::Transform &transform = pGameEntity->mSceneNode->_getTransform();
		GameEntityVec::iterator itGameEntity = std::lower_bound(
			mGameEntities[pGameEntity->mSceneType].begin(),
			mGameEntities[pGameEntity->mSceneType].end(),
			&transform.mDerivedTransform[transform.mIndex],
			GameEntityCmp());
		mGameEntities[pGameEntity->mSceneType].insert(itGameEntity, pGameEntity);
	}
	//-----------------------------------------------------------------------------------
	void GraphicsSystem::gameEntityRemoved(GameEntity *toRemove)
	{
		const Ogre::Transform &transform = toRemove->mSceneNode->_getTransform();
		GameEntityVec::iterator itGameEntity = std::lower_bound(
			mGameEntities[toRemove->mSceneType].begin(),
			mGameEntities[toRemove->mSceneType].end(),
			&transform.mDerivedTransform[transform.mIndex],
			GameEntityCmp());

		assert(itGameEntity != mGameEntities[toRemove->mSceneType].end() && *itGameEntity == toRemove);
		mGameEntities[toRemove->mSceneType].erase(itGameEntity);

		toRemove->mSceneNode->getParentSceneNode()->removeAndDestroyChild(toRemove->mSceneNode);
		toRemove->mSceneNode = 0;

		toRemove->onGameEntityRemoved(mpSceneManager);
	}
	//-----------------------------------------------------------------------------------
	void GraphicsSystem::updateGameEntities(const GameEntityVec &gameEntities, float weight)
	{
		mThreadGameEntityToUpdate = &gameEntities;
		mThreadWeight = weight;

		//Note: You could execute a non-blocking scalable task and do something else, you should
		//wait for the task to finish right before calling renderOneFrame or before trying to
		//execute another UserScalableTask (you would have to be careful, but it could work).
		mpSceneManager->executeUserScalableTask(this, true);
	}
	//-----------------------------------------------------------------------------------
	void GraphicsSystem::execute(size_t threadId, size_t numThreads)
	{
		size_t currIdx = mCurrentTransformIdx;
		size_t prevIdx = (mCurrentTransformIdx + NUM_GAME_ENTITY_BUFFERS - 1) % NUM_GAME_ENTITY_BUFFERS;

		const size_t objsPerThread = (mThreadGameEntityToUpdate->size() + (numThreads - 1)) / numThreads;
		const size_t toAdvance = std::min(threadId * objsPerThread, mThreadGameEntityToUpdate->size());

		GameEntityVec::const_iterator itor = mThreadGameEntityToUpdate->begin() + toAdvance;
		GameEntityVec::const_iterator end = mThreadGameEntityToUpdate->begin() +
			std::min(toAdvance + objsPerThread,
			mThreadGameEntityToUpdate->size());
		while (itor != end)
		{
			// ON A PER ENTITY BASIS, This is updating with interpolation
			GameEntity *gEnt = *itor;
			gEnt->updateGraphics(mCurrentTransformIdx, mThreadWeight);
			++itor;
		}
	}
}
