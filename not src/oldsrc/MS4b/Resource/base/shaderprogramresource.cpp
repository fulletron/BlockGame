#include "shaderprogramresource.h"
#include <Graphics\openglincludes.h>
#include "shaderresource.h"


namespace GS {
namespace ResourceNS {

	_UINT32 ShaderProgramResource::init(GS::Game * a_rpGame, GS::LibraryNS::EntryInitFunction a_vsResource, GS::LibraryNS::EntryInitFunction a_fsResource)
	{
		m_rpGame = a_rpGame;
		__createProgram();
		if(!m_programId)
			return -1;

		m_rpVertexShader = (GS::ResourceNS::ShaderResource *)a_vsResource(a_rpGame);
		__addShaderToProgram(m_rpVertexShader);

		m_rpFragmentShader = (GS::ResourceNS::ShaderResource *)a_fsResource(a_rpGame);
		__addShaderToProgram(m_rpFragmentShader);

		//__linkProgram();

		return 0;
	}

	void ShaderProgramResource::shutdown()
	{
	}

	void ShaderProgramResource::__createProgram()
	{
		m_programId = glCreateProgram();
	}

	bool ShaderProgramResource::__addShaderToProgram(ShaderResource* a_shader)
	{
		if(!a_shader->isLoaded())return false;

		glAttachShader(m_programId, a_shader->getShaderID());

		return true;
	}

	bool ShaderProgramResource::link()
	{
		glLinkProgram(m_programId);
		int iLinkStatus;
		glGetProgramiv(m_programId, GL_LINK_STATUS, &iLinkStatus);
		m_linked = iLinkStatus == GL_TRUE;
		return m_linked;
	}

	void ShaderProgramResource::__deleteProgram()
	{
		if(!m_linked)
			return;
		m_linked = false;

		glDeleteProgram(m_programId);
	}

	void ShaderProgramResource::useProgram()
	{
		if(m_linked)
			glUseProgram(m_programId);
	}

	_UINT32 ShaderProgramResource::getProgramID()
	{
		return m_programId;
	}

	// Setting floats

	void ShaderProgramResource::setUniform(char * sName, float* fValues, int iCount)
	{
		int iLoc = glGetUniformLocation(m_programId, sName);
		glUniform1fv(iLoc, iCount, fValues);
	}

	void ShaderProgramResource::setUniform(char * sName, const float fValue)
	{
		int iLoc = glGetUniformLocation(m_programId, sName);
		glUniform1fv(iLoc, 1, &fValue);
	}

	// Setting vectors

	void ShaderProgramResource::setUniform(char * sName, glm::vec2* vVectors, int iCount)
	{
		int iLoc = glGetUniformLocation(m_programId, sName);
		glUniform2fv(iLoc, iCount, (GLfloat*)vVectors);
	}

	void ShaderProgramResource::setUniform(char * sName, const glm::vec2 vVector)
	{
		int iLoc = glGetUniformLocation(m_programId, sName);
		glUniform2fv(iLoc, 1, (GLfloat*)&vVector);
	}

	void ShaderProgramResource::setUniform(char * sName, glm::vec3* vVectors, int iCount)
	{
		int iLoc = glGetUniformLocation(m_programId, sName);
		glUniform3fv(iLoc, iCount, (GLfloat*)vVectors);
	}

	void ShaderProgramResource::setUniform(char * sName, const glm::vec3 vVector)
	{
		int iLoc = glGetUniformLocation(m_programId, sName);
		glUniform3fv(iLoc, 1, (GLfloat*)&vVector);
	}

	void ShaderProgramResource::setUniform(char * sName, glm::vec4* vVectors, int iCount)
	{
		int iLoc = glGetUniformLocation(m_programId, sName);
		glUniform4fv(iLoc, iCount, (GLfloat*)vVectors);
	}

	void ShaderProgramResource::setUniform(char * sName, const glm::vec4 vVector)
	{
		int iLoc = glGetUniformLocation(m_programId, sName);
		glUniform4fv(iLoc, 1, (GLfloat*)&vVector);
	}

	// Setting 3x3 matrices

	void ShaderProgramResource::setUniform(char * sName, glm::mat3* mMatrices, int iCount)
	{
		int iLoc = glGetUniformLocation(m_programId, sName);
		glUniformMatrix3fv(iLoc, iCount, false, (GLfloat*)mMatrices);
	}

	void ShaderProgramResource::setUniform(char * sName, const glm::mat3 mMatrix)
	{
		int iLoc = glGetUniformLocation(m_programId, sName);
		glUniformMatrix3fv(iLoc, 1, false, (GLfloat*)&mMatrix);
	}

	// Setting 4x4 matrices

	void ShaderProgramResource::setUniform(char * sName, glm::mat4* mMatrices, int iCount)
	{
		int iLoc = glGetUniformLocation(m_programId, sName);
		glUniformMatrix4fv(iLoc, iCount, false, (GLfloat*)mMatrices);
	}

	void ShaderProgramResource::setUniform(char * sName, const glm::mat4 mMatrix)
	{
		int iLoc = glGetUniformLocation(m_programId, sName);
		glUniformMatrix4fv(iLoc, 1, false, (GLfloat*)&mMatrix);
	}

	// Setting integers

	void ShaderProgramResource::setUniform(char * sName, int* iValues, int iCount)
	{
		int iLoc = glGetUniformLocation(m_programId, sName);
		glUniform1iv(iLoc, iCount, iValues);
	}

	void ShaderProgramResource::setUniform(char * sName, const int iValue)
	{
		int iLoc = glGetUniformLocation(m_programId, sName);
		glUniform1i(iLoc, iValue);
	}

};
};