#include "shaderprogram.h"

extern GS::Utilities::ChunkManager g_chunkman;
extern GS::Graphics::Window g_window;

namespace GS {
namespace Graphics {


ShaderProgram::ShaderProgram()
{
	m_inited = false; 	
	m_vertexShader = 0;
	m_geometryShader = 0; 
	m_fragmentShader = 0;	
}

ShaderProgram::~ShaderProgram()
{
}

_INT32 ShaderProgram::__compileShader(_UINT32 & a_shaderID, const char * a_source, const _INT32 a_shaderType)
{
	_INT32 ret = 0;
    // Create and compile the vertex shader
    a_shaderID = glCreateShader(a_shaderType);
    glShaderSource(a_shaderID, 1, &a_source, NULL);
    glCompileShader(a_shaderID);
	glGetShaderiv(a_shaderID, GL_COMPILE_STATUS, &ret);

	// 1 is true (compiled)
	// 0 is false (did not compile)

	return ret;
}

_INT32 ShaderProgram::__validateShaderProgram()
{
	_INT32 ret = 0;

	glValidateProgram( m_shaderProgram );
	glGetProgramiv(m_shaderProgram, GL_VALIDATE_STATUS, &ret);

	// 1 is true (valid)
	// 0 is false (invalid)

	return ret;
}

_INT32 ShaderProgram::init(const char * a_vertexSource, const char * a_fragmentSource, const char * a_geometrySource)
{
	if( !a_vertexSource
	||	!a_fragmentSource )
		return -1;

	if(!__compileShader( m_vertexShader, a_vertexSource, GL_VERTEX_SHADER ))
		return -2;
	if(!__compileShader( m_fragmentShader, a_fragmentSource, GL_FRAGMENT_SHADER ))
		return -3;

	if( a_geometrySource )
		if(!__compileShader( m_geometryShader, a_geometrySource, GL_GEOMETRY_SHADER ))
			return -4;

    // Link the vertex and fragment shader into a shader program
    m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);

	// link geo shader if there is one
	if(m_geometryShader)
		glAttachShader(m_shaderProgram, m_geometryShader);

    glLinkProgram(m_shaderProgram);

	if( !__validateShaderProgram() )
		return -5;

	//glBindFragDataLocation(m_shaderProgram, 0, "outColor");

	m_inited = true;

	return 0;
}

void ShaderProgram::shutdown()
{
	glDeleteShader( m_vertexShader );
	glDeleteShader( m_fragmentShader );
	if( m_geometryShader )
		glDeleteShader( m_geometryShader );
	glDeleteProgram( m_shaderProgram );
}

};
};
