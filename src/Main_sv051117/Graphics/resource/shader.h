#ifndef __SHADER_H_
#define __SHADER_H_

#include "iresource.h"

namespace GS {
namespace Resource {

class ShaderResource : public IResource {

	IMPLEMENT_IRESOURCE;

selective:
	_UINT32 m_shader;

public:
	ShaderResource();
	~ShaderResource();

	_UINT32 init(const _UINT64 & a_name, const char * a_source,
			const _INT32 a_type );
//	_UINT32 init(const _UINT64 & a_name, std::string * a_source,
//		const _INT32 a_type);

	_UINT32 shutdown();


	_UINT32 getShader(){return m_shader;}
	void bindFragDataLoc( const int a_loc, const char * a_str );

selective:
	_INT32 __compileShader(	const char * a_source, _INT32 a_type );	

};

};
};

#endif
