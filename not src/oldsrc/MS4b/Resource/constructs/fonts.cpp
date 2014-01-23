#include "fonts.h"
#include "shaderprograms.h"
#include "..\base\fontresource.h"
#include "..\base\shaderprogramresource.h"
#include <Game\game.h>
#include "..\..\Utilities\gsinlines.h"
#include <Game\inlines.h>

namespace GS {
namespace ResourceNS {
namespace Fonts {
	LibraryNS::IEntry * __init_font(GS::Game * const a_rpGame, const _UINT64 & a_key, const char * a_filename, const int & a_fontSize, GS::LibraryNS::EntryInitFunction a_resInitFunc)
	{

		FontResource * ret = (FontResource *)a_rpGame->getLibrary()->getEntry(a_key);

		if(!ret)
		{
			std::string t_completeFilepath = GS::UtilitiesNS::getDirectory().c_str();
			t_completeFilepath.append(DIR_S DIR_IN DIR_RES DIR_FONTS);
			t_completeFilepath.append(a_filename);

			std::string failMessage = "FAILED TO INIT FONT KEY: ";
			failMessage.append((char*)a_key);

			ret = new FontResource();
			DBC(ret->init(	a_rpGame, 
						t_completeFilepath.c_str(), 
						a_fontSize,
						a_resInitFunc
						), failMessage.c_str());
		}

		return a_rpGame->getLibrary()->addEntry(a_key, (GS::LibraryNS::IEntry *)ret);
	}
		
	LibraryNS::IEntry * init_ftkash48(GS::Game * const a_rpGame)
	{
		return __init_font(	a_rpGame,
							(_UINT64)"ftkash48",
							"KaushanScript-Regular.otf",
							48,
							GS::ResourceNS::ShaderPrograms::init_spfontdr
						);

		//ftFont.loadFont("Internal\\Resources\\Fonts\\Delicious-Roman.otf",64);
		//ftFont.loadFont("Internal\\Resources\\Fonts\\KaushanScript-Regular.otf",48);
		//ftFont.loadFont("Internal\\Resources\\Fonts\\Exo-DemiBold-Italic.otf",64);
		//ftFont.loadFont("Internal\\Resources\\Fonts\\Exo-DemiBold.otf",64);
		//ftFont.loadFont("Internal\\Resources\\Fonts\\Exo-Regular.otf",64);
		//ftFont.loadFont("Internal\\Resources\\Fonts\\Adler.ttf",64);
		//ftFont.loadFont("Internal\\Resources\\Fonts\\comic.ttf",64);
	}

	LibraryNS::IEntry * init_ftxodb64(GS::Game * const a_rpGame)
	{
		return __init_font(	a_rpGame,
							(_UINT64)"ftxodb64",
							"Exo-DemiBold.otf",
							64,
							GS::ResourceNS::ShaderPrograms::init_spfontdr
						);
	}
};
};
};