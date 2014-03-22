#include "shader.h"

#include <Graphics/openglincludes.h>

namespace GS {
namespace Graphics {

ShaderResource::ShaderResource()
: Resource(), m_shader(0), m_inited(false)
{}

ShaderResource::~ShaderResource()
{}

_INT32 ShaderResource::init( const char * a_source, const _INT32 a_type )
{
	if( m_inited )
		return -1;
	if( __compileShader( a_source, a_type ) )
		m_inited = true;
	return 0;
}

_INT32 ShaderResource::__compileShader( const char * a_source, const _INT32 a_type )
{
	_INT32 ret = 0;
	m_shader = glCreateShader( a_type );
	glShaderSource( m_shader, 1, &a_source, NULL );
	glCompileShader( m_shader );

	glGetShaderiv( m_shader, GL_COMPILE_STATUS, &ret );

	return ret;
}

void ShaderResource::shutdown()
{
	
}

};
};
