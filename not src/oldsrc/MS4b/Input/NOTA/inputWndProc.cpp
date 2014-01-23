/*

#include "input.h"
#include "..\..\Game\game.h"

namespace GS{
namespace InputNS
{
	LRESULT CALLBACK Input::WndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
	{
		static GS::Game * m_rpGame = 0;
		if(!m_rpGame) 
			m_rpGame = (GS::Game *)GetProp(hWnd, L"Game");

		// attempt to handle your messages
		switch(message)
		{
			case (WM_PAINT):
			{
				InvalidateRect(hWnd,NULL,TRUE);
				break;
			}		

			case(WM_DESTROY):
			{
				PostQuitMessage(0);
				m_rpGame->flagForQuit();
				break;
			}
			case(WM_SIZING):
			{
				GS::BaseWindowNS::maintainAspectRatio(m_rpGame->getGraphics()->get__m_baseWindow(), wparam,lparam);
				break;
			}
			case(WM_SIZE):
			{	
				GS::D3DManagerNS::sizeWMRet(m_rpGame->getGraphics()->get__m_D3DManager(), wparam, lparam);
				return 0;
			}
			case(WM_EXITSIZEMOVE):
			{
				GS::D3DManagerNS::exitSizeMove(m_rpGame->getGraphics()->get__m_D3DManager());
				return 0;
			}
			case(WM_KEYDOWN):
			{
				switch(wparam)
				{
					// Escape Key will close the application
					// Remove/Modify this call when creating a real game with menus, etc.
					case VK_ESCAPE:
					{
						PostQuitMessage(0);
						m_rpGame->flagForQuit();
						break;
					}
				}
			}

			case(WM_SYSKEYUP):
			{
				case VK_LMENU:
				case VK_RMENU:
				return NULL; 
			}

			case (WM_GETMINMAXINFO):
			{
				LPMINMAXINFO lpMMI;
				lpMMI = reinterpret_cast<LPMINMAXINFO>( lparam );
				lpMMI->ptMinTrackSize.x = MINIMUM_WIDTH;
				lpMMI->ptMinTrackSize.y = MINIMUM_HEIGHT;

				break;
			}

		}
		return DefWindowProc(hWnd, message, wparam, lparam);
	}
};
};

*/