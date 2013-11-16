#ifndef __TEXTURES_H_
#define __TEXTURES_H_

#include <Resource\base\resourcefile.h>

namespace GS { class Game;
namespace ResourceNS {
	namespace Textures {
		GS::LibraryNS::IEntry * __init_texture(GS::Game * const a_rpGame, const _UINT64 & a_key, const char * a_filename);

		GS::LibraryNS::IEntry * init_panebk00(GS::Game * const a_rpGame);
		GS::LibraryNS::IEntry * init_smalbk00(GS::Game * const a_rpGame);
	};
};
};

#endif