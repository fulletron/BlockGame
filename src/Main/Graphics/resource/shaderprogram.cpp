#include "shaderprogram.h"
#include "shader.h"

#include "Utilities/gserrorfunc.h"
#include "Graphics/openglincludes.h"

//extern GS::Graphics::Window g_window;

namespace GS {
namespace Resource {

ShaderProgramResource::ShaderProgramResource()
{
	m_pVS = 0;
	m_pGS = 0; 
	m_pFS = 0;	
}

ShaderProgramResource::~ShaderProgramResource()
{
}

_INT32 ShaderProgramResource::__validateShaderProgram()
{
	_INT32 ret = 0;

	glValidateProgram( m_shaderProgram );
	glGetProgramiv(m_shaderProgram, GL_VALIDATE_STATUS, &ret);

	// 1 is true (valid)
	// 0 is false (invalid)
	if (!ret)
	{
	}

	return ret;
}

_UINT32 ShaderProgramResource::init(const _UINT64 & a_name, ShaderResource * a_vs, ShaderResource * a_fs, ShaderResource * a_gs)
{
	__setName(a_name);
	__setType(RESTYPE::SHADERPROGRAM);
	if( _CheckForErrors() )
		return -100;

	if(!a_vs
	|| !a_fs )
		return -1;

	if( !a_vs->getShader() 
	|| !a_fs->getShader() )
		return -2;
		
	m_pVS = a_vs;
	m_pGS = a_gs;
	m_pFS = a_fs;

    // Link the vertex and fragment shader into a shader program
    m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, a_vs->getShader() );
	glAttachShader(m_shaderProgram, a_fs->getShader() );

	// link geo shader if there is one
	if( a_gs )
		glAttachShader(m_shaderProgram, a_gs->getShader() );

    glLinkProgram(m_shaderProgram);

	if( !__validateShaderProgram() )
		return -5;

	//glBindFragDataLocation(m_shaderProgram, 0, "outColor");
	if( _CheckForErrors() )
		return -101;

	setIsReady(true);

	return 0;
}

_UINT32 ShaderProgramResource::shutdown()
{
/*
	glDeleteShader( m_vertexShader );
	glDeleteShader( m_fragmentShader );
	if( m_geometryShader )
		glDeleteShader( m_geometryShader );
	glDeleteProgram( m_shaderProgram );
*/
	return 0;
}

};
};
