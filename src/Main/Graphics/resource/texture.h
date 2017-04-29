#ifndef __TEXTURE_H_
#define __TEXTURE_H_

#include "iresource.h"

namespace GS {
namespace Resource {

class TextureResource : public IResource 
{
	IMPLEMENT_IRESOURCE;

selective:
	_UINT32 m_texture;

public:
	TextureResource();
	~TextureResource();

	_INT32 loadFile( const std::string & a_filename );

	_UINT32 init();
	_UINT32 shutdown();
	_UINT32 getTexture(){return m_texture;}

};

};
};

#endif
