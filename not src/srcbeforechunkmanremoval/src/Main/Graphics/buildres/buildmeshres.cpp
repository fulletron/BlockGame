#include <Graphics/reslib.h>

namespace GS {
namespace Graphics {

MeshResource * ResourceLibrary::__buildMeshRes( const _INT64 a_name )
{
	MeshResource newRes;
	
	switch(a_name)
	{
	case CV8::RES_MSH_RECT: {
		_FLOAT vertices[] = {
			-1.0f,  1.0f, 0.0f, 0.0f, // Top-left
			 1.0f,  1.0f, 1.0f, 0.0f, // Top-right
		 	 1.0f, -1.0f, 1.0f, 1.0f, // Bottom-right
			-1.0f, -1.0f, 0.0f, 1.0f  // Bottom-left
		};
		_UINT32 elements[] = {
			0, 1, 2,
			2, 3, 0
		};
	
		newRes.build( 
			vertices, 
			sizeof(vertices), 
			elements,
			sizeof(elements) );
		newRes.enableVertexAttribArray(0, 2, 4, 0);
		newRes.enableVertexAttribArray(1, 2, 4, 2);
		} break;
	case CV8::RES_MSH_SCREEN: {
		_FLOAT vertices[] = {
			-1.0f,  1.0f, 0.0f, 1.0f, // Bottom-left
		 	 1.0f,  1.0f, 1.0f, 1.0f, // Bottom-right
			 1.0f, -1.0f, 1.0f, 0.0f, // Top-right
			-1.0f, -1.0f, 0.0f, 0.0f  // Top-left
		};
		_UINT32 elements[] = {
			0, 1, 2,
			2, 3, 0
		};
	
		newRes.build( 
			vertices, 
			sizeof(vertices), 
			elements,
			sizeof(elements) );
		newRes.enableVertexAttribArray(0, 2, 4, 0);
		newRes.enableVertexAttribArray(1, 2, 4, 2);
		} break;
	default: return 0; 
	}

	newRes.assignName( a_name );
	newRes.addCount();
	_UINT32 loc = m_meshResources.add( newRes );
	return m_meshResources.getp( loc );
}

};
};
