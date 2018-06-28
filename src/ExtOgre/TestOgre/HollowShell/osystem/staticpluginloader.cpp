#include "staticpluginloader.h"

#ifdef OGRE_STATIC_LIB
#ifdef OGRE_BUILD_RENDERSYSTEM_METAL
#include "OgreMetalPlugin.h"
#endif
#endif
#include "OgreRoot.h"

namespace OGraphics
{
	StaticPluginLoader::StaticPluginLoader()
#ifdef OGRE_STATIC_LIB
		:
#ifdef OGRE_BUILD_RENDERSYSTEM_METAL
	mMetalPlugin(0)
#endif
#endif
	{
	}
	//-----------------------------------------------------------------------------------
	StaticPluginLoader::~StaticPluginLoader()
	{
#ifdef OGRE_STATIC_LIB
#ifdef OGRE_BUILD_RENDERSYSTEM_METAL
		OGRE_DELETE mMetalPlugin;
		mMetalPlugin = 0;
#endif
#endif
	}
	//-----------------------------------------------------------------------------------
	void StaticPluginLoader::install(Ogre::Root *root)
	{
#ifdef OGRE_STATIC_LIB
#ifdef OGRE_BUILD_RENDERSYSTEM_METAL
		if (!mMetalPlugin)
			mMetalPlugin = OGRE_NEW Ogre::MetalPlugin();
		root->installPlugin(mMetalPlugin);
#endif
#endif
	}
}
