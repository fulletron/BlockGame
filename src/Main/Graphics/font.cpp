#include "font.h"

namespace GS {
namespace Graphics {

// KYLE ::
// TODO ::
// Replace all definitions with my definitions.

_INT32 Font::renderText( const std::string& a_text, const Vector2_t& a_pos )
{
	if( !m_loaded )
		return -1;
	if( a_text.empty() )
		return -2;
	uint32_t vao = 0,
		vbo = 0,
		ibo = 0;

	// Vertex buffer, Index buffer sizes
	uint16_t vlen = a_text.length() << 2;
	uint16_t ilen = a_text.length() * ( ( 1 << 2 ) + 2  );

	// KYLE ::
	// TODO ::
	// use homemade allocator
	Vertex2_t * verts = new Vertex2_t[vlen];
	uint16_t * inds = new uint16_t[ilen];

	memset( inds, 0, sizeof( uint16_t ) * ilen );
	memset( verts, 0, sizeof( Vertex2_t ) * vlen );

	// Track max width & height
	int max_w = 0, max_h = 0;

	// The x-position to start the next character at
	int32_t last_w = a_pos.x;

	// The y pos of the starting character
	float y = a_pos.y;

	for( size_t i = 0; i < vlen; i += 4 )
	{
		_UCHAR c = a_text[ i >> 2 ];
		
		if( c == '\n' )
		{
			last_w = a_pos.x;
			y -= m_biggest_h;
		}

		// the actual letter
		_UCHAR actualLetter = ( c > '~' || c < ' ' ) ? ' ' : c;
		
		// the letter adjusted to fit the m_glyphs index
		_UCHAR letterIndex = actualLetter - m_startingChar;
		
		// dimensions of the current letter
		const Vec4D<_USHORT> & cDim = m_glyphs[letterIndex].dim;
		
		float w = last_w;
		float h = cDim.y;
		last_w = w + cDim.z; // cDim.z is bitmap width

		// Set the vertices
		// KYLE ::
		// TODO ::
		// divide by a non magic number, alternatively, decide
		// how much customization i want in xy values
		verts[i].Position = Vector2_t(w / 800.0f,
					(y + h - (h - cDim.a)) / 600.0f);
		verts[i+1].Position = Vector2_t(last_w  / 800.0f, 
					(y + h - (h - cDim.a) ) / 600.0f);
		verts[i+2].Position = Vector2_t(last_w  / 800.0f, 
					(y - (h - cDim.a)) / 600.0f);
		verts[i+3].Position = Vector2_t(w  / 800.0f, 
					(y - (h - cDim.a)) / 600.0f);
	
		// The relative width OR height of any given character
		// cell on the texture
		float singleCharDim = 1.0f / SC( float, m_numOfCharsRoot );

		int numCharsRootI = SC( int, m_numOfCharsRoot );
		int charIndex = letterIndex;
		
		// this letters beginning cell w, h
		float tx = SC(float,( charIndex % numCharsRootI )) 
				* singleCharDim;
		float ty = SC(float,( charIndex / numCharsRootI )) 
				* singleCharDim;
		
		// current letters w, h in relation to entire (partial cell)
		float thisCharWidth = singleCharDim 
			* (SC(float, cDim.x) / SC(float, m_biggest_w));
		float thisCharHeight = singleCharDim 
			* (SC(float, h) / SC(float, m_biggest_h));
		
		// declare the tex coords
		verts[i+0].TexCoord = Vector2_t(tx, ty);
		verts[i+1].TexCoord = Vector2_t(tx + thisCharWidth, ty);
		verts[i+2].TexCoord = Vector2_t(
				tx + thisCharWidth, ty + thisCharHeight);
		verts[i+3].TexCoord = Vector2_t(tx, ty + thisCharHeight);

		// KYLE ::
		// TODO ::
		// pass in the color as opposed to setting it here!
		// DO NOT HAVE A COLOR MEMBER VARIABLE;
		for( size_t j = i; j < i + 4; ++j )
			verts[j].Color = m_color;

		// Assuming vert 0 is top left and verts are 
		// clockwise, texture quads are indices
		// [0, 1, 3, 3, 2, 1]

		// The index we need is i / 4 * 6, since that
		// gives us the current character, and each
		// character needs 6 indices.
		int x = ( i >> 2 ) * 6;

		inds[x+0] = i + 0;
		inds[x+1] = i + 1;
		inds[x+2] = i + 3;
		inds[x+3] = i + 3;
		inds[x+4] = i + 2;
		inds[x+5] = i + 1;
		
		// keep track of overall dims
		max_w += cDim.x;
		max_h = ( max_h > cDim.a + h ) ? max_h : cDim.a + h ;
	}	
	// KYLE ::
	// TODO ::
	// Enable font render shader. Perhaps	
	
	// Create GPU buffers for vertex/index data
	glGenVertexArrays( 1, &vao );
	glGenBuffers( 1, &vbo );
	glGenBuffers( 1, &ibo );
	
	glBindVertexArray( vao );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibo );
	// Enable the vertex attributes for position, texcoord, color
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	// Give data to GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2_t) * vlen, verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * ilen, inds, GL_STATIC_DRAW);
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
		(void*)(sizeof(uint16_t) * i * 6));
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
	// Delete all buffers.
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);

	_CheckForErrors();

	// KYLE ::
	// TODO ::
	// remove these deletes
	// Delete old buffers in RAM.
	delete[] verts;
	delete[] inds;
	// Give back the total dimensions of the text rendered.
	return 0;
}

_INT32 Font::loadFile( const char * a_fontFile, const int a_size )
{
	// KYLE ::
	// TODO ::
	// move the library initialization out of this function
	// perhaps have a static m_library and do call it here
	FT_Error error;
	error = FT_Init_FreeType( &m_library );
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
	for(size_t i = m_startingChar; i <= endingChar; ++i)
	{
		// KYLE ::
		// ? For cleanup at the end ( unsure if needed!)
		FT_Glyph glyph;

		//Locate the index of the character in the font face
		uint32_t index = FT_Get_Char_Index( m_face, i );
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
		uint32_t w = bitmap.width;
		uint32_t h = bitmap.rows;

		// Store Largest
		if( w > m_biggest_w )
			m_biggest_w = w;
		if( h > m_biggest_h )
			m_biggest_h = h;
		
		// ? clean up!
		FT_Done_Glyph( glyph );
	}
	
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// TODO :: replace with custom mem alloc
	unsigned char* data = new unsigned char[	m_biggest_w * 
							m_biggest_h * 
							m_numOfCharsRoot * 
							m_numOfCharsRoot ];
	memset(data, 0, m_biggest_w * 
			m_biggest_h * 
			m_numOfCharsRoot * 
			m_numOfCharsRoot *
			sizeof(unsigned char) );

	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_R8, 
		m_biggest_w * m_numOfCharsRoot,
		m_biggest_h * m_numOfCharsRoot,
		0, GL_RED, GL_UNSIGNED_BYTE,
		data );

	uint32_t w = 0;
	uint32_t h = 0;

	for( size_t i = m_startingChar; i <= endingChar; ++i )
	{
		FT_Glyph glyph;
		size_t glyphNumCur = i - m_startingChar;
		uint32_t index = FT_Get_Char_Index( m_face, i );

		FT_Load_Glyph( m_face, index, FT_LOAD_RENDER );
		FT_Render_Glyph( m_face->glyph, FT_RENDER_MODE_NORMAL );
		FT_Get_Glyph( m_face->glyph, &glyph );
		
		FT_GlyphSlot slot = m_face->glyph;
		FT_Bitmap& bitmap = slot->bitmap;	
		
		w = bitmap.width;
		h = bitmap.rows;

		// store the needed glyph information in m_glyphs
		m_glyphs[glyphNumCur].loc.x = glyphNumCur % m_numOfCharsRoot;
		m_glyphs[glyphNumCur].loc.y = glyphNumCur / m_numOfCharsRoot;
		m_glyphs[glyphNumCur].dim.x = SC(_USHORT, w);
		m_glyphs[glyphNumCur].dim.y = SC(_USHORT, h);
		m_glyphs[glyphNumCur].dim.z = SC(_USHORT, slot->advance.x >> 6);
		m_glyphs[glyphNumCur].dim.a = SC(_USHORT, slot->metrics.horiBearingY >> 6);
		
		// put the glyph bitmap buffer in the texture
		size_t biggest_char = ( m_biggest_h * m_biggest_w );
		memcpy( 	data + biggest_char * glyphNumCur, 
				bitmap.buffer, 
				sizeof(unsigned char) * w * h );

		// Perhaps an OpenGL Error Check Here? TODO ::

		glTexSubImage2D( GL_TEXTURE_2D, 0,
			m_biggest_w * ( SC(int, glyphNumCur) % 10 ),
			m_biggest_h * ( SC(int, glyphNumCur) / 10 ),
			w, h, GL_RED, GL_UNSIGNED_BYTE,
			data + biggest_char * glyphNumCur );
	}

	_CheckForErrors();

	delete[] data; // TODO ::

	glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
	
	m_loaded = true;

	return 0;
}

#if 0

bool Font::Initialize()
{
	if(s_loaded) return true;
	if(FT_Init_FreeType(&s_Library) != 0) return false;
	return (s_loaded = true);
}

Font::Font() : m_ready(false), m_loaded(false)
{
	// Initialize FreeType.
	if(!Font::Initialize()) return;
	// Load the shader.
	if(!m_FontRender.LoadFromFile("Default.vs", "FontRender.fs"))
	return;
	// Give the font shader an identity matrix for the model-view
	// and the projection matrix that was created with the window.
	m_FontRender.Bind();
	if(	!m_FontRender.SetMatrix("modelview", glm::mat4() ) ||
		!m_FontRender.SetMatrix("proj", Window::s_pWindow->m_projMat))
	return;
	m_FontRender.Unbind();
	m_ready = true;
}

bool Font::LoadFromFile(const std::string& filename, const uint16_t size)
{
	// Make sure everything is ready.
	if(!m_ready || !Font::s_loaded) 
		return false;

	// Create a new font face.
	if(FT_New_Face(s_Library, filename.c_str(), 0, &m_FontFace) != 0)
		return false;
 
	// Set the size of the font face.
	// Since the function expects a size in 1/64 pixels, we multiply
	// by 64 (same as left-shifting 6 bits) before passing.
	// The 96 represents a 96-dpi font bitmap.
	if(FT_Set_Char_Size(m_FontFace, size << 6, size << 6, 96, 96) != 0)
		return false;
 
	// Load all printable characters.
	// If you visit an ASCII table (like www.asciitable.com) you will see
	// that the only valid values for printing are the space character all
	// the way up to the tilde (~).
	for(size_t i = ' '; i <= '~'; ++i)
	{
		FT_Glyph glyph;
 
		// Locate the index of the character in the font face.
		uint32_t index = FT_Get_Char_Index(m_FontFace, i);
		if(index == 0) continue;
 
		// Load the glyph into the font face.
		FT_Load_Glyph(m_FontFace, index, FT_LOAD_RENDER);
 
		// Render the glyph as a mono-chrome bitmap.
		FT_Render_Glyph(m_FontFace->glyph, FT_RENDER_MODE_NORMAL);
 
		// Put the glyph in the glyph slot into an actual glpyh struct.
		FT_Get_Glyph(m_FontFace->glyph, &glyph);
 
		// Small shortcuts
		FT_GlyphSlot slot = m_FontFace->glyph;
		FT_Bitmap& bitmap = slot->bitmap;
 
		// Bitmap dimensions
		uint32_t w = bitmap.width;
		uint32_t h = bitmap.rows;
 
		uint32_t texture = 0;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
 
		// We need to copy the data over to a new buffer in order
		// to properly pass it to the GPU.
		unsigned char* data = new unsigned char[w * h];
		memset(data, NULL, w * h * sizeof(unsigned char));
		memcpy(data, bitmap.buffer, sizeof(unsigned char) * w * h);
 
		// Alignment for pixels needs to be at 1 byte.
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, 0, GL_RED, w, h,
		GL_UNSIGNED_BYTE, data);
		// Restore default alignment value. I haven't actually tested this
		// part so it may or may not actually be the default.
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		// Delete bitmap buffers
		delete[] data;
		FT_Done_Glyph(glyph);
 
		// Our custom glyph structure.
		Font::Glyph render_glyph;
		// render_glyph.pTexture = pTexture;
		render_glyph.texture = texture;
 
		// The dimensions are organized as follows:
		// x: total bitmap width
		// y: total bitmap height
		// w: advancement to the next character
		// h: height offset from the top of the character to the line
		// w and h are represented in 1/64ths of a pixel so we need
		// to convert them to accurate on-screen pixels.
		render_glyph.dim = Rect_t(w, h,
		slot->advance.x >> 6,
		slot->metrics.horiBearingY >> 6);
		// Assign the glyph to its slot in the dictionary.
		mp_glyphTextures[i] = render_glyph;
	}
 
	// Clean up the font face.
	FT_Done_Face(m_FontFace);
 
	// Store the filename internally in-case we need to Resize() later.
	m_filename = filename;
	// We're done!
	return (m_loaded = true);
}

Rect_t Font::RenderText(const std::string& text, const Vector2_t& Pos)
{
	// VAO and buffers that will contain our text vertex data.
	uint32_t vao = 0, vbo = 0, ibo = 0;
	// Track total text size.
	Rect_t Size(Pos.x, Pos.y, 0, 0);
 
	if(!m_loaded || !Font::s_loaded || text.empty()) return Size;
 
	// Vertex buffer size, index buffer size.
	uint16_t vlen = text.length() << 2;
	uint16_t ilen = text.length() * ((1 << 2) + 2);
 
	// Create buffers and zero them.
	Vertex2_t* verts = new Vertex2_t[vlen];
	uint16_t* inds = new uint16_t[ilen];
 
	memset(inds, NULL, sizeof(uint16_t) * ilen);
	memset(verts, NULL, sizeof(Vertex2_t) * vlen);
 
	// Track width and max height.
	int max_w = 0, max_h = 0;
 
	// The x-position to start the next character at.
	int32_t last_w = Pos.x;
	// The y-position of the starting character, for new-lines.
	float y = Pos.y;
 
	// Fill up buffers. Each character needs 4 vertices, so
	// we increment by 4 each iteration then compensate for
	// that throughout the loop.
	for(size_t i = 0; i < vlen; i += 4)
	{
	// Shortcut.
	char c = text[i >> 2];
 
	// Handle new-lines by starting from the x position
	// again and increasing Y by the height of an arbitrary
	// large letter (here H).
	if(c == '\n')
	{
	last_w = Pos.x;
	y += mp_glyphTextures['H'].dim.y + mp_glyphTextures['H'].dim.h;
	}
 
	// We want to make sure the letters are in the range
	// that we've loaded (ASCII printables).
	char letter = (c > '~' || c < ' ') ? ' ' : c;
	// Retrieve dimensions from the dictionary.
	// Since we're doing i += 4, the index in the text string
	// would be text[i / 4].
	Rect_t Dim = mp_glyphTextures[letter].dim;
 
	float w = last_w;
	float h = Dim.y;
	last_w = w + Dim.w; // Increase until next char by the
	// bitmap's horizontal advance value.
 
	// [i] : top left
	// [i + 1] : top right
	// [i + 2] : bottom right
	// [i + 3] : bottom left
	verts[i].Position = Vector2_t(w, y- Dim.h);
	verts[i+1].Position = Vector2_t(last_w, y - Dim.h);
	verts[i+2].Position = Vector2_t(last_w, y - Dim.h + h);
	verts[i+3].Position = Vector2_t(w, y - Dim.h + h);
 
	// Load up the bitmap texture coordinates moving counter-clockwise
	// from the origin.
	verts[i].TexCoord = Vector2_t(0, 0);
	verts[i+1].TexCoord = Vector2_t(1, 0);
	verts[i+2].TexCoord = Vector2_t(1, 1);
	verts[i+3].TexCoord = Vector2_t(0, 1);
 
	// The vertices all use the font color.
	// See CFont::SetColor()
	for(size_t j = i; j < i + 4; ++j)
	verts[j].Color = m_Color;
 
	// A basic textured quad uses the indices [0, 1, 3, 3, 2, 1]
	// assuming that verts[0] is the top-left, and the rest are
	// calculated going clock-wise.
 
	// The index in the buffer that we need is i / 4 * 6, since
	// i / 4 gives us the current character, and each character
	// needs 6 indices.
	int x = (i >> 2) * 6;
 
	// Assign the values.
	inds[x] = i;
	inds[x+1] = i + 1;
	inds[x+2] = i + 3;
	inds[x+3] = i + 3;
	inds[x+4] = i + 2;
	inds[x+5] = i + 1;
 
	// Keep track of the overall dimensions.
	max_w += Dim.w;
	max_h = (max_h > Dim.h + h) ? max_h : Dim.h + h;
	}
 
	// Tally up dimensions.
	Size.w = max_w;
	Size.h = max_h;
 
	// Enable font-rendering shader.
	m_FontRender.Bind();
	// Create GPU buffers for vertex/index data
	glGenBuffers(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
 
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
 
	// Enable the vertex attributes for position, texcoord, and color.
	// See the shader for details.
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	// Give data to GPU.
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2_t) * vlen, verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * ilen, inds, GL_STATIC_DRAW);
 
	// Vertices are arranged in memory like so:
	// [ p0, p1, t0, t1, c0, c1, c2, c3 ]
 
	// Specify vertex position arrangement.
	// According to the diagram shown above, the vertex position
	// would start at index 0.
	// See the VBO_OFFSET macro in CFont.hpp.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
	sizeof(Vertex2_t),
	VBO_OFFSET(0, Vertex2_t, Position));
 
	// Specify texture coordinate position arrangement.
	// According to the diagram, texture coordinates
	// start at index 2.
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
	sizeof(Vertex2_t), VBO_OFFSET(0, Vertex2_t, TexCoord));
 
	// Specify the color arrangement.
	// Starting at index 4.
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE,
	sizeof(Vertex2_t), VBO_OFFSET(0, Vertex2_t, Color));
 
	// Enable blending so that the text doesn't have a black background.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
	// Draw each character with its texture enabled.
	for(size_t i = 0; i < text.length(); ++i)
	{
		// Make invalid characters just spaces (' ')
		char c = (text[i] > '~' || text[i] < ' ') ? ' ' : text[i];
		glBindTexture(GL_TEXTURE_2D, mp_glyphTextures[c]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT,
		(void*)(sizeof(uint16_t) * i * 6));
	}
	// Delete GPU buffers.
	glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);
 
	// Unbind all the things.
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	m_FontRender.Unbind();
	// Delete all buffers.
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
 
	// Delete old buffers in RAM.
	delete[] verts;
	delete[] inds;
	// Give back the total dimensions of the text rendered.
	return Size;
}

#endif

};
};
