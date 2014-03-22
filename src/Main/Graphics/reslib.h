#ifndef __RESOURCELIB_H_
#define __RESOURCELIB_H_

#include <Utilities/gsvector.h>
#include <Graphics/font.h>
#include <Graphics/shaderprogram.h>
#include <Graphics/shader.h>

namespace GS {
namespace Graphics {

class ResourceLibrary
{
public:
	enum {
	UNKNOWN = -1,
	FONT = 1,
	SHADER = 2,
	SHADERPROGRAM = 3
	};

selective:
	static const int NUM_FONTS = 2;
	static const int NUM_SHADERS = 2;
	static const int NUM_SHADERPROGRAMS = 2;

	GS::Utilities::LimitedVector<FontResource> m_fontResources;
	GS::Utilities::LimitedVector<ShaderResource> m_shaderResources;
	GS::Utilities::LimitedVector<ShaderProgramResource> m_shaderProgramResources;
	
public:

	ResourceLibrary(){}
	~ResourceLibrary(){}

	/** 
	* Initializes the library. LimitedVectors are properly allocated
	* chunked memory.
	*
	* @return _UINT32 0 is success
	*/
	_UINT32 init();

	/*
	template <typename T>
	T * findResource( const _UINT32 a_type, const _UINT64 a_name );
	*/
	
	/**
	* Specifically finds a font resource by name
	*/
	FontResource * findFontResource( const _INT64 a_name );

	/**
	* Specifically finds a Shader resource by name
	*/
	ShaderResource * findShaderResource( const _INT64 a_name );

	/**
	* Specifically find a Shader Program by name
	*/
	ShaderProgramResource * findShaderProgramResource( 
						const _INT64 a_name );
	
	/**
	* Subtracts a reference count from the resource. DOES NOT DELETE IT!
	*/
	_INT32 forgetResource( const _INT32 a_type, const _INT64 a_name );

selective:
	template <typename T>
	_INT32 __indexOfResource( GS::Utilities::LimitedVector<T> * a_pVec, const _INT64 a_name );

	/**
	* Specifically builds a font resource by name
	*/
	FontResource * __buildFontRes( const _INT64 a_name );

	/**
	* Specifically builds a Shader Resource by name
	*/
	ShaderResource * __buildShaderRes( const _INT64 a_name );

	/**
	* Specifically build a Shader Program by name
	*/
	ShaderProgramResource * __buildShaderProgramRes( 
						const _INT64 a_name );
};

};
};

#endif
