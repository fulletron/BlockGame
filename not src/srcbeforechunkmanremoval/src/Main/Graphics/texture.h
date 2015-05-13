#ifndef __TEXTURE_H_
#define __TEXTURE_H_

#include <Graphics/resource.h>

namespace GS {
namespace Graphics {

class TextureResource : public Resource {

selective:
	_UINT32 m_texture;
	_BOOL m_inited;

public:
	TextureResource();
	~TextureResource();

	_INT32 init(  );

	_INT32 loadFile( const std::string & a_filename );

	void shutdown();
	_UINT32 getTexture(){return m_texture;}

selective:

};

};
};

#endif
