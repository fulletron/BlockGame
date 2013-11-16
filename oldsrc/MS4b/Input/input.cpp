#include <Game\game.h>

namespace GS{
namespace InputNS{
	typedef enum
	{
		NOT_CLICKED = 0,
		JUST_CLICKED = 1,
		HELD = 2,
		JUST_RELEASED = 3
	}PRESS_STATE;

	_UINT32 Input::init(GS::Game * const a_g)
	{
		m_pGame = a_g;

		//GS::WindowNS::Window * t_rpWindow = m_pGame->getGraphics()->get__m_baseWindow();

		resetInput();

		return 0;
	}

	void Input::grabInput()
	{
		__grabKeyboard();
		__grabMouse();
		resetHandlingInput();
	}

	void Input::__grabKeyboard(void)
	{
		for(int i = 0; i < m_sfKeyboard.KeyCount; ++i)
		{
			if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i))
			{
				if(m_keyboard.keyState[i] == NOT_CLICKED)
					m_keyboard.keyState[i] = JUST_CLICKED;
				else if(m_keyboard.keyState[i] == JUST_CLICKED)
					m_keyboard.keyState[i] = HELD;
			}
			else
			{
				if(m_keyboard.keyState[i] == JUST_CLICKED
				|| m_keyboard.keyState[i] == HELD)
					m_keyboard.keyState[i] = JUST_RELEASED;
				else
					m_keyboard.keyState[i] = NOT_CLICKED;
			}
		}
	}

	void Input::__grabMouse()
	{

		for(int i = 0; i < m_sfMouse.ButtonCount; ++i)
		{
			if(sf::Mouse::isButtonPressed((sf::Mouse::Button)i))
			{
				if(m_mouse.mouseButton[i] == NOT_CLICKED)
					m_mouse.mouseButton[i] = JUST_CLICKED;
				else if(m_mouse.mouseButton[i] == JUST_CLICKED)
					m_mouse.mouseButton[i] = HELD;
			}
			else
			{
				if(m_mouse.mouseButton[i] == JUST_CLICKED
				|| m_mouse.mouseButton[i] == HELD)
					m_mouse.mouseButton[i] = JUST_RELEASED;
				else
					m_mouse.mouseButton[i] = NOT_CLICKED;
			}
		}

		int mouseX, mouseY;
		glfwGetMousePos( &mouseX, &mouseY );
		m_mouse.mousePos.x = static_cast<float>(mouseX);
		m_mouse.mousePos.y = static_cast<float>(mouseY);
	}

	_2DFLOATVEC Input::getMousePos()
	{
		return m_mouse.mousePos;
	}

	void Input::resetInput()
	{
		for (int i = 0; i < sizeof(m_keyboard.keyState); ++i)
		{
			m_keyboard.keyState[i] = NOT_CLICKED;
		}

		for (int i = 0; i < sizeof(m_mouse.mouseButton); ++i)
			m_mouse.mouseButton[i] = false;
	}

	void Input::shutdown()
	{
	}
};
};