#ifndef __SHADERPROGRAM_H_
#define __SHADERPROGRAM_H_

#include <Graphics/resource.h>

namespace GS {
namespace Graphics {

class ShaderResource;
class ShaderProgramResource : public Resource {

public:
	// TEMPORARILY PUBLIC FOR EASE OF DEV
	// gl texture of the font atlas
	_UINT32						m_shaderProgram;

selective:
	// Is this font loaded?
	_BOOL						m_inited;

	// shaders. consider making a different class!
	ShaderResource *					m_pVS;
	ShaderResource *					m_pGS; 
	ShaderResource *					m_pFS;

public:
	ShaderProgramResource();
	~ShaderProgramResource();

	_INT32 init(
			ShaderResource * a_vs, 
			ShaderResource * a_fs, 
			ShaderResource * a_gs = 0 );

	void shutdown();
	_UINT32 getProgram(){return m_shaderProgram;}

selective:
	_INT32 __validateShaderProgram();

};


};
};

#endif
