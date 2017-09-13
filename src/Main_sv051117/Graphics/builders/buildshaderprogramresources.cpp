#include "../library/library.h"
#include "../resource/shaderprogram.h"

#include "Utilities/definitions_values.h"

namespace GS {
namespace Library {

GS::Resource::ShaderProgramResource * Library::__buildShaderProgramResource( const _UINT64 a_name )
{
	GS::Resource::ShaderProgramResource * newRes = new GS::Resource::ShaderProgramResource();

	GS::Resource::ShaderResource * vs = 0;
	GS::Resource::ShaderResource * gs = 0;
	GS::Resource::ShaderResource * fs = 0;

	switch(a_name)
	{
	case CV8::RES_SP_FONTDRAW :
		vs = __findShaderResource( CV8::RES_SH_BASEFONTVS );
		fs = __findShaderResource( CV8::RES_SH_BASEFONTFS );
		break;
	case CV8::RES_SP_FBDRAW :
		vs = __findShaderResource( CV8::RES_SH_BASEFBVS );
		fs = __findShaderResource( CV8::RES_SH_BASEFBFS );
		break;
	case CV8::RES_SP_TEXRECTDRAW :
		vs = __findShaderResource( CV8::RES_SH_TEXRECTVS );
		fs = __findShaderResource( CV8::RES_SH_TEXRECTFS );
		break;
	default: return 0; 
	}

	newRes->init( a_name, vs, fs, gs );
	newRes->addCount();
	m_shaderProgramResources.push_back( newRes );
	return newRes;
}

};
};

