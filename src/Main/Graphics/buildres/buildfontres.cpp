#include <Graphics/reslib.h>

namespace GS {
namespace Graphics {

FontResource * ResourceLibrary::__buildFontRes( const _INT64 a_name )
{
	FontResource newRes;

	switch(a_name)
	{
	case CV8::RES_FONT_KASHSCRIPT:
		break;
	default: return 0; 
	}

	//newRes.init( src.c_str(), type );
	newRes.assignName( a_name );
	m_fontResources.add( newRes );
	return m_fontResources.getp( a_name );
}

};
};

