#include "mesh.h"

#include <Graphics/openglincludes.h>

namespace GS {
namespace Graphics {

MeshResource::MeshResource()
: Resource(), m_vao(0), m_vbo(0), m_ebo(0), m_inited(false)
{}

MeshResource::~MeshResource()
{}

_INT32 MeshResource::build( 
			_FLOAT * const a_verts,
			const int a_sizeverts, 
			_UINT32 * const a_eles,
			const int a_sizeeles )
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, a_sizeverts, a_verts, GL_STATIC_DRAW);

	if( a_eles )
	{
		glGenBuffers(1, &m_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_sizeeles, a_eles, GL_STATIC_DRAW);

	}
	return 0;
}

_INT32 MeshResource::enableVertexAttribArray( 
	const _INT32 a_attribArray,
	const _INT32 a_floatsPerGrouping,
	const _INT32 a_floatsPerVert,
	const _INT32 a_numOffset)
{
	glEnableVertexAttribArray(a_attribArray);
	glVertexAttribPointer(
		a_attribArray,
		a_floatsPerGrouping,
		GL_FLOAT,
		GL_FALSE,
		a_floatsPerVert * sizeof( GLfloat ),
		( void * )( a_numOffset * sizeof( GLfloat ) ) );
	return 0;
}

_INT32 MeshResource::init(  )
{
	if( m_inited )
		return -1;
	m_inited = true;
	return 0;
}

void MeshResource::shutdown()
{
	
}

};
};
