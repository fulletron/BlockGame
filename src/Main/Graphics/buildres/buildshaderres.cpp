#include <Graphics/reslib.h>

namespace GS {
namespace Graphics {

#define R_SH_BASEFTVS 1
#define R_SH_BASEFTFS 2

ShaderResource * ResourceLibrary::__buildShaderRes( const _INT64 a_name )
{
	ShaderResource newRes;
	std::string src = "";
	_INT32 type = 0;

	switch(a_name)
	{
	case R_SH_BASEFTVS :
		type = GL_VERTEX_SHADER;
		src = _FS::loadFile( ( _FS::getCurrentFullPath() 
		/ "Internal/" / "Resources/" / "Effects/" 
		/ "basicfont.vert").string().c_str() );
		break;
	case R_SH_BASEFTFS: 
		type = GL_FRAGMENT_SHADER;
		src = _FS::loadFile( ( _FS::getCurrentFullPath() 
		/ "Internal/" / "Resources/" / "Effects/" 
		/ "basicfont.frag").string().c_str() );
		break;
	default: return 0; 
	}

	newRes.init( src.c_str(), type );
	newRes.assignName( a_name );
	m_shaderResources.add( newRes );
	return m_shaderResources.getp( a_name );
}

};
};

