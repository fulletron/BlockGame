#include "reslib.h"

namespace GS {
namespace Graphics {

_UINT32 ResourceLibrary::init()
{
	//m_pFontResources.resize(10);
	//m_pShaderResources.resize(10);
	//m_pShaderProgramResources.resize(10);
	//m_pTextureResources.resize(10);
	//m_pMeshResources.resize(10);

	return 0;
}

template <typename T>
_UINT32 ResourceLibrary::__indexOfResource( 
	_VECTOR<T> * a_pVec, 
	const _UINT64 a_name ) 
{
	for( int i = 0; i < STATIC_CAST( _UINT32, a_pVec->size() ); ++i )
		if( a_pVec->at(i)->getName() == a_name )
			return i;
	return -1;
}
	
template _UINT32 ResourceLibrary::__indexOfResource( 
	_VECTOR<FontResource*> * a_pVec, 
	const _UINT64 a_name );
template _UINT32 ResourceLibrary::__indexOfResource( 
	_VECTOR<ShaderResource*> * a_pVec, 
	const _UINT64 a_name );
template _UINT32 ResourceLibrary::__indexOfResource( 
	_VECTOR<ShaderProgramResource*> * a_pVec, 
	const _UINT64 a_name );
template _UINT32 ResourceLibrary::__indexOfResource( 
	_VECTOR<TextureResource*> * a_pVec, 
	const _UINT64 a_name );
template _UINT32 ResourceLibrary::__indexOfResource( 
	_VECTOR<MeshResource*> * a_pVec, 
	const _UINT64 a_name );

FontResource * ResourceLibrary::findFontResource( const _UINT64 a_name )
{
	_INT32 loc = __indexOfResource<FontResource*>( 
				&m_pFontResources, a_name );

	if( loc == -1 )
		return __buildFontRes( a_name );
	
	FontResource * ret = m_pFontResources.at( loc );
	ret->addCount();
	return ret;

}

ShaderResource * ResourceLibrary::findShaderResource( const _UINT64 a_name )
{
	_INT32 loc = __indexOfResource<ShaderResource*>( 
				&m_pShaderResources, a_name );

	if( loc == -1 )
		return __buildShaderRes( a_name );

	ShaderResource * ret = m_pShaderResources.at( loc );
	ret->addCount();
	return ret;
}

ShaderProgramResource * ResourceLibrary::findShaderProgramResource( 
	const _UINT64 a_name  )
{
	_INT32 loc = __indexOfResource<ShaderProgramResource*>( 
				&m_pShaderProgramResources, a_name );

	if( loc == -1 )
		return __buildShaderProgramRes( a_name );

	ShaderProgramResource * ret = m_pShaderProgramResources.at( loc );
	ret->addCount();
	return ret;
}

TextureResource * ResourceLibrary::findTextureResource( 
	const _UINT64 a_name  )
{
	_INT32 loc = __indexOfResource<TextureResource*>( 
				&m_pTextureResources, a_name );

	if( loc == -1 )
		return __buildTextureRes( a_name );

	TextureResource * ret = m_pTextureResources.at( loc );
	ret->addCount();
	return ret;
}

MeshResource * ResourceLibrary::findMeshResource(
	const _UINT64 a_name )
{
	_INT32 loc = __indexOfResource<MeshResource*>(
		&m_pMeshResources, a_name );

	if( loc == -1 )
		return __buildMeshRes( a_name );

	MeshResource * ret = m_pMeshResources.at( loc );
	ret->addCount();
	return ret;
}

// TODO :: IMPLEMENT FORGET
_INT32 ResourceLibrary::forgetResource( const _UINT32 a_type, const _UINT64 a_name )
{
	return 0;
}

_INT32 ResourceLibrary::forgetResource( IResource * a_pResource )
{
	return forgetResource( a_pResource->getType(), a_pResource->getName());
}

};
};
