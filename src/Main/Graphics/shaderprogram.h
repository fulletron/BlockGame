#ifndef __SHADERPROGRAM_H_
#define __SHADERPROGRAM_H_

#include <Utilities/utilities.h>
#include <Graphics/openglincludes.h>
#include "graphics.h"


namespace GS {
namespace Graphics {

class ShaderProgram {

public:
	// TEMPORARILY PUBLIC FOR EASE OF DEV
	// gl texture of the font atlas
	_UINT32						m_shaderProgram;

selective:
	// Is this font loaded?
	_BOOL						m_inited;

	// shaders. consider making a different class!
	_UINT32						m_vertexShader;
	_UINT32						m_geometryShader; 
	_UINT32						m_fragmentShader;

public:
	ShaderProgram();
	~ShaderProgram();

	_INT32 init(
			const char * a_vertexSource, 
			const char * a_fragmentSource, 
			const char * a_geometrySource = 0 );

	void shutdown();

selective:
	_INT32 __compileShader( 
			_UINT32 & a_shaderID, 
			const char * a_source,
			const _INT32 a_shaderType );

	_INT32 __validateShaderProgram();

};


};
};

#endif
