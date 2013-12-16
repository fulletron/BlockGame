#include "font.h"

namespace GS {
namespace Graphics {

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