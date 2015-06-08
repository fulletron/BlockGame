#include "shaderprogram.h"
#include <Utilities/chunkmanager.h>
#include <Utilities/glfwerrorfunc.h>
#include <Graphics/window.h>
#include <Graphics/reslib.h>
#include <Graphics/shader.h>

extern GS::Graphics::ResourceLibrary g_lib;
extern GS::Utilities::ChunkManager g_chunkman;
extern GS::Graphics::Window g_window;

namespace GS {
namespace Graphics {

ShaderProgramResource::ShaderProgramResource()
{
	m_inited = false; 	
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

	return ret;
}

_INT32 ShaderProgramResource::init( ShaderResource * const a_vs, ShaderResource * const a_fs, ShaderResource * const a_gs)
{
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

	m_inited = true;

	return 0;
}

void ShaderProgramResource::shutdown()
{
/*
	glDeleteShader( m_vertexShader );
	glDeleteShader( m_fragmentShader );
	if( m_geometryShader )
		glDeleteShader( m_geometryShader );
	glDeleteProgram( m_shaderProgram );
*/
}

};
};