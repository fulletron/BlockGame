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
		Vec4D<_USHORT> glyphDim;
		Vec2D<_UCHAR> glyphLoc;

		GlyphInAtlas(){}
	};

	FT_Library	m_library;
	FT_Face		m_face;

	uint32_t	m_texture;

	GlyphInAtlas m_glyphs[100];

	Font(){}
	~Font(){}

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
						16*64, /* char_height in 1/64th of points */ 
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


		uint32_t biggest_w = 0;
		uint32_t biggest_h = 0;
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

			if( w > biggest_w )
				biggest_w = w;
			if( h > biggest_h )
				biggest_h = h;
		}

		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		int tTexWidth = biggest_w * 10;
		int tTexHeight = biggest_h * 10;

		// create data ptr to hold every letter (needs to be 100 chars
		unsigned char* data = new unsigned char[biggest_w * biggest_h * 100];
		memset(data, NULL, tTexWidth * tTexHeight * sizeof(unsigned char));

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
 
			memcpy(data + (glyphNumCur * biggest_w + ((glyphNumCur / 10) % biggest_h)), bitmap.buffer, sizeof(unsigned char) * w * h);
 
			FT_Done_Glyph(glyph);
		}

		// Alignment for pixels needs to be at 1 byte.
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, 0, GL_RED, tTexWidth, tTexHeight,
		GL_UNSIGNED_BYTE, data);
		// Restore default alignment value. I haven't actually tested this
		// part so it may or may not actually be the default.
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

		// Delete bitmap buffers
		delete[] data;

		

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

		return 0;
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