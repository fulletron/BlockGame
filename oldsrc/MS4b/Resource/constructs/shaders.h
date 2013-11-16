#ifndef __SHADERS_H_
#define __SHADERS_H_

#include <Resource\base\resourcefile.h>

namespace GS { class Game;
namespace ResourceNS {
	namespace Shaders {
		GS::LibraryNS::IEntry * __init_shader(GS::Game * a_rpGame, const char * a_charStream, int a_shaderType);

		GS::LibraryNS::IEntry * init_vsfont00(GS::Game * a_rpGame);
		GS::LibraryNS::IEntry * init_fsfont00(GS::Game * a_rpGame);

		GS::LibraryNS::IEntry * init_vsscrn00(GS::Game * a_rpGame);
		GS::LibraryNS::IEntry * init_fsscrn00(GS::Game * a_rpGame);

		GS::LibraryNS::IEntry * init_vs2dtex0(GS::Game * a_rpGame);
		GS::LibraryNS::IEntry * init_fs2dtex0(GS::Game * a_rpGame);
	};
};
};

#endif