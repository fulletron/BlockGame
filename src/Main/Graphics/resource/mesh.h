#ifndef __MESH_H_
#define __MESH_H_

#include "iresource.h"

namespace GS {
namespace Resource {

class MeshResource : public IResource {

selective:
	_UINT32 m_vao;
	_UINT32 m_vbo;
	_UINT32 m_ebo;

public:
	MeshResource();
	~MeshResource();

	_UINT32 init();
	_UINT32 shutdown();
	
	_UINT32 build( 	_FLOAT * a_verts, 
			const int a_sizeverts, 
			_UINT32 * a_eles, 
			const int a_sizeeles );

	_UINT32 enableVertexAttribArray( 
		const _INT32 a_attribArray,
		const _INT32 a_floatsPerGrouping,
		const _INT32 a_floatsPerVert,
		const _INT32 a_numOffset);

	_UINT32 getVAO(){return m_vao;}
	_UINT32 getEBO(){return m_ebo;}
	_UINT32 getVBO(){return m_vbo;}
};

};
};

#endif
