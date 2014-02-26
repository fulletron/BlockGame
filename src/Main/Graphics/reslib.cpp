#include "reslib.h"

extern GS::Utilities::ChunkManager g_chunkMan;

namespace GS {
namespace Graphics {

_UINT32 ResourceLibrary::init()
{
	_TChunkPtr<FontResource> pFontRes;
	pFontRes = g_chunkMan.allocate( 
			CV8("resftsd0"), 
			sizeof( FontResource ) * NUM_FONTS, 
			BOT 
			);
	
	m_fontResources.init( NUM_FONTS, pFontRes.pointer() );

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