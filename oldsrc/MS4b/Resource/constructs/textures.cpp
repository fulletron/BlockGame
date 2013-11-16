#include "..\base\textureresource.h"
#include <Game\game.h>
#include "..\..\Utilities\gsinlines.h" /// getDirectory
#include <Game\inlines.h> /// DBC
#include "textures.h"

namespace GS {
namespace ResourceNS {
namespace Textures {
	GS::LibraryNS::IEntry * __init_texture(GS::Game * const a_rpGame, const _UINT64 & a_key, const char * a_filename)
	{
		TextureResource * ret = (TextureResource *)a_rpGame->getLibrary()->getEntry(a_key);
		
		if(!ret)
		{

			std::string t_completeFilepath = GS::UtilitiesNS::getDirectory().c_str();
			t_completeFilepath.append(DIR_S DIR_IN DIR_RES DIR_TEXTS);
			t_completeFilepath.append(a_filename);

			std::string failMessage = "FAILED TO INIT TEXTURE KEY: ";
			failMessage.append((char*)a_key);

			ret = new TextureResource();
			DBC(ret->init(	a_rpGame, 
						t_completeFilepath.c_str(), 
						false
						), failMessage.c_str());
		}

		return a_rpGame->getLibrary()->addEntry(a_key, (GS::ResourceNS::IResourceFile *)ret);
	}
		
	GS::LibraryNS::IEntry * init_panebk00(GS::Game * const a_rpGame)
	{
		return __init_texture(	a_rpGame,
							(_UINT64)"panebk00",
							"panebkg.png"
						);
	}

	GS::LibraryNS::IEntry * init_smalbk00(GS::Game * const a_rpGame)
	{
		return __init_texture(	a_rpGame,
							(_UINT64)"smalbk00",
							"smallpanelbacking.png"
						);
	}

};
};
};