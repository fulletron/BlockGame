#include "library.h"

namespace GS {
namespace Library {

_UINT32 Library::init()
{
	return 0;
}

_UINT32 Library::shutdown()
{
	return 0;
}

_UINT32 Library::subscribe(const _UINT64 a_name, const RESTYPE & a_type)
{
	switch (a_type)
	{
	case RESTYPE::TEXTURE:
		break;
	case RESTYPE::MESH:
		break;
	case RESTYPE::SHADERPROGRAM:
		break;
	case RESTYPE::SHADER:
		break;
	default:
		break;
	}
	return 0;
}

_UINT32 Library::unsubscribe(const _UINT64 a_name, const RESTYPE & a_type)
{
	switch (a_type)
	{
	case RESTYPE::TEXTURE:
		break;
	case RESTYPE::MESH:
		break;
	case RESTYPE::SHADERPROGRAM:
		break;
	case RESTYPE::SHADER:
		break;
	default:
		break;
	}
	return 0;
}

GS::Resource::TextureResource * Library::__findTextureResource(
	const _UINT64 a_name)
{
	_INT32 loc = __indexOfResource<GS::Resource::TextureResource*>(
		&m_textureResources, a_name);

	if (loc == -1)
		return __buildTextureResource(a_name);

	GS::Resource::TextureResource * ret = m_textureResources.at(loc);
//	ret->addCount();
	return ret;
}

GS::Resource::MeshResource * Library::__findMeshResource(
	const _UINT64 a_name)
{
	_INT32 loc = __indexOfResource<GS::Resource::MeshResource*>(
		&m_meshResources, a_name);

	if (loc == -1)
		return __buildMeshResource(a_name);

	GS::Resource::MeshResource * ret = m_meshResources.at(loc);
//	ret->addCount();
	return ret;
}

GS::Resource::ShaderResource * Library::__findShaderResource(
	const _UINT64 a_name)
{
	_INT32 loc = __indexOfResource<GS::Resource::ShaderResource*>(
		&m_shaderResources, a_name);

	if (loc == -1)
		return __buildShaderResource(a_name);

	GS::Resource::ShaderResource * ret = m_shaderResources.at(loc);
	//	ret->addCount();
	return ret;
}

GS::Resource::ShaderProgramResource * Library::__findShaderProgramResource(
	const _UINT64 a_name)
{
	_INT32 loc = __indexOfResource<GS::Resource::ShaderProgramResource*>(
		&m_shaderProgramResources, a_name);

	if (loc == -1)
		return __buildShaderProgramResource(a_name);

	GS::Resource::ShaderProgramResource * ret = m_shaderProgramResources.at(loc);
	//	ret->addCount();
	return ret;
}

template <typename T>
_UINT32 Library::__indexOfResource(
	_VECTOR<T> * a_pVec,
	const _UINT64 a_name)
{
	for (int i = 0; i < STATIC_CAST(_UINT32, a_pVec->size()); ++i)
		if (a_pVec->at(i)->getName() == a_name)
			return i;
	return -1;
}
/*
template _UINT32 Library::__indexOfResource(
	_VECTOR<FontResource*> * a_pVec,
	const _UINT64 a_name);
*/
template _UINT32 Library::__indexOfResource(
	_VECTOR<GS::Resource::ShaderResource*> * a_pVec,
	const _UINT64 a_name);
template _UINT32 Library::__indexOfResource(
	_VECTOR<GS::Resource::ShaderProgramResource*> * a_pVec,
	const _UINT64 a_name);
template _UINT32 Library::__indexOfResource(
	_VECTOR<GS::Resource::TextureResource*> * a_pVec,
	const _UINT64 a_name);
template _UINT32 Library::__indexOfResource(
	_VECTOR<GS::Resource::MeshResource*> * a_pVec,
	const _UINT64 a_name);


};
};
