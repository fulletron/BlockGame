#ifndef __GRAPHICS_H_
#define __GRAPHICS_H_

//#include "dxincludes.h"
#include "..\..\Game\definitions.h"
#include "Camera.h"
#include "window.h"
//#include "D3DManager.h"

namespace GS
{ 
	// PROTOTYPE
	class Game;

	namespace GraphicsNS 
	{
		class Graphics
		{
		private:
			GS::Game *					m_rpGame;

			WindowNS::Window	m_baseWindow;
			//D3DManagerNS::D3DManager	m_D3DManager;
			CameraNS::Camera			m_camera;
		
		public:
			Graphics(void){}
			~Graphics(void){}

			_UINT32			init(GS::Game * const a_g);
			//_UINT32		init(const HINSTANCE & a_hInst, GS::Game * const a_g);
			_UINT32			shutdown();

			GETP_ACCESSOR(	WindowNS::Window,	m_baseWindow	);
			//GETP_ACCESSOR(	D3DManagerNS::D3DManager,	m_D3DManager	);
		};

		void render(GS::Game * const a_g);
		//void exitSizeMove(Graphics * const a_graphics);
		//void sizeWMRet(Graphics * const a_graphics, WPARAM wparam, LPARAM lparam);
	};

};

#endif