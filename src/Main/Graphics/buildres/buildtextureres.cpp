#include <Graphics/reslib.h>

#include <Utilities/glfwerrorfunc.h>
namespace GS {
namespace Graphics {

TextureResource * ResourceLibrary::__buildTextureRes( const _UINT64 a_name )
{
	TextureResource * newRes = new TextureResource();
	std::string filename = "";
	std::string src_textures = "Internal/Resources/Textures/";
	
	switch(a_name)
	{
	case CV8::RES_TEX_PANEBKG:
	filename = ( _FS::getCurrentFullPath()
	.append(src_textures)
	.append("smallpanelbacking.png").c_str());
	break;
	case CV8::RES_TEX_FADEBAR:
	filename = (_FS::getCurrentFullPath()
	.append(src_textures)
	.append("gradiantfadebar.png").c_str());
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

	newRes->loadFile( filename );
	newRes->assignName( a_name );
	newRes->assignType( ResourceLibrary::TEXTURE );
	newRes->addCount();
	m_pTextureResources.push_back( newRes );
	return newRes;
}

};
};

