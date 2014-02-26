#include "font.h"

extern GS::Utilities::ChunkManager g_chunkman;
extern GS::Graphics::Window g_window;

FT_Library GS::Graphics::FontResource::m_library = 0;
_BOOL GS::Graphics::FontResource::m_libraryLoaded = false;

namespace GS {
namespace Graphics {

_INT32 FontResource::renderText(const std::string & a_text, 
						const Vector2_t & a_pos, 
						const Color4f_t & a_color)
{
	// if it isn't ready, don't do it!
	if( !m_libraryLoaded )
		return -1;
	if( !m_loaded )
		return -2;
	if( a_text.empty() )
		return -3;

	// there will be temporary allocation in this portion of code
	// this replaces NEW
	GS::Utilities::Frame * pTrash = g_chunkman.getFrame( FR_TRASH );
	pTrash->setfStop(TOP);

	// Vertex buffer, Index buffer sizes
	_USHORT vlen = a_text.length() << 2;
	_USHORT ilen = a_text.length() * ( ( 1 << 2 ) + 2  );

	// allocate verts and inds. use custom allocation
	_TChunkPtr<Vertex2_t> verts;
	verts = g_chunkman.allocate(pTrash, sizeof( Vertex2_t ) * vlen, TOP);

	_TChunkPtr<_USHORT> inds;
	inds = g_chunkman.allocate(pTrash, sizeof( _USHORT ) * ilen, TOP);

	memset( inds.pointer(), 0, sizeof( _USHORT ) * ilen );
	memset( verts.pointer(), 0, sizeof( Vertex2_t ) * vlen );

	// Track max width & height
	_INT32 max_w = 0, max_h = 0;

	// The x-position to start the next character at
	_INT32 right_w = a_pos.x;

	// The y pos of the starting character
	float y = a_pos.y;

	for( _SIZET i = 0; i < vlen; i += 4 )
	{
		_UCHAR c = a_text[ i >> 2 ];

		// the actual letter
		_UCHAR actualLetter = ( c > '~' || c < ' ' ) ? ' ' : c;
		
		// the letter adjusted to fit the m_glyphs index
		_UCHAR letterIndex = actualLetter - m_startingChar;
		
		// dimensions of the current letter
		const GlyphInAtlas & glyph = m_glyphs[letterIndex];

		// TODO ::
		// MODIFY THE VALUES
		float passedHeight = 1.0f; ///
		float dimensionMulti = (passedHeight * 600.0f) / m_biggest_h; ///
		
		if( c == '\n' )
		{
			right_w = a_pos.x;
			y -= m_biggest_h;
		}

		float left_w = right_w;
		float h = glyph.height;
		float hby = glyph.horizBearingY;
		right_w = left_w + glyph.advanceX;


		// Set the vertices
		// KYLE ::
		// TODO ::
		// divide by a non magic number, alternatively, decide
		// how much customization i want in xy values
		verts.pointer()[i+0].Position = 
			Vector2_t( ( left_w + glyph.horizBearingX ) / 800.0f,
			(y + glyph.horizBearingY) / 600.0f);
		verts.pointer()[i+1].Position = 
			Vector2_t( ( left_w + glyph.width + glyph.horizBearingX ) / 800.0f,
			(y + glyph.horizBearingY) / 600.0f);
		verts.pointer()[i+2].Position = 
			Vector2_t( ( left_w + glyph.width + glyph.horizBearingX ) / 800.0f, // as opposed to right
			(y + glyph.horizBearingY - glyph.height) / 600.0f);
		verts.pointer()[i+3].Position = 
			Vector2_t( ( left_w + glyph.horizBearingX ) / 800.0f,
			(y + glyph.horizBearingY - glyph.height) / 600.0f);
		
	
		// The relative width OR height of any given character
		// cell on the texture
		float singleCharDim = 1.0f / SC( float, m_numOfCharsRoot );

		_UCHAR numCharsRootI = SC( _UCHAR, m_numOfCharsRoot );
		_USHORT charIndex = letterIndex;
		
		// this letters beginning cell w, h
		float tx = SC(float,( charIndex % numCharsRootI )) 
				* singleCharDim;
		float ty = SC(float,( charIndex / numCharsRootI )) 
				* singleCharDim;

		// current letters w, h in relation to entire (partial cell)
		float thisCharWidth = singleCharDim 
			* (SC(float, glyph.width) / SC(float, m_biggest_w));
		float thisCharHeight = singleCharDim 
			* (SC(float, (glyph.height)) / SC(float, m_biggest_h));
		
		// declare the tex coords
		verts.pointer()[i+0].TexCoord = Vector2_t(tx, ty);
		verts.pointer()[i+1].TexCoord = Vector2_t(tx + thisCharWidth, ty);
		verts.pointer()[i+2].TexCoord = Vector2_t(
				tx + thisCharWidth, ty + thisCharHeight);
		verts.pointer()[i+3].TexCoord = Vector2_t(tx, ty + thisCharHeight);

		// Set the color!
		for( size_t j = i; j < i + 4; ++j )
			verts.pointer()[j].Color = a_color;

		// Assuming vert 0 is top left and verts are 
		// clockwise, texture quads are indices
		// [0, 1, 3, 3, 2, 1]

		// The index we need is i / 4 * 6, since that
		// gives us the current character, and each
		// character needs 6 indices.
		_USHORT x = ( i >> 2 ) * 6;

		inds.pointer()[x+0] = i + 0;
		inds.pointer()[x+1] = i + 1;
		inds.pointer()[x+2] = i + 3;
		inds.pointer()[x+3] = i + 3;
		inds.pointer()[x+4] = i + 2;
		inds.pointer()[x+5] = i + 1;
		
		// keep track of overall dims
		max_w += glyph.height;
		max_h = ( max_h > glyph.horizBearingY + h ) ? max_h : glyph.horizBearingY + h ;
	}	
	// KYLE ::
	// TODO ::
	// Enable font render shader. Perhaps	
	
	glBindVertexArray( m_vao );
	glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ibo );
	// Enable the vertex attributes for position, texcoord, color
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	// Give data to GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2_t) * vlen, verts.pointer(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_USHORT) * ilen, inds.pointer(), GL_STATIC_DRAW);
	// Vertices are arranged in memory like so:
	// [ p0, p1, t0, t1, c0, c1, c2, c3 ]

	// vertex position starts at index 0.
	// VBO_OFFSET macro
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex2_t),VBO_OFFSET(0, Vertex2_t, Position));

	// texture coordinates start at index 2
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex2_t), VBO_OFFSET(0, Vertex2_t, TexCoord));
	// color floats start at index 4
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE,
		sizeof(Vertex2_t), VBO_OFFSET(0, Vertex2_t, Color));

	// Enable blending so that the text doesn't have a black background.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw each character
	for(size_t i = 0; i < a_text.length(); ++i)
	{
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT,
		(void*)(sizeof(_USHORT) * i * 6));
	}	
	
	// Delete GPU buffers.
	glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);

	// Unbind all the things.

	//glBindTexture(GL_TEXTURE_2D, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//m_FontRender.Unbind();

	_CheckForErrors();

	// Reset trash frames allocation back to top!
	pTrash->freefStop(TOP);

	// Give back the total dimensions of the text rendered.
	return 0;
}

_INT32 FontResource::initializeLibrary()
{
	if( m_libraryLoaded )
		return 0;

	FT_Error error;
	error = FT_Init_FreeType( &m_library );
	if( error )
		return error;

	m_libraryLoaded = true;
	return 0;
}

_INT32 FontResource::loadFile( const char * a_fontFile, const int a_size )
{
	FT_Error error;
	error = initializeLibrary();
	if( error )
		return error;

	_GSPath path = GS::Utilities::FileSystem::getCurrentFullPath();	
	path /= "./Internal/Resources/Fonts/";
	path /= a_fontFile;

	// m_face is the handle to the entire set of characters
	error = FT_New_Face(	m_library,
				path.string().c_str(),
				0,
				&m_face );
	
	if( error )
		return error;

	error = FT_Set_Char_Size(
				m_face,		
				0,		//char_width 1/64th of point
				a_size * 64,	//char_height ''''
				300,		//horizontal device res
				300 ); 		//vertical device res

	if( error )
		return error;

	// SETTING THE CHARACTER RANGE
	// MOST PROBABLY MISPLACED
	// KYLE ::
	m_startingChar = ' ';
	_UCHAR endingChar = '~';
	m_numOfCharsRoot = 
		GS::Utilities::Misc::getClosestSquareRoot( 
					endingChar - m_startingChar + 1 );
	m_biggest_w = 0;
	m_biggest_h = 0;

	// Find the size of a cell on the font texture atlas
	// This is done by looking up all of the text and finding
	// the largest w and largest h.
	for(_SIZET i = m_startingChar; i <= endingChar; ++i)
	{
		// KYLE ::
		// ? For cleanup at the end ( unsure if needed!)
		FT_Glyph glyph;

		//Locate the index of the character in the font face
		_UINT32 index = FT_Get_Char_Index( m_face, i );
		if(index == 0) continue; // if this one doesn't exise, skip
		
		// Load the glyph into the font face
		FT_Load_Glyph( m_face, index, FT_LOAD_RENDER );

		// Render the glyph as a mono-chrome bitmap
		FT_Render_Glyph( m_face->glyph, FT_RENDER_MODE_NORMAL );

		// ? Set glyph so i can call glyph_done
		FT_Get_Glyph( m_face->glyph, &glyph );

		// Small Shortcuts
		FT_GlyphSlot slot = m_face->glyph;
		FT_Bitmap& bitmap = slot->bitmap;

		// Bitmap dimensions
		_UINT32 w = bitmap.width;
		_UINT32 h = bitmap.rows;

		// Store Largest
		if( w > m_biggest_w )
			m_biggest_w = w;
		if( h > m_biggest_h )
			m_biggest_h = h;
		
		// ? clean up!
		FT_Done_Glyph( glyph );
	}

	// there will be temporary allocation in this portion of code
	// this replaces NEW
	GS::Utilities::Frame * pTrash = g_chunkman.getFrame( FR_TRASH );
	pTrash->setfStop(TOP);
	
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// CUSTOM ALLOCATION!
	_TChunkPtr<_UCHAR> data;
	data = g_chunkman.allocate( pTrash, 
							sizeof( _UCHAR ) * 
							m_biggest_w * 
							m_biggest_h * 
							m_numOfCharsRoot * 
							m_numOfCharsRoot,
							TOP);

	memset(data.pointer(), 0, m_biggest_w * 
			m_biggest_h * 
			m_numOfCharsRoot * 
			m_numOfCharsRoot *
			sizeof(unsigned char) );

	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_R8, 
		m_biggest_w * m_numOfCharsRoot,
		m_biggest_h * m_numOfCharsRoot,
		0, GL_RED, GL_UNSIGNED_BYTE,
		data.pointer() );

	_UINT32 w = 0;
	_UINT32 h = 0;

	for( size_t i = m_startingChar; i <= endingChar; ++i )
	{
		FT_Glyph glyph;
		size_t glyphNumCur = i - m_startingChar;
		_UINT32 index = FT_Get_Char_Index( m_face, i );

		FT_Load_Glyph( m_face, index, FT_LOAD_RENDER );
		FT_Render_Glyph( m_face->glyph, FT_RENDER_MODE_NORMAL );
		FT_Get_Glyph( m_face->glyph, &glyph );
		
		FT_GlyphSlot slot = m_face->glyph;
		FT_Bitmap& bitmap = slot->bitmap;	
		
		w = bitmap.width;
		h = bitmap.rows;

		// store the needed glyph information in m_glyphs
		m_glyphs[glyphNumCur].horizBearingX = SC(_SHORT, slot->metrics.horiBearingX >> 6);
		m_glyphs[glyphNumCur].horizBearingY = SC( _SHORT, slot->metrics.horiBearingY >> 6);
		m_glyphs[glyphNumCur].advanceX = SC( _SHORT, slot->advance.x >> 6 );
		m_glyphs[glyphNumCur].height = SC( _SHORT, h );
		m_glyphs[glyphNumCur].width = SC( _SHORT, w );
		
		// put the glyph bitmap buffer in the texture
		size_t biggest_char = ( m_biggest_h * m_biggest_w );
		memcpy( 	data.pointer() + biggest_char * glyphNumCur, 
				bitmap.buffer, 
				sizeof(unsigned char) * w * h );

		// Perhaps an OpenGL Error Check Here? TODO ::

		glTexSubImage2D( GL_TEXTURE_2D, 0,
			m_biggest_w * ( SC(int, glyphNumCur) % 10 ),
			m_biggest_h * ( SC(int, glyphNumCur) / 10 ),
			w, h, GL_RED, GL_UNSIGNED_BYTE,
			data.pointer() + biggest_char * glyphNumCur );
	}

	_CheckForErrors();

	// reset allocated memory
	pTrash->freefStop(TOP);

	glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );

	// Create GPU buffers for vertex/index data
	glGenVertexArrays( 1, &m_vao );
	glGenBuffers( 1, &m_vbo );
	glGenBuffers( 1, &m_ibo );
	
	m_loaded = true;

	return 0;
}

void FontResource::destroyLibrary()
{
	if ( !m_libraryLoaded )
		return;

	FT_Done_FreeType( m_library );
	m_libraryLoaded = false;
}

void FontResource::shutdown(bool a_killLib)
{
	glDeleteVertexArrays(1, &m_vao); 
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);

	glDeleteTextures(1, &m_texture);
	FT_Done_Face( m_face );
	if( a_killLib )
	{
		destroyLibrary();
	}
	m_loaded = false;
}

FontResource::FontResource()
{
	m_libraryLoaded = false; 
	m_loaded = false;
}

FontResource::~FontResource()
{
}

};
};
