#ifndef __SHADER_H_
#define __SHADER_H_

#include <Graphics/resource.h>

namespace GS {
namespace Graphics {

class ShaderResource : public Resource {

selective:
	_UINT32 m_shader;
	_BOOL m_inited;

public:
	ShaderResource();
	~ShaderResource();

	_INT32 init( 	const char * a_source,
			const _INT32 a_type );

	void shutdown();
	_UINT32 getShader(){return m_shader;}

selective:
	_INT32 __compileShader(	const char * a_source, _INT32 a_type );	

};

};
};

#endif
