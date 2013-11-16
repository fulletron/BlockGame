#ifndef __MESHES_H_
#define __MESHES_H_

#include <Resource\base\resourcefile.h>

namespace GS { class Game;
namespace ResourceNS {
	namespace Meshes {
		GS::LibraryNS::IEntry * __init_mesh(GS::Game * a_rpGame, 
			const _UINT64 & a_meshKey,
			const _UINT32 & a_glDrawType,
			const float * const a_vertices,
			const _UINT32 & a_numVertices,
			const _UINT32 * const a_elements,
			const _UINT32 &	a_numElements);

		GS::LibraryNS::IEntry * init_mzscrn00(GS::Game * a_rpGame);
	};
};
};

#endif