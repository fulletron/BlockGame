#include <Graphics/reslib.h>

namespace GS {
namespace Graphics {

FontResource * ResourceLibrary::__buildFontRes( const _INT64 a_name )
{
	FontResource newRes;

	switch(a_name)
	{
	case CV8::RES_FONT_KASHSCRIPT:
		newRes.loadFile( "KaushanScript-Regular.otf", 16);
		break;
	default: return 0; 
	}

	newRes.assignName( a_name );
	newRes.addCount();
	_UINT32 loc = m_fontResources.add( newRes );
	return m_fontResources.getp( loc );
}

};
};

