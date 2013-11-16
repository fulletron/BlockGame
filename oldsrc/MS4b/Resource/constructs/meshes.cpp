#include "meshes.h"
#include "..\base\meshresource.h"
#include <Game\game.h>

namespace GS { 
namespace ResourceNS {
	namespace Meshes {
		GS::LibraryNS::IEntry * __init_mesh(GS::Game * a_rpGame, 
			const _UINT64 & a_meshKey,
			const _UINT32 & a_glDrawType,
			const float * const a_vertices,
			const _UINT32 & a_numVertices,
			const _UINT32 * const a_elements,
			const _UINT32 &	a_numElements)
		{
			MeshResource * ret = (MeshResource *)a_rpGame->getLibrary()->getEntry(a_meshKey);
		
			if(!ret)
			{
				ret = new MeshResource();
				ret->init(		a_rpGame,
								a_glDrawType,
								a_vertices,
								a_numVertices,
								a_elements,
								a_numElements
							);
			}
			return a_rpGame->getLibrary()->addEntry(a_meshKey, (GS::ResourceNS::IResourceFile *)ret);
		}

		GS::LibraryNS::IEntry * init_mzscrn00(GS::Game * a_rpGame)
		{

			//STD 
			/*
				-1.0f,  1.0f,  0.0f, 1.0f,
				 1.0f,  1.0f,  1.0f, 1.0f,
				 1.0f, -1.0f,  1.0f, 0.0f,

				 1.0f, -1.0f,  1.0f, 0.0f,
				-1.0f, -1.0f,  0.0f, 0.0f,
				-1.0f,  1.0f,  0.0f, 1.0f
				*/

			// Quad vertices
			_UINT32 numVertsTexcoords = 24;
			float vertsTexcoords[] = {
				-1.0f,  1.0f,  0.0f, 1.0f,
				 1.0f,  1.0f,  1.0f, 1.0f,
				 1.0f, -1.0f,  1.0f, 0.0f,

				 1.0f, -1.0f,  1.0f, 0.0f,
				-1.0f, -1.0f,  0.0f, 0.0f,
				-1.0f,  1.0f,  0.0f, 1.0f
			};

			return __init_mesh(	a_rpGame,
								(_UINT64)"mzscrn00",
								GL_TRIANGLES,
								vertsTexcoords,
								numVertsTexcoords,
								0,
								0
							);
		}
	};
};
};