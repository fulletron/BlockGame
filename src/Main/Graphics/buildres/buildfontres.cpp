#include <Graphics/reslib.h>

namespace GS {
namespace Graphics {

FontResource * ResourceLibrary::__buildFontRes( const _INT64 a_name )
{
	FontResource * newRes = new FontResource();

	switch(a_name)
	{
	case CV8::RES_FONT_KASHSCRIPT:
		newRes->loadFile( "KaushanScript-Regular.otf", 16);
		break;
	default: return 0; 
	}

	newRes->assignName( a_name );
	newRes->addCount();
	m_pFontResources.push_back( newRes );
	return newRes;
}

};
};

