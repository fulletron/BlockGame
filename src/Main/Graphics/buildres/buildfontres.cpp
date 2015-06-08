#include <Graphics/reslib.h>

namespace GS {
namespace Graphics {

FontResource * ResourceLibrary::__buildFontRes( const _INT64 a_name )
{
	FontResource * newRes = new FontResource();

	switch(a_name)
	{
	case CV8::RES_FONT_KASHSCRIPT_16:
		newRes->loadFile( "KaushanScript-Regular.otf", 16);
		break;
	case CV8::RES_FONT_KASHSCRIPT_64:
		newRes->loadFile( "KaushanScript-Regular.otf", 64);
		break;
	default: return 0; 
	}

	newRes->assignName( a_name );
	newRes->assignType( ResourceLibrary::FONT );
	newRes->addCount();
	m_pFontResources.push_back( newRes );
	return newRes;
}

};
};

