#include "reslib.h"

extern GS::Utilities::ChunkManager g_chunkMan;

namespace GS {
namespace Graphics {

template <typename T>
_TChunkPtr<T> allocateArray( const _UINT64 a_frameName, const int a_num )
{
	_TChunkPtr<T> pT;
	pT = g_chunkMan.allocate(
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
