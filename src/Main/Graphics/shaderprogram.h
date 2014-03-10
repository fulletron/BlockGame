#ifndef __SHADERPROGRAM_H_
#define __SHADERPROGRAM_H_

#include <Graphics/resource.h>

namespace GS {
namespace Graphics {

class ShaderProgramResource : public Resource {

public:
	// TEMPORARILY PUBLIC FOR EASE OF DEV
	// gl texture of the font atlas
	_UINT32						m_shaderProgram;

selective:
	// Is this font loaded?
	_BOOL						m_inited;

	// shaders. consider making a different class!
	_UINT64						m_vsName;
	_UINT64						m_gsName; 
	_UINT64						m_fsName;

public:
	ShaderProgramResource();
	~ShaderProgramResource();

	_INT32 init(
			const _UINT64 & a_vsName, 
			const _UINT64 & a_fsName, 
			const _UINT64 & a_gsName = 0 );

	void shutdown();

selective:
	_INT32 __validateShaderProgram();

};


};
};

#endif
