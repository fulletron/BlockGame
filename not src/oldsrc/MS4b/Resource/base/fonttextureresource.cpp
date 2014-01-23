#include "fontTextureResource.h"

namespace GS {
namespace ResourceNS {

	_UINT32 FontTextureResource::init(GS::Game * a_rpGame, const char * a_filename, const bool & a_generateMipMaps)
	{
		m_rpGame = a_rpGame;

		if(a_filename)
			return loadFromFile(a_filename, a_generateMipMaps);

		return 0;
	}

	_UINT32 FontTextureResource::loadFromFile(const char * a_filename, bool a_generateMipMaps)
	{
		glGenTextures(1, &m_glTexture);
		glBindTexture(GL_TEXTURE_2D, m_glTexture);

		_BYTE * t_pImage = 0;
		t_pImage = SOIL_load_image(a_filename, &m_width, &m_height, 0, SOIL_LOAD_RGB);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, t_pImage);

		if(a_generateMipMaps)
			glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(t_pImage);

		m_filename = (char *)a_filename;
		m_mipMapsGenerated = a_generateMipMaps;

		return 0;
	}

	void FontTextureResource::bindTexture(_UINT32 a_textureUnit)
	{
		glActiveTexture(GL_TEXTURE0 + a_textureUnit);
		glBindTexture(GL_TEXTURE_2D, m_glTexture);
		glBindSampler(a_textureUnit, m_glSampler);
	}

	void FontTextureResource::setFiltering(_INT32 a_tfMagnification, _INT32 a_tfMinification)
	{
		if(a_tfMagnification == TEXTURE_FILTER_MAG_NEAREST)
			glSamplerParameteri(m_glSampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		else if(a_tfMagnification == TEXTURE_FILTER_MAG_BILINEAR)
			glSamplerParameteri(m_glSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if(a_tfMinification == TEXTURE_FILTER_MIN_NEAREST)
			glSamplerParameteri(m_glSampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		else if(a_tfMinification == TEXTURE_FILTER_MIN_BILINEAR)
			glSamplerParameteri(m_glSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		else if(a_tfMinification == TEXTURE_FILTER_MIN_NEAREST_MIPMAP)
			glSamplerParameteri(m_glSampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		else if(a_tfMinification == TEXTURE_FILTER_MIN_BILINEAR_MIPMAP)
			glSamplerParameteri(m_glSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		else if(a_tfMinification == TEXTURE_FILTER_MIN_TRILINEAR)
			glSamplerParameteri(m_glSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}

	void FontTextureResource::setSamplerParameter(GLenum a_parameter, GLenum a_value)
	{
		glSamplerParameteri(m_glSampler, a_parameter, a_value);
	}

	void FontTextureResource::shutdown()
	{
		glDeleteSamplers(1, &m_glSampler);
		glDeleteTextures(1, &m_glTexture);
	}

	void FontTextureResource::createFromData(_BYTE* bData, int a_iWidth, int a_iHeight, int a_iBPP, GLenum format, bool bGenerateMipMaps)
	{
		// Generate an OpenGL texture ID for this texture
		glGenTextures(1, &m_glTexture);
		glBindTexture(GL_TEXTURE_2D, m_glTexture);

		if(format == GL_RGB || format == GL_BGR) // We must handle this because of internal format parameter
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, a_iWidth, a_iHeight, 0, format, GL_UNSIGNED_BYTE, bData);
			if(bGenerateMipMaps)glGenerateMipmap(GL_TEXTURE_2D);
		}
		//else if (format == GL_RGBA)
		//{
		//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, a_iWidth, a_iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bData);
		//	if(bGenerateMipMaps)glGenerateMipmap(GL_TEXTURE_2D);
		//}
		else if(format == GL_R8)
		{
			//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			//glTexImage2D(GL_TEXTURE_2D, 0, format, a_iWidth, a_iHeight, 0, format, GL_UNSIGNED_BYTE, bData);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, a_iWidth, a_iHeight, 0, GL_RED, GL_UNSIGNED_BYTE, bData);
			if(bGenerateMipMaps)glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, format, a_iWidth, a_iHeight, 0, format, GL_UNSIGNED_BYTE, bData);
			if(bGenerateMipMaps)glGenerateMipmap(GL_TEXTURE_2D);
		}

		glGenSamplers(1, &m_glSampler);

		m_filename = "";
		m_mipMapsGenerated = bGenerateMipMaps;
		m_width = a_iWidth;
		m_height = a_iHeight;
		m_bytesPerPixel = a_iBPP;
	}

};
};