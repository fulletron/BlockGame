#ifndef __RESOURCEFILE_H_
#define __RESOURCEFILE_H_

#include "Game\definitions.h"
#include <Game\define_gettersetter.h>
#include <Library\library.h>

namespace GS { class Game;
namespace ResourceNS {

	enum ETextureFiltering
	{
		TEXTURE_FILTER_MAG_NEAREST = 0,
		TEXTURE_FILTER_MAG_BILINEAR,
		TEXTURE_FILTER_MIN_NEAREST,
		TEXTURE_FILTER_MIN_BILINEAR,
		TEXTURE_FILTER_MIN_NEAREST_MIPMAP,
		TEXTURE_FILTER_MIN_BILINEAR_MIPMAP,
		TEXTURE_FILTER_MIN_TRILINEAR,
	};

	class IResourceFile : public GS::LibraryNS::IEntry
	{
	};
};
};

#endif