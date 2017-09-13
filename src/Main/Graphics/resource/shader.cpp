#include "shader.h"
#include <Utilities/definitions_types.h>
#include <Graphics/openglincludes.h>

namespace GS {
namespace Resource {

ShaderResource::ShaderResource()
: m_shader(0)
{}

ShaderResource::~ShaderResource()
{}

_UINT32 ShaderResource::init( const _UINT64 & a_name, const char * a_source, const _INT32 a_type )
{
	__setName(a_name);
	__setType(RESTYPE::SHADER);
	if( isReady() )
		return 1;
	if( __compileShader( a_source, a_type ) )
		setIsReady(true);
	return 0;
}

void ShaderResource::bindFragDataLoc( const int a_loc, const char * a_str )
{
	glBindFragDataLocation( m_shader, a_loc, a_str );
}

_INT32 ShaderResource::__compileShader( const char * a_source, const _INT32 a_type )
{
	_INT32 ret = 0;
	m_shader = glCreateShader( a_type );
	glShaderSource( m_shader, 1, &a_source, NULL );
	glCompileShader( m_shader );

	glGetShaderiv( m_shader, GL_COMPILE_STATUS, &ret );

	if (!ret)
	{
		DEBUG_OUT_RED("Shader" << m_name << "could not compile...");
		///MAKE NOISE
	}

	return ret;
}

_UINT32 ShaderResource::shutdown()
{
	return 0;
}

};
};
