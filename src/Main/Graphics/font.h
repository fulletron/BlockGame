#ifndef __FONT_H_
#define __FONT_H_

#include <Utilities/utilities.h>
#include <Graphics/resource.h>

// MORE HELP ON THE WEB
// http://www.freetype.org/freetype2/docs/tutorial/step1.html

#include "fonthelpers.h"

namespace GS {
namespace Graphics {

class FontResource : public Resource {

public:
	struct GlyphInAtlas
	{
		_SHORT width;
		_SHORT height;
		_SHORT horizBearingX;
		_SHORT horizBearingY;
		_SHORT advanceX;
	};

	// TEMPORARILY PUBLIC FOR EASE OF DEV
	// gl texture of the font atlas
	_UINT32						m_texture;

selective:
	// Create GPU buffers for vertex/index data
	_UINT32 m_vao,
		m_vbo,
		m_ibo;

	// The library for freetype operations.
	// STATIC: Only one needs to exist ever.
	static FT_Library			m_library;
	static _BOOL				m_libraryLoaded;

	// Is this font loaded?
	_BOOL						m_loaded;
	// Handle to the entire character set
	// This is specific to each .otf or .ttf
	FT_Face						m_face;

	// HOW MANY GLYPHS? KYLE ::
	GlyphInAtlas				m_glyphs[128];

	// Biggest Width of loaded font in pixels
	_UINT32						m_biggest_w,
	// Biggest Height of loaded font in pixels
								m_biggest_h;

	_UCHAR						m_startingChar;
	_UCHAR						m_numOfCharsRoot;

public:
	FontResource();
	~FontResource();

	/**
	* Initializes the FreeType library.
	* If the library has not been loaded,
	* this function is automatically called
	* in loadFile(). It is also static,
	* so it can be called without an instance
	* of the Font class.
	*
	* @return 0 on success, 
	* @return ERROR_NUMBER on failure.
	**/
	static _INT32 initializeLibrary();

	/**
	* Loads a TTF or OTF into this instance.
	* It stores all the relevant information (dimensions,
	* glyph metrics, etc) in this class, as well as turns
	* the bitmaps into renderable textures is GPU memory.
	*
	* @param const char * a_fontFile
	*	full path of the file (with filename)
	* @param const int a_size: 
	*	initial size in pixels (detail)
	*
	* @return 0 // SUCCESS!,
	* @return ERROR_NUMBER // FAILURE!
	**/
	_INT32 loadFile( const char * a_fontFile, const int a_size = 16);


	/**
	* Renders text to the current framebuffer.
	* This function does not bind it's texture.
	* 
	*
	* @param const std::string & a_text
	*	Text to Render!
	* @param const Vector2_t & a_pos
	*	Position to render (in pixels!)
	* @param const Color4f_t & a_color
	*	Color of the text
	*
	* @return 0 // SUCCESS!,
	* @return ERROR_NUMBER // FAILURE!
	*
	* @ TODO :: return the final coords (for Carat)
	**/
	_INT32 renderText(	const std::string & a_text, 
						const Vector2_t & a_pos, 
						const Color4f_t & a_color 
							= Color4f_t(1.0f, 1.0f, 1.0f, 1.0f));

	/**
	* Get the tallest character height in pixels
	*/
	_UINT32 getHeight() { return m_biggest_h; }

	/**
	* Destroys the font instance.
	* Standardly, it doesn't call
	* destroyLibrary, but can.
	**/
	void shutdown(bool a_killLib = false);

	/**
	* Destroys the FreeType library.
	**/
	static void destroyLibrary();
};


};
};

#endif
