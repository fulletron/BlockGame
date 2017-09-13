#ifndef __SHADERPROGRAM_H_
#define __SHADERPROGRAM_H_

#include <Graphics/resource/resource.h>

namespace GS {
namespace Resource {

class ShaderResource;
class ShaderProgramResource : public Resource {
	//IMPLEMENT_IRESOURCE;
public:
	// TEMPORARILY PUBLIC FOR EASE OF DEV
	// gl texture of the font atlas
	_UINT32						m_shaderProgram;

selective:
	// shaders. consider making a different class!
	ShaderResource *					m_pVS;
	ShaderResource *					m_pGS; 
	ShaderResource *					m_pFS;

public:
	ShaderProgramResource();
	~ShaderProgramResource();

	_UINT32 init(
			const _UINT64 & a_name,
			ShaderResource * a_vs, 
			ShaderResource * a_fs, 
			ShaderResource * a_gs = 0 );

	_UINT32 shutdown();
	_UINT32 getProgram(){return m_shaderProgram;}

selective:
	_INT32 __validateShaderProgram();

};


};
};

#endif
