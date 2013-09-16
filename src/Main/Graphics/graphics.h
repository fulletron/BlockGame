#ifndef __GRAPHICS_H_
#define __GRAPHICS_H_

#include "openglincludes.h"
#include <Utilities/typedefinitions.h>

namespace GS
{ 
	// PROTOTYPE
	class Game;

	namespace GraphicsNS
	{
		class Graphics
		{
		private:
		public:
			Graphics(void){}
			~Graphics(void){}

			//_UINT32			init(GS::Game * const a_g);
			_UINT32			shutdown();
		};
	};

};

#endif