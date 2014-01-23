#include "shaderresource.h"
#include <Graphics\openglincludes.h>

namespace GS {
namespace ResourceNS {

	_UINT32 ShaderResource::init(GS::Game * a_rpGame, const char * a_charStream, int a_shaderType)
	{
		m_rpGame = a_rpGame;

		bool success = __loadShader(a_charStream, a_shaderType);
		if(success)
			return 0;
		else
			return 1;
	}

	void ShaderResource::shutdown()
	{
		__deleteShader();
	}

	bool ShaderResource::isLoaded()
	{
		return m_loaded;
	}

	_UINT32 ShaderResource::getShaderID()
	{
		return m_shaderId;
	}

	bool ShaderResource::__loadShader(const char * a_shaderSource, int a_iType)
	{
		m_shaderId = glCreateShader(a_iType);

		glShaderSource(m_shaderId, 1, &a_shaderSource, NULL);
		glCompileShader(m_shaderId);

		int iCompilationStatus;
		glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &iCompilationStatus);

		if(iCompilationStatus == GL_FALSE)
			return false;

		m_shaderType = a_iType;
		m_loaded = true;

		return true;
	}

	void ShaderResource::__deleteShader()
	{
		if(!isLoaded())
			return;
		m_loaded = false;
		glDeleteShader(m_shaderId);
	}

};
};