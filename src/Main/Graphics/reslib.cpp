#include "reslib.h"

extern GS::Utilities::ChunkManager g_chunkman;

namespace GS {
namespace Graphics {

template <typename T>
_TChunkPtr<T> allocateArray( const _UINT64 a_frameName, const int a_num )
{
	_TChunkPtr<T> pT;
	pT = g_chunkman.allocate(
			a_frameName,
			sizeof( T ) * a_num,
			BOT
			);
	return pT;
}

/*
template<typename T>
T * ResourceLibrary::findResource( const _INT32 a_resType, const _UINT64 a_name )
{
	GS::Utilities::LimitedVector<T> * pVector = 0;
	
	switch(a_resType)
	{
	case FONT: 
		pVector = &m_fontResources; break;
	case SHADER: 
		pVector = &m_shaderResources; break;
	case SHADERPROGRAM: 
		pVector = &m_shaderProgramResources; break;
	
	default: return 0;
	}
	for( int i = 0; i < pVector->size(); ++i )
		if( pVector->at(i).getName() == a_name )
			return pVector->at(i);

	return 0;		
}
*/

_UINT32 ResourceLibrary::init()
{
	m_fontResources.init( 
				NUM_FONTS, 
				allocateArray<FontResource>( 
					CV8("smallres"), 
					NUM_FONTS 
				).pointer() 
			);
/*	
_TChunkPtr<FontResource> pFontRes;
	pFontRes = g_chunkMan.allocate( 
			CV8("resftsd0"), 
			sizeof( FontResource ) * NUM_FONTS, 
			BOT 
			);
	
	m_fontResources.init( NUM_FONTS, pFontRes.pointer() );
*/
	m_shaderResources.init( 
				NUM_SHADERS, 
				allocateArray<ShaderResource>( 
					CV8("smallres"), 
					NUM_SHADERS 
				).pointer() 
			);
	
	m_shaderProgramResources.init( 
				NUM_SHADERPROGRAMS, 
				allocateArray<ShaderProgramResource>( 
					CV8("smallres"), 
					NUM_SHADERPROGRAMS 
				).pointer() 
			);
	return 0;
}
	
FontResource * ResourceLibrary::findFontResource( const _UINT64 a_name )
{
	FontResource * ret = 0;
	for( int i = 0; i < m_fontResources.getSize(); ++i )
		ret = ( m_fontResources.getp(i) );
		if( ret->getName() == a_name )
			return ret;
	return 0;
}

//ShaderResource * ResourceLibrary::findShaderResource( const _UINT64 a_name )
//{
//	return 0;
//}

_INT32 ResourceLibrary::forgetResource( const _INT32 a_type, const _UINT64 a_name )
{
	return 0;
}


// THESE TWO FUNCTIONS SHOULD GET THEIR OWN CPP (EACH)

FontResource * ResourceLibrary::__buildFontRes( const _UINT64 a_name )
{
	return 0;
}

//ShaderResource * ResourceLibrary::__buildShaderRes( const _UINT64 a_name )
//{
//	return 0;
//}

};
};
