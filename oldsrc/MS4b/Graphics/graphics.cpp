#include "..\..\Game\game.h"
#include "..\..\Game\inlines.h"

namespace GS {
namespace GraphicsNS
{
	_UINT32 Graphics::shutdown()
	{
		m_camera.shutdown();
		//m_D3DManager.shutdown();
		m_baseWindow.shutdown();
		return 0;
	}

	/*
	_UINT32 Graphics::init(const HINSTANCE & a_hInst, GS::Game * const a_g)
	{
		m_rpGame = a_g;

		DBC(m_baseWindow.init(a_g, a_hInst), L"FAILED :: CANNOT INIT BASE WINDOW");
		//DBC(m_D3DManager.init(&m_baseWindow), L"FAILED :: CANNOT INIT BASE WINDOW");
		DBC(m_camera.init(&m_baseWindow), L"FAILED :: CANNOT INIT BASE WINDOW");

		return 0;
	}
	*/

	_UINT32 Graphics::init(GS::Game * const a_g)
	{
		m_rpGame = a_g;

		DBC(m_baseWindow.init(a_g), "FAILED :: CANNOT INIT BASE WINDOW");
		//DBC(m_D3DManager.init(&m_baseWindow), L"FAILED :: CANNOT INIT BASE WINDOW");
		DBC(m_camera.init(&m_baseWindow), "FAILED :: CANNOT INIT BASE WINDOW");

		return 0;
	}

	void render(GS::Game * const a_g)
	{
		if(!a_g)
			return;

		GS::StateNS::IState * t_pState = a_g->getState();

		if(WindowNS::Window::needsRefresh())
			a_g->getGraphics()->get__m_baseWindow()->retainWindowIntegrity();

		// Clear the screen to black
		//glClearColor( 0.2f, 0.1f, 0.1f, 1.0f );
		glClearColor( 0.33f, 0.33f, 0.33f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glClearDepth(1.0);

		if(t_pState)
			t_pState->render();

		glfwSwapBuffers();
		/*
		IDirect3DDevice9* t_pD3DDevice = a_g->getGraphics()->get__m_D3DManager()->get__m_pD3DDevice();
		static GS::StateNS::IState * s_pState = s_pState = a_g->getState();
		// If the device was not created successfully, return
		if(!t_pD3DDevice)
			return;

		// Clear the back buffer, call BeginScene()
		if(SUCCEEDED(t_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 1.0f, 0)))
		{
			if(SUCCEEDED(t_pD3DDevice->BeginScene()))
			{
				if(s_pState)
					s_pState->render();
				// EndScene, and Present the back buffer to the display buffer
				t_pD3DDevice->EndScene();
			}
			t_pD3DDevice->Present(0, 0, 0, 0);
		}
		*/
	}
};
};