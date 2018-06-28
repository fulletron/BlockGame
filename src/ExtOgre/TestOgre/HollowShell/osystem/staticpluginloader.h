#ifndef _STATICPLUGINLOADER_H_
#define _STATICPLUGINLOADER_H_

#include "OgreBuildSettings.h"

namespace Ogre
{
#ifdef OGRE_STATIC_LIB
#ifdef OGRE_BUILD_RENDERSYSTEM_METAL
	class MetalPlugin;
#endif
#endif
	class Root;
}

namespace OGraphics
{
	/// Utility class to load plugins statically
	class StaticPluginLoader
	{
#ifdef OGRE_STATIC_LIB
#ifdef OGRE_BUILD_RENDERSYSTEM_METAL
		Ogre::MetalPlugin           *mMetalPlugin;
#endif
#endif
	public:
		StaticPluginLoader();
		~StaticPluginLoader();

		void install(Ogre::Root *root);
	};
}

#endif

