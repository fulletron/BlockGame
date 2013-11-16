#include "button.h"
//#include "..\..\Graphics\dxincludes.h"
//#include "..\..\Resource\texture.h"
#include "..\..\Game\game.h"
//#include "..\..\Resource\resourcedictionary.h"

namespace GS { 
namespace EntityNS {
		_UINT32 Button::init(GS::Game * const a_rpGame, void const * const a_data)
		{
			/*
			m_rpGame = a_rpGame;
			// KYLE :: const cast, reinterpret cast?
			Builder_Button * t_pBB = (Builder_Button*)a_data;

			setScale(t_pBB->baseScale);
			setPos(t_pBB->posPerc);
			m_pButtonSays = t_pBB->buttonSays;

			/// KYLE :: DO SOME RESOURCE MAGIC!
			GS::ResourceNS::ScreenTexture* t_pScreenTex = 
				(GS::ResourceNS::ScreenTexture*)m_rpGame->getLibrary()->getEntry(t_pBB->resourceName);

			if(!t_pScreenTex)
			{
				t_pScreenTex = m_rpGame->getLibrary()->loadResource(
					ResourceNS::BUTTON_MENU, 
					t_pScreenTex, 
					&ResourceBuilder(
						GS::Game * a_pGame, 
						_UINT32 a_resourcename, 
						_UWCHAR* a_filename)
		{
			pGame = a_pGame;
			resourcename = a_resourcename;
			filename = a_filename;
		}
				
			}

			m_buttonDimensions = t_pScreenTex->getDesc();

			/// KYLE :: MAKE THIS SMALLER
			_RECT t_rect;
			t_rect.top = 0; 
			t_rect.left = 0;
			t_rect.bottom = (long)m_buttonDimensions.y/3;
			t_rect.right = (long)m_buttonDimensions.x;
			setSrcRect(t_rect);
			*/

			return 0;
		}
		void Button::update(_DOUBLE a_dt)
		{
		}
		void Button::draw()
		{
			
		}
		void Button::shutdown()
		{
		}
		bool Button::input(const GS::InputNS::Input & a_input, bool & a_moDone, bool & a_kbDone)
		{
			return false;
		}
		void Button::resetScale()
		{
		}

		void Button::onScreenResize()
		{
		}

		void Button::entityRescale()
		{
		}

		// IUF BREATHE
		//int getBreatheStepFreq();
		//void breatheUpdate(float dt);
};
};