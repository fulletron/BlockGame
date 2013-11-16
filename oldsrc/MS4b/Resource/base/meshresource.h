#include "..\base\resourcefile.h"
#include <Graphics\openglincludes.h>

namespace GS { class Game;
namespace ResourceNS {

	class MeshResource : public IResourceFile
	{
	public:
	private:
		GS::Game *				m_rpGame;

		_UINT32					m_glDrawType;
		_UINT32					m_numVerts;
		_UINT32					m_numElements;


		GLuint					m_vao;
		GLuint					m_vbo;
		GLuint					m_ebo;

	public:

		GET_ACCESSOR( GLuint , m_vao );
		GET_ACCESSOR( GLuint , m_vbo );
		GET_ACCESSOR( GLuint , m_ebo );
		bool isElementArray(){return m_numElements?true:false;}

		_UINT32 init(GS::Game * a_rpGame, 
			const _UINT32 & a_glDrawType, 
			const float * const a_vertices, 
			const _UINT32 & a_numVertices, 
			const _UINT32 * const a_elements = 0,
			const _UINT32 & a_numElements = 0)
		{
			m_rpGame = a_rpGame;
			m_glDrawType = a_glDrawType;
			m_numVerts = a_numVertices;

			glGenVertexArrays( 1, &m_vao );
			glBindVertexArray( m_vao );

			// Create a Vertex Buffer Object and copy the vertex data to it
			//GLuint vbo2;
			glGenBuffers( 1, &m_vbo );
			glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
			glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * a_numVertices, a_vertices, GL_STATIC_DRAW );

			if(a_elements == 0 || a_numElements == 0)
			{
				m_ebo = 0;
				m_numElements = 0;
			}
			else
			{
				m_numElements = a_numElements;
				glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ebo );
				glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( a_numElements ), a_elements, GL_STATIC_DRAW );
			}

			return 0;
		}

		void drawGL()
		{
			if(isElementArray())
			{
				glDrawElements( m_glDrawType, m_numElements, GL_UNSIGNED_INT, 0 );
			}
			else
			{
				glDrawArrays( m_glDrawType, 0, m_numVerts );
			}
		}

		// I DO NOT NEED ELEMENT ARRAYS, BUT I MIGHT WANT THEM?
		void shutdown()
		{
			glDeleteBuffers( 1, &m_vbo );
			glDeleteVertexArrays( 1, &m_vao );
			if(m_numElements)
				glDeleteBuffers( 1, &m_ebo );
		}
	};

};
};