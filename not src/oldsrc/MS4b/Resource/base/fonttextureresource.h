#ifndef __FONTTEXTURERESOURCE_H_
#define __FONTTEXTURERESOURCE_H_

#include "resourcefile.h"
#include <Graphics\openglincludes.h>

namespace GS { class Game;
namespace ResourceNS {

	class FontTextureResource : public IResourceFile
	{
	public:
		FontTextureResource(): m_mipMapsGenerated(false){}
		~FontTextureResource(){}
		_UINT32 init(GS::Game * a_rpGame, const char * a_filename, const bool & a_generateMipMaps);
		void shutdown();

		void createFromData(_BYTE* bData, int a_iWidth, int a_iHeight, int a_iBPP, GLenum format, bool bGenerateMipMaps);
		_UINT32	loadFromFile(const char * a_filename, bool a_generateMipMaps = false);

		void bindTexture(_UINT32 a_textureUnit = 0);
		void setFiltering(_INT32 a_tfMagnification, _INT32 a_tfMinification);
		void setSamplerParameter(GLenum a_parameter, GLenum a_value);

		GET_ACCESSOR(_UINT32, m_width);
		GET_ACCESSOR(_UINT32, m_height);

		GET_ACCESSOR(_UINT32, m_glTexture);

	private:

		GS::Game *			m_rpGame;

		_INT32				m_width, 
							m_height, 
							m_bytesPerPixel;
		_UINT32				m_glTexture;
		_UINT32				m_glSampler;
		bool				m_mipMapsGenerated;

		_INT32				m_tfMinification, 
							m_tfMaxification;

		char *				m_filename;
		_BYTE *				m_keyName; /// KYLE :: WHAT??????
	};

};
};

#endif