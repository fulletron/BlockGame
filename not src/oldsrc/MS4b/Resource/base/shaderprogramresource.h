#ifndef __SHADERPROGRAMRESOURCE_H_
#define __SHADERPROGRAMRESOURCE_H_

#include "resourcefile.h"
#include <Graphics\openglincludes.h>

namespace GS {
namespace ResourceNS {

	class ShaderResource;

	class ShaderProgramResource
	{
	private:
		GS::Game * m_rpGame;

		void __createProgram();
		void __deleteProgram();

		bool __addShaderToProgram(ShaderResource* shShader);

		ShaderResource * m_rpVertexShader;
		ShaderResource * m_rpGeometryShader;
		ShaderResource * m_rpFragmentShader;

	public:
		ShaderProgramResource(){m_linked = false; m_programId = 0; m_rpVertexShader = 0; m_rpGeometryShader = 0; m_rpFragmentShader = 0;}
		~ShaderProgramResource(){}

		_UINT32 init(GS::Game * const a_rpGame, GS::LibraryNS::EntryInitFunction a_vsResource, GS::LibraryNS::EntryInitFunction a_fsResource);
		void shutdown();

		bool link();
		void useProgram();
		_UINT32 getProgramID();


		// Setting vectors
		void setUniform(char * sName, glm::vec2* vVectors, int iCount = 1);
		void setUniform(char * sName, const glm::vec2 vVector);
		void setUniform(char * sName, glm::vec3* vVectors, int iCount = 1);
		void setUniform(char * sName, const glm::vec3 vVector);
		void setUniform(char * sName, glm::vec4* vVectors, int iCount = 1);
		void setUniform(char * sName, const glm::vec4 vVector);

		// Setting floats
		void setUniform(char * sName, float* fValues, int iCount = 1);
		void setUniform(char * sName, const float fValue);

		// Setting 3x3 matrices
		void setUniform(char * sName, glm::mat3* mMatrices, int iCount = 1);
		void setUniform(char * sName, const glm::mat3 mMatrix);

		// Setting 4x4 matrices
		void setUniform(char * sName, glm::mat4* mMatrices, int iCount = 1);
		void setUniform(char * sName, const glm::mat4 mMatrix);

		// Setting integers
		void setUniform(char * sName, int* iValues, int iCount = 1);
		void setUniform(char * sName, const int iValue);

	private:
		_UINT32				m_programId; // ID of program
		bool				m_linked; // Whether program was linked and is ready to use
	};

};
};

#endif