#ifndef __FONTS_H_
#define __FONTS_H_

#include <Resource\base\resourcefile.h>
#include <Library\library.h>

namespace GS { class Game;
namespace ResourceNS {
	namespace Fonts {
		LibraryNS::IEntry * __init_font(GS::Game * const a_rpGame, const _UINT64 & a_key, const char * a_filename, const int & a_fontSize, GS::LibraryNS::EntryInitFunction a_resInitFunc);

		LibraryNS::IEntry * init_ftkash48(GS::Game * const a_rpGame);
		LibraryNS::IEntry * init_ftxodb64(GS::Game * const a_rpGame);
	};
};
};

#endif