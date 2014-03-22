#include <Graphics/reslib.h>

namespace GS {
namespace Graphics {

ShaderProgramResource * ResourceLibrary::__buildShaderProgramRes( const _INT64 a_name )
{
	ShaderProgramResource newRes;

	ShaderResource * vs = 0;
	ShaderResource * gs = 0;
	ShaderResource * fs = 0;

	switch(a_name)
	{
	case CV8::RES_SP_FONTDRAW :
		vs = findShaderResource( 0 );
		fs = findShaderResource( 0 );
		break;
	default: return 0; 
	}

	//newRes.init( src.c_str(), type );
	newRes.assignName( a_name );
	newRes.addCount();
	_UINT32 loc = m_shaderProgramResources.add( newRes );
	return m_shaderProgramResources.getp( loc );
}

};
};

