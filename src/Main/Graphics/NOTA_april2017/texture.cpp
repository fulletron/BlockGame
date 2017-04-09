#include "texture.h"
#include <Utilities/glfwerrorfunc.h>

#include <Graphics/openglincludes.h>

namespace GS {
namespace Graphics {

TextureResource::TextureResource()
: Resource(), m_texture(0), m_inited(false)
{}

TextureResource::~TextureResource()
{}

_INT32 TextureResource::init(  )
{
	if( m_inited )
		return -1;
	m_inited = true;
	return 0;
}

_INT32 TextureResource::loadFile( const std::string & a_filename )
{
	if ( _CheckForErrors() )
		return -1;
	glGenTextures(1, &m_texture);

	int width, height;
	unsigned char* image;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture );
	image = SOIL_load_image( a_filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	unsigned char* imageFalse = new unsigned char[width * height];
	for (int i = 0; i < width * height; ++i)
		imageFalse[i] = '0';
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, imageFalse);// image);
	SOIL_free_image_data(image);

	if ( _CheckForErrors() )
		return -1;
	return 0;
}

void TextureResource::shutdown()
{
	
}

};
};
