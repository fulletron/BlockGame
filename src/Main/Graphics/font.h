#ifndef __FONT_H_
#define __FONT_H_

#include <Utilities/utilities.h>
#include <Graphics/openglincludes.h>
#include "graphics.h"

// MORE HELP ON THE WEB
// http://www.freetype.org/freetype2/docs/tutorial/step1.html

#include "fonthelpers.h"

namespace GS {
namespace Graphics {

class Font {

public:
	class GlyphInAtlas
	{
	public:
		_SHORT width;
		_SHORT height;
		_SHORT horizBearingX;
		_SHORT horizBearingY;
		_SHORT advanceX;

		GlyphInAtlas(){}
		~GlyphInAtlas(){}
	};

#ifdef TEST_ENABLED
public:
#else
protected:
#endif

	// KYLE ::
	// TODO ::
	// The library for freetype operations.
	// Only one needs to exist ever.
	static FT_Library			m_library;
	static _BOOL				m_libraryLoaded;

	// Is this font loaded?
	_BOOL						m_loaded;
	// Handle to the entire character set
	// This is specific to each .otf or .ttf
	FT_Face						m_face;

	// HOW MANY GLYPHS? KYLE ::
	GlyphInAtlas				m_glyphs[256];

	_UINT32						m_biggest_w,
								m_biggest_h;


	_UCHAR						m_startingChar;
	_UCHAR						m_numOfCharsRoot;

public:
	// TEMPORARILY PUBLIC FOR EASE OF DEV

	// gl texture of the font atlas
	_UINT32						m_texture;

	Font(){m_libraryLoaded = false; m_loaded = false;}
	~Font(){}

	static _INT32 initializeLibrary();
	_INT32 loadFile( const char * a_fontFile, const int a_size = 16);
	_INT32 renderText(	const std::string & a_text, 
						const Vector2_t & a_pos, 
						const Color4f_t & a_color 
							= Color4f_t(1.0f, 1.0f, 1.0f, 1.0f));
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
