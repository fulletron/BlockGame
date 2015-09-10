#ifndef __RESOURCELIB_H_
#define __RESOURCELIB_H_

#include <Utilities/typedefinitions.h>
#include <Graphics/font.h>
#include <Graphics/shaderprogram.h>
#include <Graphics/shader.h>
#include <Graphics/texture.h>
#include <Graphics/mesh.h>

namespace GS {
namespace Graphics {

class ResourceLibrary
{
public:
	enum {
	UNKNOWN = -1,
	FONT = 1,
	SHADER = 2,
	SHADERPROGRAM = 3,
	TEXTURE = 4,
	MESH = 5
	};

selective:
	static const int NUM_FONTS = 1;
	static const int NUM_SHADERS = 6;
	static const int NUM_SHADERPROGRAMS = 3;
	static const int NUM_TEXTURES = 1;
	static const int NUM_MESHES = 2;

	_VECTOR<FontResource*>					m_pFontResources;
	_VECTOR<ShaderResource*>				m_pShaderResources;
	_VECTOR<ShaderProgramResource*>			m_pShaderProgramResources;
	_VECTOR<TextureResource*>				m_pTextureResources;
	_VECTOR<MeshResource*>					m_pMeshResources;

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
	FontResource * findFontResource( const _UINT64 a_name );

	/**
	* Specifically finds a Shader resource by name
	*/
	ShaderResource * findShaderResource( const _UINT64 a_name );

	/**
	* Specifically find a Shader Program by name
	*/
	ShaderProgramResource * findShaderProgramResource( 
						const _UINT64 a_name );

	TextureResource * findTextureResource( const _UINT64 a_name );
	MeshResource * findMeshResource( const _UINT64 a_name );
	/**
	* Subtracts a reference count from the resource. DOES NOT DELETE IT!
	*/
	_INT32 forgetResource( const _UINT32 a_type, const _UINT64 a_name );
	_INT32 forgetResource( IResource * a_pResource );

selective:

	/**
	* Looks up the index of a resource in a vector by name
	*/
	template <typename T>
	_UINT32 __indexOfResource( _VECTOR<T> * a_pVec, const _UINT64 a_name );

	/**
	* Specifically builds a font resource by name
	*/
	FontResource * __buildFontRes( const _UINT64 a_name );

	/**
	* Specifically builds a Shader Resource by name
	*/
	ShaderResource * __buildShaderRes( const _UINT64 a_name );

	/**
	* Specifically build a Shader Program by name
	*/
	ShaderProgramResource * __buildShaderProgramRes( 
						const _UINT64 a_name );

	TextureResource * __buildTextureRes( const _UINT64 a_name );
	MeshResource * __buildMeshRes( const _UINT64 a_name );
};

};
};

#endif
