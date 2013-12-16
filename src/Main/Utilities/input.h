#ifndef __INPUT_H_
#define __INPUT_H_

#include <Graphics/openglincludes.h>
#include <Utilities/typedefinitions.h>
#include <Utilities/gsvector.h>

namespace GS {
	namespace Graphics { class Window; };
namespace Utilities {

class Input {

#ifdef TEST_ENABLED
public:
#else
private:
#endif
public:
	struct Press {
		int keybutton;
		int action;
		int mods;

		Press(){}
		~Press(){}

		Press(int a_keybutton, int a_action, int a_mods)
		{
			keybutton = a_keybutton;
			action = a_action;
			mods = a_mods;
		}
	};

	class InputDeck {
	public:
		InputDeck(){}
		~InputDeck(){}

		double m_x, m_y, m_scrollX, m_scrollY;
		GS::Utilities::LimitedVector16<Press> m_presses;
		char m_mods;

		void wipe()
		{
			m_x = 0;
			m_y = 0;
			m_scrollX = 0;
			m_scrollY = 0;
			m_mods = 0;
			m_presses.clean();
		}
	};

	static Input * s_pInput;
	static InputDeck * s_pInputDeck;
	InputDeck inputDeck;

	static void mousePosCB(GLFWwindow * a_pGLFWwindow, double a_x, double a_y){s_pInputDeck->m_x = a_x; s_pInputDeck->m_y = a_y;}
	static void keyCB(GLFWwindow * a_pGLFWwindow, int a_key, int a_scancode, int a_action, int a_mods){s_pInputDeck->m_presses.add(Press(a_key, a_action, a_mods));}
	static void mouseClickCB(GLFWwindow * a_pGLFWwindow, int a_button, int a_action, int a_mods){s_pInputDeck->m_presses.add(Press(a_button, a_action, a_mods));}
	static void scrollCB(GLFWwindow * a_pGLFWwindow, double a_xOffset, double a_yOffset){s_pInputDeck->m_scrollX = a_xOffset; s_pInputDeck->m_scrollY = a_yOffset;}

	_INT32 init(GS::Graphics::Window * a_pWindow);

	static void wipe(){s_pInputDeck->wipe();}
};

};
};

#endif