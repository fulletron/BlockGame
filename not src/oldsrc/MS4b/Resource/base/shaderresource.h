#ifndef __SHADERRESOURCE_H_
#define __SHADERRESOURCE_H_

#include "resourcefile.h"

namespace GS {
namespace ResourceNS {

	//GL_VERTEX_SHADER
	//GL_GEOMETRY_SHADER
	//GL_FRAGMENT_SHADER

	class ShaderResource
	{
	private:
		bool __loadShader(const char * sFile, int a_iType);
		void __deleteShader();
	public:
		ShaderResource(){m_loaded = false;}
		~ShaderResource(){}

		_UINT32 init(GS::Game * a_rpGame, const char * a_charStream, int a_shaderType);
		void shutdown();

		bool isLoaded();
		_UINT32 getShaderID();
	private:
		GS::Game *			m_rpGame;
		_UINT32				m_shaderId;
		int					m_shaderType;
		bool				m_loaded;
	};
};
};

#endif