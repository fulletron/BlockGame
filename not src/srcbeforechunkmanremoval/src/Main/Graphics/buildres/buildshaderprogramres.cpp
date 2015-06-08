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
		vs = findShaderResource( CV8::RES_SH_BASEFONTVS );
		fs = findShaderResource( CV8::RES_SH_BASEFONTFS );
		break;
	case CV8::RES_SP_FBDRAW :
		vs = findShaderResource( CV8::RES_SH_BASEFBVS );
		fs = findShaderResource( CV8::RES_SH_BASEFBFS );
		break;
	case CV8::RES_SP_TEXRECTDRAW :
		vs = findShaderResource( CV8::RES_SH_TEXRECTVS );
		fs = findShaderResource( CV8::RES_SH_TEXRECTFS );
		break;
	default: return 0; 
	}

	newRes.init( vs, fs, gs );
	newRes.assignName( a_name );
	newRes.addCount();
	_UINT32 loc = m_shaderProgramResources.add( newRes );
	return m_shaderProgramResources.getp( loc );
}

};
};
