#ifndef _GRAPHICSSYSTEM_H_
#define _GRAPHICSSYSTEM_H_

#include "basesystem.h"
#include "gameentitymanager.h"

#include "osystem/staticpluginloader.h" // install() function

#include "OgrePrerequisites.h"
#include "OgreColourValue.h"
#include "Overlay/OgreOverlayPrerequisites.h" //#include "OgreOverlayPrerequisites.h"

#include "Threading/OgreUniformScalableTask.h"
#include "sdlemulationlayer.h"
#include "Overlay/OgreOverlaySystem.h" //#include "OgreOverlaySystem.h"

// MOVABLETEXT :: 
#include "textblip/MovableText.h"

#if OGRE_USE_SDL2
	#include <SDL.h>
#endif

namespace OGraphics
{

class SdlInputHandler;

class GraphicsSystem : public BaseSystem, public Ogre::UniformScalableTask
{
protected:
	BaseSystem * mpLogicSystem;

#if OGRE_USE_SDL2
	SDL_Window *mpSdlWindow;
	SdlInputHandler * mpInputHandler;
#endif

	Ogre::Root *mpRoot;
	Ogre::RenderWindow *mpRenderWindow;
	Ogre::SceneManager * mpSceneManager;
	Ogre::Camera * mpCamera;
	Ogre::CompositorWorkspace *mpWorkspace;
//	Ogre::String mPluginsPath;
	Ogre::String mPluginsFolder;
	Ogre::String mWriteAccessFolder;
	Ogre::String mResourcePath;

	// MOVABLETEXT :: 
	Ogre::MovableTextFactory * mpMovableTextFactory;

	Ogre::v1::OverlaySystem *mOverlaySystem;
	
	StaticPluginLoader mStaticPluginLoader;

	/// Tracks the amount of elapsed time since we last
	/// heard from the LogicSystem finishing a frame
	float               mAccumTimeSinceLastLogicFrame;
	Ogre::uint32        mCurrentTransformIdx;
	GameEntityVec       mGameEntities[Ogre::NUM_SCENE_MEMORY_MANAGER_TYPES];
	GameEntityVec const *mThreadGameEntityToUpdate;
	float               mThreadWeight;

	bool                mQuit;
	bool                mAlwaysAskForConfig;

	Ogre::ColourValue   mBackgroundColour;

#if OGRE_USE_SDL2
	void handleWindowEvent(const SDL_Event& evt);
#endif

        bool isWriteAccessFolder( const Ogre::String &folderPath, const Ogre::String &fileToSave );
	/// @see MessageQueueSystem::processIncomingMessage
	virtual void processIncomingMessage(Mq::MessageId messageId, const void *data);

	static void addResourceLocation(const Ogre::String &archName, const Ogre::String &typeName,
		const Ogre::String &secName);
	virtual void setupResources(void);
	virtual void registerHlms(void);
	/// Optional override method where you can perform resource group loading
	/// Must at least do ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	virtual void loadResources(void);
	virtual void chooseSceneManager(void);
	virtual void createCamera(void);
	/// Virtual so that advanced samples such as Sample_Compositor can override this
	/// method to change the default behavior if setupCompositor() is overridden, be
	/// aware @mBackgroundColour will be ignored
	virtual Ogre::CompositorWorkspace* setupCompositor(void);

	/// Optional override method where you can create resource listeners (e.g. for loading screens)
	virtual void createResourceListener(void) {}

	void gameEntityAdded(const GameEntityManager::CreatedGameEntity * pCGE);
	//void gameEntityAdded(const GameEntity * pGameEntity);
	void gameEntityRemoved(GameEntity *toRemove);

	// KYLE :: 
	Ogre::SceneNode * mpSceneNodeWorld;
	Ogre::SceneNode * mpSceneNodeUI;
	Ogre::Camera * mpCameraUI;
	void buildSceneNodeUI(void);
	void buildCameraUI(void);
	void buildBaseNodes(void);

public:
	GraphicsSystem(IGameState *gameState,
		Ogre::ColourValue backgroundColour = Ogre::ColourValue(0.2f, 0.4f, 0.6f));
	virtual ~GraphicsSystem();

	void _notifyLogicSystem(BaseSystem *logicSystem)      { mpLogicSystem = logicSystem; }

	void initialize(const Ogre::String &windowTitle, BaseSystem * logicSystem);
	void deinitialize(void);

	void initMicrocodeCache(void);
	void deinitMicrocodeCache(void);

	void update(float timeSinceLast);

	/** Updates the SceneNodes of all the game entities in the container,
	interpolating them according to weight, reading the transforms from
	mCurrentTransformIdx and mCurrentTransformIdx-1.
	@param gameEntities
	The container with entities to update.
	@param weight
	The interpolation weight, ideally in range [0; 1]
	*/
	void updateGameEntities(const GameEntityVec &gameEntities, float weight);

	/// Overload Ogre::UniformScalableTask. @see updateGameEntities
	virtual void execute(size_t threadId, size_t numThreads);

	/// Returns the GameEntities that are ready to be rendered. May include entities
	/// that are scheduled to be removed (i.e. they are no longer updated by logic)
	const GameEntityVec& getGameEntities(Ogre::SceneMemoryMgrTypes type) const
	{
		return mGameEntities[type];
	}

#if OGRE_USE_SDL2
	SdlInputHandler* getInputHandler(void)                  { return mpInputHandler; }
#endif

	void setQuit(void)                                      { mQuit = true; }
	bool getQuit(void) const                                { return mQuit; }

	float getAccumTimeSinceLastLogicFrame(void) const       { return mAccumTimeSinceLastLogicFrame; }

	Ogre::Root* getRoot(void) const                         { return mpRoot; }
	Ogre::RenderWindow* getRenderWindow(void) const         { return mpRenderWindow; }
	Ogre::SceneManager* getSceneManager(void) const         { return mpSceneManager; }
	Ogre::SceneNode * getSceneNodeWorld(void) /*const*/			{ return mpSceneNodeWorld; }
	Ogre::SceneNode* getSceneNodeUI(void) /*const*/         { return mpSceneNodeUI; }
	Ogre::Camera* getCamera(void) const                     { return mpCamera; }
	Ogre::Camera* getCameraUI(void) const					{ return mpCameraUI; }
	Ogre::CompositorWorkspace* getCompositorWorkspace(void) const { return mpWorkspace; }
	Ogre::v1::OverlaySystem* getOverlaySystem(void) const   { return mOverlaySystem; }

	const Ogre::String& getPluginsFolder(void) const        { return mPluginsFolder; }
	const Ogre::String& getWriteAccessFolder(void) const    { return mWriteAccessFolder; }
	const Ogre::String& getResourcePath(void) const         { return mResourcePath; }

	virtual void stopCompositor(void);
	virtual void restartCompositor(void);

};


};


#endif