#ifndef __LIBRARY_H_
#define __LIBRARY_H_

#include "ilibrary.h"

#include "../resource/texture.h"
#include "../resource/mesh.h"
#include "../resource/shader.h"
#include "../resource/shaderprogram.h"

namespace GS {
namespace Library {

class Library : public ILibrary
{
selective:
	_VECTOR<GS::Resource::TextureResource*> m_textureResources;
	_VECTOR<GS::Resource::MeshResource*> m_meshResources;
	_VECTOR<GS::Resource::ShaderResource*> m_shaderResources;
	_VECTOR<GS::Resource::ShaderProgramResource*> m_shaderProgramResources;

public:

	_UINT32 init();
	_UINT32 shutdown();

	_UINT32 subscribe(const _UINT64 a_name, const RESTYPE & a_type);
	_UINT32 unsubscribe(const _UINT64 a_name, const RESTYPE & a_type);

selective:
	template <typename T>
	_UINT32 __indexOfResource( _VECTOR<T> * a_pVec, const _UINT64 a_name );

	GS::Resource::MeshResource * __findMeshResource(const _UINT64 a_name);
	GS::Resource::TextureResource * __findTextureResource(const _UINT64 a_name);
	GS::Resource::ShaderResource * __findShaderResource(const _UINT64 a_name);
	GS::Resource::ShaderProgramResource * __findShaderProgramResource(const _UINT64 a_name);

	/**
	* Specifically builds a font resource by name
	*/
	//FontResource * __buildFontRes(const _UINT64 a_name);

	/**
	* Specifically builds a Shader Resource by name
	*/
	GS::Resource::ShaderResource * __buildShaderResource(const _UINT64 a_name);

	/**
	* Specifically build a Shader Program by name
	*/
	GS::Resource::ShaderProgramResource * __buildShaderProgramResource(
		const _UINT64 a_name);

	GS::Resource::TextureResource * __buildTextureResource(const _UINT64 a_name);
	GS::Resource::MeshResource * __buildMeshResource(const _UINT64 a_name);
};


};
};

#endif
