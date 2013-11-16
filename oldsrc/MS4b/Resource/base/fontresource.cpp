#include "fontresource.h"
#include "shaderprogramresource.h"
#include <Graphics\openglincludes.h>
#include <Game\game.h>

namespace GS {
namespace ResourceNS {

	inline int __next_p2(int n){int res = 1; while(res < n)res <<= 1; return res;}

	void FontResource::__createChar(int iIndex)
	{
		FT_Load_Glyph(m_ftFace, FT_Get_Char_Index(m_ftFace, iIndex), FT_LOAD_DEFAULT);

		FT_Render_Glyph(m_ftFace->glyph, FT_RENDER_MODE_NORMAL);
		FT_Bitmap* pBitmap = &m_ftFace->glyph->bitmap;

		int iW = pBitmap->width, iH = pBitmap->rows;
		int iTW = __next_p2(iW), iTH = __next_p2(iH);

		GLubyte* bData = new GLubyte[iTW*iTH];
		// Copy glyph data and add dark pixels elsewhere
		for(int ch = 0; ch < iTH; ++ch)
			for(int cw = 0; cw < iTW; ++cw)
				bData[ch*iTW+cw] = (ch >= iH || cw >= iW) ? 0 : pBitmap->buffer[(iH-ch-1)*iW+cw];
 
		// And create a texture from it
		//m_tCharTextures[iIndex].createFromData(bData, iTW, iTH, 8, GL_R8, false);
		m_tCharTextures[iIndex].createFromData(bData, iTW, iTH, 8, GL_DEPTH_COMPONENT, false);
		m_tCharTextures[iIndex].setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR);

		m_tCharTextures[iIndex].setSamplerParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		m_tCharTextures[iIndex].setSamplerParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Calculate glyph data
		m_advX[iIndex] = m_ftFace->glyph->advance.x>>6;
		m_bearingX[iIndex] = m_ftFace->glyph->metrics.horiBearingX>>6;
		m_charWidth[iIndex] = m_ftFace->glyph->metrics.width>>6;

		m_advY[iIndex] = (m_ftFace->glyph->metrics.height - m_ftFace->glyph->metrics.horiBearingY)>>6;
		m_bearingY[iIndex] = m_ftFace->glyph->metrics.horiBearingY>>6;
		m_charHeight[iIndex] = m_ftFace->glyph->metrics.height>>6;

		m_newLine = glm::max(m_newLine, int(m_ftFace->glyph->metrics.height>>6));

		// Rendering data, texture coordinates are always the same, so now we waste a little memory
		glm::vec2 vQuad[] =
		{
			glm::vec2(0.0f, float(-m_advY[iIndex]+iTH)),
			glm::vec2(0.0f, float(-m_advY[iIndex])),
			glm::vec2(float(iTW), float(-m_advY[iIndex]+iTH)),
			glm::vec2(float(iTW), float(-m_advY[iIndex]))
		};
		glm::vec2 vTexQuad[] = {glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f)};

		// Add this char to VBO
		for(int i = 0; i < 4; ++i)
		{
			m_vboData.addData(&vQuad[i], sizeof(glm::vec2));
			m_vboData.addData(&vTexQuad[i], sizeof(glm::vec2));
		}
		delete[] bData;
	}

	/*-----------------------------------------------

	Name:	loadFont

	Params:	sFile - path to font file
			iPXSize - desired font pixel size

	Result:	Loads whole font.

	/*---------------------------------------------*/

	_UINT32 FontResource::init(GS::Game * const a_rpGame, const char * a_filename, int a_pxSize, GS::LibraryNS::EntryInitFunction a_spResInitFunc)
	{
		m_rpGame = a_rpGame;
		bool success = __loadFont(a_filename, a_pxSize);
		m_pShaderProgram = (GS::ResourceNS::ShaderProgramResource *)a_spResInitFunc(a_rpGame);
		return 0;
	}

	bool FontResource::__loadFont(const char * sFile, int iPXSize)
	{
		FT_Error t_ftError = 0;
		t_ftError = FT_Init_FreeType(&m_ftLib);
		if(t_ftError)
			return false;
		
		t_ftError = FT_New_Face(m_ftLib, sFile, 0, &m_ftFace);
		if(t_ftError)
			return false;

		FT_Set_Pixel_Sizes(m_ftFace, iPXSize, iPXSize);
		m_loadedPixelSize = iPXSize;

		glGenVertexArrays(1, &m_vaoId);
		glBindVertexArray(m_vaoId);
		m_vboData.__createVBO();
		m_vboData.bindVBO();

		for(int i = 0; i < 128; ++i)
			__createChar(i);

		FT_Done_Face(m_ftFace);
		FT_Done_FreeType(m_ftLib);
	
		m_vboData.uploadDataToGPU(GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2)*2, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2)*2, (void*)(sizeof(glm::vec2)));
		return true;
	}

	/*-----------------------------------------------

	Name:	loadSystemFont

	Params:	sName - system font name
	iPXSize - desired font pixel size

	Result:	Loads system font (from system Fonts
			directory).

	/*---------------------------------------------*/

	/*
	bool FontResource::loadSystemFont(const char * sName, int iPXSize)
	{
		char buf[512]; GetWindowsDirectory(buf, 512);
		string sPath = buf;
		sPath += "\\Fonts\\";
		sPath += sName;

		return loadFont(sPath, iPXSize);
	}
	*/

	/*-----------------------------------------------

	Name:	print

	Params:	sText - text to print
			x, y - 2D position
			iPXSize - printed text size

	Result:	Prints text at specified position
			with specified pixel size.

	/*---------------------------------------------*/

	void FontResource::print(const std::string & sText, int x, int y, int iPXSize)
	{
		glBindVertexArray(m_vaoId);
		m_pShaderProgram->setUniform("gSampler", 0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		int iCurX = x, iCurY = y;
		if(iPXSize == -1)
			iPXSize = m_loadedPixelSize;
		float fScale = float(iPXSize)/float(m_loadedPixelSize);
		for(int i = 0; i < (int)sText.size(); ++i)
		{
			if(sText[i] == '\n')
			{
				iCurX = x;
				iCurY -= m_newLine*(int)fScale;
				continue;
			}
			int iIndex = int(sText[i]);
			iCurX += m_bearingX[iIndex]*iPXSize/m_loadedPixelSize;
			if(sText[i] != ' ')
			{
				m_tCharTextures[iIndex].bindTexture();
				glm::mat4 mModelView = glm::translate(glm::mat4(1.0f), glm::vec3(float(iCurX), float(iCurY), 0.0f));
				mModelView = glm::scale(mModelView, glm::vec3(fScale));
				m_pShaderProgram->setUniform("modelViewMatrix", mModelView);
				// Draw character
				glDrawArrays(GL_TRIANGLE_STRIP, iIndex*4, 4);
			}

			iCurX += (m_advX[iIndex]-m_bearingX[iIndex])*iPXSize/m_loadedPixelSize;
		}
		glDisable(GL_BLEND);
	}

	void FontResource::print(const _GSVECTOR(_BYTE) & sText, int x, int y, int iPXSize)
	{
		glBindVertexArray(m_vaoId);
		m_pShaderProgram->setUniform("gSampler", 0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		int iCurX = x, iCurY = y;
		if(iPXSize == -1)
			iPXSize = m_loadedPixelSize;
		float fScale = float(iPXSize)/float(m_loadedPixelSize);
		for(int i = 0; i < sText.size(); ++i)
		{
			if(sText.get(i) == '\n')
			{
				iCurX = x;
				iCurY -= m_newLine*iPXSize/m_loadedPixelSize;
				continue;
			}
			int iIndex = int(sText.get(i));
			iCurX += m_bearingX[iIndex]*iPXSize/m_loadedPixelSize;
			if(sText.get(i) != ' ')
			{
				m_tCharTextures[iIndex].bindTexture();
				glm::mat4 mModelView = glm::translate(glm::mat4(1.0f), glm::vec3(float(iCurX), float(iCurY), 0.0f));
				mModelView = glm::scale(mModelView, glm::vec3(fScale));
				m_pShaderProgram->setUniform("modelViewMatrix", mModelView);
				// Draw character
				glDrawArrays(GL_TRIANGLE_STRIP, iIndex*4, 4);
			}

			iCurX += (m_advX[iIndex]-m_bearingX[iIndex])*iPXSize/m_loadedPixelSize;
		}
		glDisable(GL_BLEND);
	}

	void FontResource::shutdown()
	{
		for(int i = 0; i < 128; ++i)
			m_tCharTextures[i].shutdown();
		m_vboData.shutdown();
		glDeleteVertexArrays(1, &m_vaoId);
	}

	int FontResource::getStringWidthPx(const std::string & a_string, const int & a_pxSize)
	{
		//glBindVertexArray(m_vaoId);
		//m_pShaderProgram->setUniform("gSampler", 0);
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		int iCurX = 0;
		//if(iPXSize == -1)
		int iPXSize = a_pxSize;
		float fScale = float(iPXSize)/float(m_loadedPixelSize);
		for(int i = 0; i < (int)a_string.size(); ++i)
		{
			if(a_string[i] == '\n')
			{
				continue;
			}
			int iIndex = int(a_string[i]);
			iCurX += m_advX[iIndex]*iPXSize/m_loadedPixelSize;
			//iCurX += m_bearingX[iIndex]*iPXSize/m_loadedPixelSize;
			/*
			if(a_string[i] != ' ')
			{
				m_tCharTextures[iIndex].bindTexture();
				glm::mat4 mModelView = glm::translate(glm::mat4(1.0f), glm::vec3(float(iCurX), float(iCurY), 0.0f));
				mModelView = glm::scale(mModelView, glm::vec3(fScale));
				m_pShaderProgram->setUniform("modelViewMatrix", mModelView);
				// Draw character
				glDrawArrays(GL_TRIANGLE_STRIP, iIndex*4, 4);
			}
			*/
			//iCurX += (m_advX[iIndex]-m_bearingX[iIndex])*iPXSize/m_loadedPixelSize;
		}
		//glDisable(GL_BLEND);

		return iCurX;
	}

};
};