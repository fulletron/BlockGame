#include "reslib.h"

extern GS::Utilities::ChunkManager g_chunkman;

namespace GS {
namespace Graphics {

template <typename T>
_TChunkPtr<T> allocateArray( const _INT64 a_frameName, const int a_num )
{
	_TChunkPtr<T> pT;
	pT = g_chunkman.allocate(
			a_frameName,
			sizeof( T ) * a_num,
			BOT
			);
	return pT;
}

_UINT32 ResourceLibrary::init()
{
	m_fontResources.init( 
				NUM_FONTS, 
				allocateArray<FontResource>( 
					CV8::FRAME_SMALLRES, 
					NUM_FONTS 
				).pointer() 
			);
	m_shaderResources.init( 
				NUM_SHADERS, 
				allocateArray<ShaderResource>( 
					CV8::FRAME_SMALLRES, 
					NUM_SHADERS 
				).pointer() 
			);
	
	m_shaderProgramResources.init( 
				NUM_SHADERPROGRAMS, 
				allocateArray<ShaderProgramResource>( 
					CV8::FRAME_SMALLRES, 
					NUM_SHADERPROGRAMS 
				).pointer() 
			);
	return 0;
}

/*
template <typename T>
T * ResourceLibrary::findResource( const _UINT32 a_type, const _INT64 a_name )
{
	T * ret = 0;

	GS::Utilities::LimitedVector<T> * pVec = 0;
	switch( a_type )
	{
	case FONT: pVec = &m_fontResources; break;
	case SHADER: pVec = &m_shaderResources; break;
	case SHADERPROGRAM: pVec = &m_shaderProgramResources; break;
	default: break;
	}

	_INT32 loc = __indexOfResource<T>()
	return ret;
}
*/

template <typename T>
_INT32 ResourceLibrary::__indexOfResource( 
	GS::Utilities::LimitedVector<T> * a_pVec, 
	const _INT64 a_name ) 
{
	for( int i = 0; i < SC( _INT32, a_pVec->getSize() ); ++i )
		if( a_pVec->getp(i)->getName() == a_name )
			return i;
	return -1;
}
	
template _INT32 ResourceLibrary::__indexOfResource( 
	GS::Utilities::LimitedVector<FontResource> * a_pVec, 
	const _INT64 a_name );
template _INT32 ResourceLibrary::__indexOfResource( 
	GS::Utilities::LimitedVector<ShaderResource> * a_pVec, 
	const _INT64 a_name );
template _INT32 ResourceLibrary::__indexOfResource( 
	GS::Utilities::LimitedVector<ShaderProgramResource> * a_pVec, 
	const _INT64 a_name );

FontResource * ResourceLibrary::findFontResource( const _INT64 a_name )
{
	_INT32 loc = __indexOfResource<FontResource>( 
				&m_fontResources, a_name );

	if( loc == -1 )
		return __buildFontRes( a_name );
	
	FontResource * ret = m_fontResources.getp( loc );
	ret->addCount();
	return ret;

}

ShaderResource * ResourceLibrary::findShaderResource( const _INT64 a_name )
{
	_INT32 loc = __indexOfResource<ShaderResource>( 
				&m_shaderResources, a_name );

	if( loc == -1 )
		return __buildShaderRes( a_name );

	ShaderResource * ret = m_shaderResources.getp( loc );
	ret->addCount();
	return ret;
}

ShaderProgramResource * ResourceLibrary::findShaderProgramResource( 
	const _INT64 a_name  )
{
	_INT32 loc = __indexOfResource<ShaderProgramResource>( 
				&m_shaderProgramResources, a_name );

	if( loc == -1 )
		return __buildShaderProgramRes( a_name );

	ShaderProgramResource * ret = m_shaderProgramResources.getp( loc );
	ret->addCount();
	return ret;
}

_INT32 ResourceLibrary::forgetResource( const _INT32 a_type, const _INT64 a_name )
{
	return 0;
}

};
};
