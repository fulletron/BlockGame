#include <Graphics/reslib.h>

#include <Utilities/glfwerrorfunc.h>
namespace GS {
namespace Graphics {

TextureResource * ResourceLibrary::__buildTextureRes( const _INT64 a_name )
{
	TextureResource * newRes = new TextureResource();
	std::string filename = "";
	
	switch(a_name)
	{
	case CV8::RES_TEX_PANEBKG:
		filename = ( _FS::getCurrentFullPath() 
		/ "Internal/" / "Resources/" / "Textures/" 
		/ "smallpanelbacking.png").string().c_str();
		break;
	default: return 0; 
	}

	newRes->loadFile( filename );
	newRes->assignName( a_name );
	newRes->addCount();
	m_pTextureResources.push_back( newRes );
	return newRes;
}

};
};

