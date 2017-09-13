#include "../library/library.h"
#include "../resource/texture.h"
#include "Utilities/filepath/filepath.h"

#include "Utilities/definitions_values.h"

namespace GS {
namespace Library {

GS::Resource::TextureResource * Library::__buildTextureResource( const _UINT64 a_name )
{
	GS::Resource::TextureResource * newRes = new GS::Resource::TextureResource();
	std::string filename = "";
	std::string src_textures = "/Internal/Resources/Textures/";
	std::string src_file = FILEPATH.getAbsoluteFilePath_str();
	src_file.append(src_textures);
	filename.append(src_file);
	
	switch(a_name)
	{
	case CV8::RES_TEX_PANEBKG:
	filename.append("smallpanelbacking.png");
	break;
	case CV8::RES_TEX_FADEBAR:
	filename.append("gradiantfadein.png");
	break;
	default: return 0;
	}

	/* Boost
	switch(a_name)
	{
	case CV8::RES_TEX_PANEBKG:
		filename = ( _FS::getCurrentFullPath() 
		/ "Internal/" / "Resources/" / "Textures/" 
		/ "smallpanelbacking.png").string().c_str();
		break;
	case CV8::RES_TEX_FADEBAR:
		filename = ( _FS::getCurrentFullPath() 
		/ "Internal/" / "Resources/" / "Textures/" 
		/ "gradiantfadebar.png").string().c_str();
		break;
	default: return 0; 
	}
	*/

	newRes->init(a_name);
	newRes->loadFile( filename );
	newRes->addCount();
	m_textureResources.push_back( newRes );
	return newRes;
}

};
};

