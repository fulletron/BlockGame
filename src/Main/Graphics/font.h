#ifndef __FONT_H_
#define __FONT_H_

#include <Utilities/utilities.h>
#include <Graphics/openglincludes.h>
#include "graphics.h"

// MORE HELP ON THE WEB
// http://www.freetype.org/freetype2/docs/tutorial/step1.html

#include "fonthelpers.h"
//#define VBO_OFFSET(count, vertex, field) (void*)((count * sizeof(vertex)) + (long int)&(((vertex*)NULL)->field))

namespace GS {
namespace Graphics {

class Font {

#ifdef TEST_ENABLED
public:
#else
protected:
#endif

public:

	_BOOL m_loaded;
	struct Glyph
	{
		// OpenGL texture handle for the bitmap
		uint32_t texture;
		// Dimensions and offsets.
		Rect_t dim;
	};

	class GlyphInAtlas
	{
	public:
		Vec4D<_USHORT> dim;
		Vec2D<_UCHAR> loc;

		GlyphInAtlas(){}
	};

	FT_Library	m_library;
	FT_Face		m_face;

	uint32_t	m_texture;

	GlyphInAtlas m_glyphs[100];

	uint32_t  m_biggest_w, m_biggest_h;

	_UCHAR m_startingChar;
	_UCHAR m_numOfCharsRoot;

	Color4f_t m_color;

	Font(){m_loaded = false;}
	~Font(){}


	/// THIS IS STILL REALLY MESSY
	/// CURRENTLY WORKING ON IT!
	_INT32 init()
	{
		FT_Error error;

		// Initially loads the library
		error = FT_Init_FreeType( &m_library );
		if (error)
			return error;

		boost::filesystem::path full_path( boost::filesystem::current_path() );
		//boost::filesystem::path test("./Internal/Resources/Fonts/KaushanScript-Regular.otf");
		full_path /= "./Internal/Resources/Fonts/KaushanScript-Regular.otf";

		// a new face, which is an otf or ttf
		error = FT_New_Face(	m_library,
								full_path.string().c_str(),
								0,
								&m_face );

		//error = FT_New_Memory_Face(	m_library,
		//							buffer,
		//							size,
		//							0,
		//							&m_face );

		if ( error == FT_Err_Unknown_File_Format )
			return error;
		else if ( error )
			return error;

		// Setting character size
		error = FT_Set_Char_Size(
						m_face, /* handle to face object */ 
						0, /* char_width in 1/64th of points */ 
						16*64, /* char_height in 1/64th of points */ //16
						300, /* horizontal device resolution */ 
						300 ); /* vertical device resolution */
		if (error)
			return error;
		/*
		// FT_Set_Char_Size computes pixel size... this
		// is the override!
		//error = FT_Set_Pixel_Sizes(
		//					m_face,
		//					0,
		//					16);
		//if (error)
		//	return error;

		// Load character
		FT_GlyphSlot slot = m_face->glyph;
		FT_UInt glyph_index;

		// look in the face for a specific glyph
		glyph_index = FT_Get_Char_Index( m_face, 'a' );
		if (!glyph_index)
			return -123;

		// from the glyph index, load a glyph into the "slot". the slot
		// is elsewhere
		error = FT_Load_Glyph( m_face, glyph_index, FT_LOAD_DEFAULT );
		if (error)
			return error;

		// convert the "slot" to a bitmap
		error = FT_Render_Glyph( m_face->glyph,
								FT_RENDER_MODE_NORMAL);
		if (error)
			return error;

		&slot->bitmap;

		*/

		/*


		uint32_t m_biggest_w = 0;
		uint32_t m_biggest_h = 0;
		int numOfChars = '~' - ' ' + 1;

		for(size_t i = ' '; i <= '~'; ++i)
		{
			FT_Glyph glyph;
 
			// Locate the index of the character in the font face.
			uint32_t index = FT_Get_Char_Index(m_face, i);
			if(index == 0) continue;
 
			// Load the glyph into the font face.
			FT_Load_Glyph(m_face, index, FT_LOAD_RENDER); // RENDER ????
 
			// Render the glyph as a mono-chrome bitmap.
			FT_Render_Glyph(m_face->glyph, FT_RENDER_MODE_NORMAL);
 
			// Put the glyph in the glyph slot into an actual glpyh struct.
			FT_Get_Glyph(m_face->glyph, &glyph);
 
			// Small shortcuts
			FT_GlyphSlot slot = m_face->glyph;
			FT_Bitmap& bitmap = slot->bitmap;
 
			// Bitmap dimensions
			uint32_t w = bitmap.width;
			uint32_t h = bitmap.rows;

			if( w > m_biggest_w )
				biggest_w = w;
			if( h > m_biggest_h )
				biggest_h = h;
		}

		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		int tTexWidth = m_biggest_w * 10;
		int tTexHeight = m_biggest_h * 10;

		// create data ptr to hold every letter (needs to be 100 chars
		unsigned char* data = new unsigned char[biggest_w * m_biggest_h * 100];
		memset(data, 0, tTexWidth * tTexHeight * sizeof(unsigned char));

		// Load all printable characters.
		// If you visit an ASCII table (like www.asciitable.com) you will see
		// that the only valid values for printing are the space character all
		// the way up to the tilde (~).
		for(size_t i = ' '; i <= '~'; ++i)
		{
			size_t glyphNumCur = i - ' ';

			FT_Glyph glyph;
 
			// Locate the index of the character in the font face.
			uint32_t index = FT_Get_Char_Index(m_face, i);
			if(index == 0) continue;
 
			// Load the glyph into the font face.
			FT_Load_Glyph(m_face, index, FT_LOAD_RENDER); // RENDER ????
 
			// Render the glyph as a mono-chrome bitmap.
			FT_Render_Glyph(m_face->glyph, FT_RENDER_MODE_NORMAL);
 
			// Put the glyph in the glyph slot into an actual glpyh struct.
			FT_Get_Glyph(m_face->glyph, &glyph);
 
			// Small shortcuts
			FT_GlyphSlot slot = m_face->glyph;
			FT_Bitmap& bitmap = slot->bitmap;
 
			// Bitmap dimensions
			uint32_t w = bitmap.width;
			uint32_t h = bitmap.rows;

			// STORE THE NEEDED INFORMATION TO FIND THE DAMN TEXT
			m_glyphs[glyphNumCur].glyphLoc.x = glyphNumCur % 10;
			m_glyphs[glyphNumCur].glyphLoc.y = glyphNumCur / 10;
			m_glyphs[glyphNumCur].glyphDim.x = SC(_USHORT, w);
			m_glyphs[glyphNumCur].glyphDim.y = SC(_USHORT, h);
			m_glyphs[glyphNumCur].glyphDim.z = SC(_USHORT, slot->advance.x >> 6);
			m_glyphs[glyphNumCur].glyphDim.a = SC(_USHORT, slot->metrics.horiBearingY >> 6);
 
			memcpy(data + (glyphNumCur * m_biggest_w + ((glyphNumCur / 10) % m_biggest_h)), bitmap.buffer, sizeof(unsigned char) * w * h);
 
			FT_Done_Glyph(glyph);
		}

		int test = glGetError();
		if (test != GL_NO_ERROR)
			return -38989;

		// Alignment for pixels needs to be at 1 byte.
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, 0, GL_RED, tTexWidth, tTexHeight, GL_UNSIGNED_BYTE, data);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, tTexWidth, tTexHeight, 0, GL_RED, GL_UNSIGNED_BYTE, data);
		// Restore default alignment value. I haven't actually tested this
		// part so it may or may not actually be the default.
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

		test = glGetError();
		if (test != GL_NO_ERROR)
			return -38989;

		// Delete bitmap buffers
		delete[] data;

		*/

		

		//// selecting a non-standard char map
		//error = FT_Select_CharMap( 
		//	face, /* target face object */ 
		//	FT_ENCODING_BIG5 ); /* encoding */
		//if (error)
		//	return error;

		//// scrolling through non-standard char maps
		//FT_CharMap found = 0; 
		//FT_CharMap charmap; 
		//int n; 
		//
		//for ( n = 0; n < face->num_charmaps; n++ ) 
		//{ 
		//	charmap = face->charmaps[n]; 
		//	if ( charmap->platform_id == my_platform_id 
		//		&& charmap->encoding_id == my_encoding_id ) 
		//	{ 
		//		found = charmap; break; 
		//	} 
		//} 
		//if ( !found ) 
		//{ ... } /* now, select the charmap for the face object */ 

		//error = FT_Set_CharMap( face, found ); 
		//if ( error ) 
		//{ ... }

		//// changes the transform in the slot, applies to anything in the slot
		//error = FT_Set_Transform(
		//			m_face, /* target face object */
		//			&matrix, /* pointer to 2x2 matrix */
		//			&delta); /* pointer to 2d vector */
		//if (error)
		//	return error;

		m_startingChar = ' ';
		_UCHAR endingChar = '~';
		m_numOfCharsRoot = GS::Utilities::Misc::getClosestSquareRoot(endingChar - m_startingChar + 1);

		m_biggest_w = 0;
		m_biggest_h = 0;
		
		for(size_t i = m_startingChar; i <= endingChar; ++i)
		{
			FT_Glyph glyph;
 
			// Locate the index of the character in the font face.
			uint32_t index = FT_Get_Char_Index(m_face, i);
			if(index == 0) continue;
 
			// Load the glyph into the font face.
			FT_Load_Glyph(m_face, index, FT_LOAD_RENDER); // RENDER ????
 
			// Render the glyph as a mono-chrome bitmap.
			FT_Render_Glyph(m_face->glyph, FT_RENDER_MODE_NORMAL);
 
			// Put the glyph in the glyph slot into an actual glpyh struct.
			FT_Get_Glyph(m_face->glyph, &glyph);
 
			// Small shortcuts
			FT_GlyphSlot slot = m_face->glyph;
			FT_Bitmap& bitmap = slot->bitmap;
 
			// Bitmap dimensions
			uint32_t w = bitmap.width;
			uint32_t h = bitmap.rows;

			if( w > m_biggest_w )
				m_biggest_w = w;
			if( h > m_biggest_h )
				m_biggest_h = h;
		}

		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		// Load all printable characters.
		// If you visit an ASCII table (like www.asciitable.com) you will see
		// that the only valid values for printing are the space character all
		// the way up to the tilde (~).


		unsigned char* data = new unsigned char[m_biggest_w * m_biggest_h * m_numOfCharsRoot * m_numOfCharsRoot];
		memset(data, 0, m_biggest_w * m_biggest_h * m_numOfCharsRoot * m_numOfCharsRoot *sizeof(unsigned char));

		// Alignment for pixels needs to be at 1 byte.
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, m_biggest_w * m_numOfCharsRoot, m_biggest_h * m_numOfCharsRoot, 0, GL_RED, GL_UNSIGNED_BYTE, data);


		uint32_t w = 0;
		uint32_t h = 0;
		for(size_t i = m_startingChar; i <= endingChar; ++i)
		{
			size_t glyphNumCur = i - m_startingChar;

			FT_Glyph glyph;
 
			// Locate the index of the character in the font face.
			uint32_t index = FT_Get_Char_Index(m_face, i);
			//if(index == 0) continue;
 
			// Load the glyph into the font face.
			FT_Load_Glyph(m_face, index, FT_LOAD_RENDER); // RENDER ????
 
			// Render the glyph as a mono-chrome bitmap.
			FT_Render_Glyph(m_face->glyph, FT_RENDER_MODE_NORMAL);
 
			// Put the glyph in the glyph slot into an actual glpyh struct.
			FT_Get_Glyph(m_face->glyph, &glyph);
 
			// Small shortcuts
			FT_GlyphSlot slot = m_face->glyph;
			FT_Bitmap& bitmap = slot->bitmap;
 
			// Bitmap dimensions
			w = bitmap.width;
			h = bitmap.rows;

			// STORE THE NEEDED INFORMATION TO FIND THE DAMN TEXT
			m_glyphs[glyphNumCur].loc.x = glyphNumCur % m_numOfCharsRoot;
			m_glyphs[glyphNumCur].loc.y = glyphNumCur / m_numOfCharsRoot;
			m_glyphs[glyphNumCur].dim.x = SC(_USHORT, w);
			m_glyphs[glyphNumCur].dim.y = SC(_USHORT, h);
			m_glyphs[glyphNumCur].dim.z = SC(_USHORT, slot->advance.x >> 6);
			m_glyphs[glyphNumCur].dim.a = SC(_USHORT, slot->metrics.horiBearingY >> 6);
 
			size_t biggest_char = (m_biggest_h * m_biggest_w);
			memcpy(data + biggest_char * glyphNumCur, bitmap.buffer, sizeof(unsigned char) * w * h);

		int test = glGetError();
		if (test != GL_NO_ERROR)
			return -38989;

			glTexSubImage2D(GL_TEXTURE_2D, 0, m_biggest_w * (SC(int,glyphNumCur) % 10), m_biggest_h * (SC(int,glyphNumCur) / 10) , w, h, GL_RED, GL_UNSIGNED_BYTE, data + biggest_char * glyphNumCur); /// 0 is y //

		test = glGetError();
		if (test != GL_NO_ERROR)
			return -38989;
 
			FT_Done_Glyph(glyph);
		}

		/*
		uint32_t w = 0;
		uint32_t h = 0;
		for(size_t i = 'a'; i <= 'b'; ++i)
		{
			size_t glyphNumCur = i - ' ';

			FT_Glyph glyph;
 
			// Locate the index of the character in the font face.
			uint32_t index = FT_Get_Char_Index(m_face, i);
			//if(index == 0) continue;
 
			// Load the glyph into the font face.
			FT_Load_Glyph(m_face, index, FT_LOAD_RENDER); // RENDER ????
 
			// Render the glyph as a mono-chrome bitmap.
			FT_Render_Glyph(m_face->glyph, FT_RENDER_MODE_NORMAL);
 
			// Put the glyph in the glyph slot into an actual glpyh struct.
			FT_Get_Glyph(m_face->glyph, &glyph);
 
			// Small shortcuts
			FT_GlyphSlot slot = m_face->glyph;
			FT_Bitmap& bitmap = slot->bitmap;
 
			// Bitmap dimensions
			w = bitmap.width;
			h = bitmap.rows;

			data = new unsigned char[w * h];
			memset(data, 0, w * h * sizeof(unsigned char));

			// STORE THE NEEDED INFORMATION TO FIND THE DAMN TEXT
			//m_glyphs[glyphNumCur].glyphLoc.x = glyphNumCur % 10;
			//m_glyphs[glyphNumCur].glyphLoc.y = glyphNumCur / 10;
			//m_glyphs[glyphNumCur].glyphDim.x = SC(_USHORT, w);
			//m_glyphs[glyphNumCur].glyphDim.y = SC(_USHORT, h);
			//m_glyphs[glyphNumCur].glyphDim.z = SC(_USHORT, slot->advance.x >> 6);
			//m_glyphs[glyphNumCur].glyphDim.a = SC(_USHORT, slot->metrics.horiBearingY >> 6);
 
			memcpy(data, bitmap.buffer, sizeof(unsigned char) * w * h);
 
			FT_Done_Glyph(glyph);
		}
		*/

		/*
		// Alignment for pixels needs to be at 1 byte.
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, 0, GL_RED, tTexWidth, tTexHeight, GL_UNSIGNED_BYTE, data);

		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, data);
		// Restore default alignment value. I haven't actually tested this
		// part so it may or may not actually be the default.
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		*/

		_CheckForErrors();

		// Delete bitmap buffers
		delete[] data;

		// Restore default alignment value. I haven't actually tested this
		// part so it may or may not actually be the default.
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

		m_loaded = true;

		return 0;
	}


	Rect_t RenderText(const std::string& text, const Vector2_t& Pos)
	{
		_CheckForErrors();
		// VAO and buffers that will contain our text vertex data.
		uint32_t vao = 0, vbo = 0, ibo = 0;
		// Track total text size.
		Rect_t Size(Pos.x, Pos.y, 0, 0);
 
		if(!m_loaded /*|| !Font::s_loaded */|| text.empty()) return Size;
 
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
		//char c = text[i >> 2];
		_UCHAR c = text[i >> 2];

		// Handle new-lines by starting from the x position
		// again and increasing Y by the height of an arbitrary
		// large letter (here H).
		if(c == '\n')
		{
		last_w = Pos.x;
		y -= m_biggest_h;//mp_glyphTextures['H'].dim.y + mp_glyphTextures['H'].dim.h;
		}
 
		// We want to make sure the letters are in the range
		// that we've loaded (ASCII printables).
		_UCHAR actualLetter = (c > '~' || c < ' ') ? ' ' : c;
		_UCHAR letterIndex = actualLetter - m_startingChar;
		// Retrieve dimensions from the dictionary.
		// Since we're doing i += 4, the index in the text string
		// would be text[i / 4].
		// Rect_t Dim = mp_glyphTextures[letter].dim;
		Vec4D<_USHORT> cDim = m_glyphs[letterIndex].dim;
 
		float w = last_w;
		float h = cDim.y;
		last_w = w + cDim.z; // Increase until next char by the
		// bitmap's horizontal advance value.
 
		//- cDim.a

		// [i] : top left
		// [i + 1] : top right
		// [i + 2] : bottom right
		// [i + 3] : bottom left
		verts[i].Position = Vector2_t(w / 800.0f, (y + h - (h - cDim.a)) / 600.0f);
		verts[i+1].Position = Vector2_t(last_w  / 800.0f, (y + h - (h - cDim.a) ) / 600.0f);
		verts[i+2].Position = Vector2_t(last_w  / 800.0f, (y - (h - cDim.a)) / 600.0f);
		verts[i+3].Position = Vector2_t(w  / 800.0f, (y - (h - cDim.a)) / 600.0f);


		//verts[i].Position = Vector2_t(w / 800.0f, (y + h) / 600.0f);
		//verts[i+1].Position = Vector2_t(last_w  / 800.0f, (y + h ) / 600.0f);
		//verts[i+2].Position = Vector2_t(last_w  / 800.0f, (y) / 600.0f);
		//verts[i+3].Position = Vector2_t(w  / 800.0f, (y) / 600.0f);

		// Load up the bitmap texture coordinates moving counter-clockwise
		// from the origin.

		// The relative width OR height of any given character on the texture
		float singleCharDim = 1.0f / SC(float, m_numOfCharsRoot);

		int numCharsRootI = SC(int, m_numOfCharsRoot);
		int charIndex = letterIndex;

		{
		float x = SC(float,( charIndex % numCharsRootI )) * singleCharDim; // x
		float y = SC(float,( charIndex / numCharsRootI )) * singleCharDim; // y

		float thisCharWidth = singleCharDim * (SC(float, cDim.x) / SC(float, m_biggest_w));
		float thisCharHeight = singleCharDim * (SC(float, h) / SC(float, m_biggest_h));

		//verts[i+2].TexCoord = Vector2_t(x, y);
		//verts[i+3].TexCoord = Vector2_t(x + thisCharWidth, y);
		//verts[i+0].TexCoord = Vector2_t(x + thisCharWidth, y + thisCharHeight);
		//verts[i+1].TexCoord = Vector2_t(x, y + thisCharHeight);

		verts[i+0].TexCoord = Vector2_t(x, y);
		verts[i+1].TexCoord = Vector2_t(x + thisCharWidth, y);
		verts[i+2].TexCoord = Vector2_t(x + thisCharWidth, y + thisCharHeight);
		verts[i+3].TexCoord = Vector2_t(x, y + thisCharHeight);

		//// EVERYTHING
		//verts[i].TexCoord = Vector2_t(0, 0);
		//verts[i+1].TexCoord = Vector2_t(1, 0);
		//verts[i+2].TexCoord = Vector2_t(1, 1);
		//verts[i+3].TexCoord = Vector2_t(0, 1);
		}
 
		// The vertices all use the font color.
		// See CFont::SetColor()
		for(size_t j = i; j < i + 4; ++j)
		verts[j].Color = m_color;
 
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
		max_w += cDim.x;
		max_h = (max_h > cDim.a + h) ? max_h : cDim.a + h;
		}
 
		// Tally up dimensions.
		Size.w = max_w;
		Size.h = max_h;

		_CheckForErrors();

		// Enable font-rendering shader.
		//m_FontRender.Bind();
		// Create GPU buffers for vertex/index data
		glGenVertexArrays(1, &vao);
		//glGenBuffers(1, &vao);
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

		_CheckForErrors();
 
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

		_CheckForErrors();
 
		// Draw each character with its texture enabled.
		for(size_t i = 0; i < text.length(); ++i)
		{
			// Make invalid characters just spaces (' ')
			//char c = (text[i] > '~' || text[i] < ' ') ? ' ' : text[i];
			//glBindTexture(GL_TEXTURE_2D, m_texture);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT,
			(void*)(sizeof(uint16_t) * i * 6));
		}

		_CheckForErrors();

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
		//m_FontRender.Unbind();
		// Delete all buffers.
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ibo);

		_CheckForErrors();
 
		// Delete old buffers in RAM.
		delete[] verts;
		delete[] inds;
		// Give back the total dimensions of the text rendered.
		return Size;
	}

};

#if 0
class Font
{
public:
	Font();
	~Font();

	/**
	* Initializes the FreeType library.
	* This should be called prior to ANY other font operations.
	* Since it is static, no instance of CFont needs to be present,
	* simply do:
	* if(!CFont::Initialize())
	* std::cerr << "FreeType 2 failed to initialize!\n";
	*
	* @return TRUE on success, FALSE on failure.
	**/
	static bool Initialize();
 
	/**
	* Loads a TrueType font.
	* Here, all of the printable characters in the ASCII table
	* are loaded as bitmaps, then are turned into renderable
	* textures in GPU memory. Their dimensions are stored for
	* rendering later on.
	*
	* @param std::string Font filename
	* @param uint16_t Font size (optional=12)
	*
	* @pre CFont::Initialize() must have been called.
	*
	* @return TRUE if everything went smoothly,
	* FALSE otherwise.
	**/
	bool LoadFromFile(const std::string& filename,
	const uint16_t size = 12);
 
	/**
	* Resizes the font.
	* This stores a new font size and calls LoadFromFile()
	* again, regenerating new bitmaps and textures for all
	* characters.
	* Since this can be a relatively expensive operation,
	* it should be used sparingly. If you think you're going
	* to be resizing a font often, consider caching multiple
	* instances of CFont.
	*
	* @param uint16_t New font size
	*
	* @return Value of CFont::LoadFromFile()
	**/
	bool Resize(const uint32_t size);
 
	/**
	* Renders text on the current framebuffer.
	* Given a string, this function will render it at
	* the given position. A VBO will be created, vertex
	* information generated, and then each character will
	* be rendered using its texture.
	* The position parameter marks the bottom of the "line"
	* to be drawn on, so parts of characters such as 'j'
	* or 'q' will fall below the line. Think of a sheet of
	* paper.
	* A rectangle is returned, in case it is useful to know
	* the overall dimensions of the text rendered.
	*
	* @param std::string Text to render
	* @param math::vector2_t Position to start rendering
	*
	* @return Rectangle representing rendered text dimensions.
	*
	* @see GetTextWidth()
	* @see GetTextHeight()
	**/
	Rect_t RenderText(const std::string& text,
	const Vector2_t& Pos);
 
	/**
	* Sets text color; the default is white.
	**/
	void SetFontColor(const float r, const float g, const float b);

#ifdef TEST_ENABLED
public:
#else
private:
#endif

	static FT_Library s_Library;
	static bool s_loaded;
 
	// Glyph representing data for each character.
	struct Glyph
	{
		// OpenGL texture handle for the bitmap
		uint32_t texture;
		// Dimensions and offsets.
		Rect_t dim;
	};
 
	// {Char: Glyph} dictionary.
	std::map<char, Glyph> mp_glyphTextures;
 
	FT_Face m_FontFace;
	Shader m_FontRender;
 
	Color4f_t m_Color;
	std::string m_filename;
	uint16_t m_size;
	bool m_loaded, m_ready; 

};

#endif


};
};

#endif
