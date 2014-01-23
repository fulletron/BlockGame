#ifndef __FONTRESOURCE_H_
#define __FONTRESOURCE_H_

#include "resourcefile.h"
#include "fonttextureresource.h"
#include "vertexbufferobjectresource.h"

namespace GS {
namespace ResourceNS {

	class ShaderProgramResource;

	class FontResource : public IResourceFile
	{
	private:
		void __createChar(int iIndex);
		bool __loadFont(const char * sFile, int iPXSize);

	public:
		FontResource(){}
		~FontResource(){}

		_UINT32 init(GS::Game * const a_rpGame, const char * a_filename, int a_pxSize, GS::LibraryNS::EntryInitFunction a_spResInitFunc);
		void shutdown();

		void print(const std::string & sText, int x, int y, int iPXSize);
		void print(const _GSVECTOR(_BYTE) & sText, int x, int y, int iPXSize);
		void draw2D(); // TODO: THIS WILL TAKE IN SOME SPECIFIC PARAMS AND DRAW CORRECTLY!

		int getStringWidthPx(const std::string & a_string, const int & a_pxSize);

		GETRP_ACCESSOR(ShaderProgramResource, m_pShaderProgram);

	private:
		GS::Game * m_rpGame;

		/// LOCALLY STORED RESOURCES (THESE MUST BE DELETED UPON SHUTDOWN)
		FontTextureResource				m_tCharTextures[256];
		VertexBufferObjectResource		m_vboData;

		/// REFERENCED RESOURCES (THESE MUST BE SUBTRACTED UPON SHUTDOWN)
		ShaderProgramResource *			m_pShaderProgram;

		/// OTHER
		FT_Library m_ftLib;
		FT_Face m_ftFace;
		int m_advX[256], m_advY[256];
		int m_bearingX[256], m_bearingY[256];
		int m_charWidth[256], m_charHeight[256];
		int m_loadedPixelSize, m_newLine;
		_UINT32 m_vaoId;
	};

};
};

#endif