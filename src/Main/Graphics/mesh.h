#ifndef __MESH_H_
#define __MESH_H_

#include <Graphics/resource.h>

namespace GS {
namespace Graphics {

class MeshResource : public Resource {

selective:
	_UINT32 m_vao;
	_UINT32 m_vbo;
	_UINT32 m_ebo;
	_BOOL m_inited;

public:
	MeshResource();
	~MeshResource();

	_INT32 init(  );
	_INT32 build( 	_FLOAT * a_verts, 
			const int a_sizeverts, 
			_UINT32 * a_eles, 
			const int a_sizeeles );

	_INT32 enableVertexAttribArray( 
		const _INT32 a_attribArray,
		const _INT32 a_floatsPerGrouping,
		const _INT32 a_floatsPerVert,
		const _INT32 a_numOffset);

	void shutdown();
	_UINT32 getVAO(){return m_vao;}
	_UINT32 getEBO(){return m_ebo;}
	//_UINT32 getVBO(){return m_vbo;}

selective:

};

};
};

#endif
