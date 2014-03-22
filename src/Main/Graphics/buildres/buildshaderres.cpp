#include <Graphics/reslib.h>

namespace GS {
namespace Graphics {

ShaderResource * ResourceLibrary::__buildShaderRes( const _INT64 a_name )
{
	ShaderResource newRes;
	std::string src = "";
	_INT32 type = 0;

	switch(a_name)
	{
	case CV8::RES_SH_BASEFONTVS :
		type = GL_VERTEX_SHADER;
		src = _FS::loadFile( ( _FS::getCurrentFullPath() 
		/ "Internal/" / "Resources/" / "Effects/" 
		/ "basicfont.vert").string().c_str() );
		break;
	case CV8::RES_SH_BASEFONTFS: 
		type = GL_FRAGMENT_SHADER;
		src = _FS::loadFile( ( _FS::getCurrentFullPath() 
		/ "Internal/" / "Resources/" / "Effects/" 
		/ "basicfont.frag").string().c_str() );
		break;
	default: return 0; 
	}

	newRes.init( src.c_str(), type );
	newRes.assignName( a_name );
	newRes.addCount();
	_UINT32 loc = m_shaderResources.add( newRes );
	return m_shaderResources.getp( loc );
}
};

};