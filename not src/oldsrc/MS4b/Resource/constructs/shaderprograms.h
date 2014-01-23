#ifndef __SHADERPROGRAMS_H_
#define __SHADERPROGRAMS_H_

#include <Resource\base\resourcefile.h>

namespace GS { class Game;
namespace ResourceNS {
namespace ShaderPrograms {
	GS::LibraryNS::IEntry * __init_shaderProgram(GS::Game * const a_rpGame, const _UINT64 & a_key, GS::LibraryNS::EntryInitFunction a_vsFunc, GS::LibraryNS::EntryInitFunction a_fsFunc);
	
	GS::LibraryNS::IEntry * init_spfontdr(GS::Game * const a_rpGame);
	GS::LibraryNS::IEntry * init_spscrn00(GS::Game * const a_rpGame);
};

};
};

#endif