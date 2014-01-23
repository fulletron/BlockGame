#include "window.h"
#include "..\..\Input\input.h"
#include "..\..\Game\game.h"

namespace GS{
namespace WindowNS
{
	bool Window::sm_needsWindowRefresh = false;

	void Window::shutdown()
	{
		glfwCloseWindow();
	}

	GLint Window::_maintainAspectRatio(GLint a_width, GLint a_height)
	{
		float tempAspectRatio = ((GLfloat)a_width / (GLfloat)a_height);
		float aspectRatio = 0.0f;
		float aspectRatioInverse = 0.0f;

		if(tempAspectRatio < 1.46f) // 4/3 RATIO
		{
			//aspectRatio = 4.0f/3.0f;
			aspectRatioInverse = 3.0f/4.0f;
		}
		else if (tempAspectRatio < 1.69f) // 16/10 RATIO
		{
			//aspectRatio = 16.0f/10.0f;
			aspectRatioInverse = 10.0f/16.0f;
		}
		else // 16/9 RATIO
		{
			//aspectRatio = 16.0f/9.0f;
			aspectRatioInverse = 9.0f/16.0f;
		}

		return (GLint)(a_width * aspectRatioInverse);
	}

	void Window::retainWindowIntegrity()
	{
		GLint t_screenWidth = 0, t_screenHeight = 0;
		glfwGetWindowSize(&t_screenWidth, &t_screenHeight);
		glViewport(0, 0, t_screenWidth, t_screenHeight);

		m_windowScreen.set(_RECT<_INT32>(0,0,t_screenWidth, t_screenHeight), _RECT<_FLOAT>(0.5f,0.5f,1.0f,1.0f),ALIGN_CENTER);

		sm_needsWindowRefresh = false;
		if(get__m_rpGame())
			if(get__m_rpGame()->getState())
				get__m_rpGame()->getState()->onScreenResize();
	}

	void GLFWCALL Window::_windowResizeFunction(GLint a_width, GLint a_height)
	{
		GLint t_width = a_width;
		GLint t_height = a_height;

		if(t_width < 800)
		{
			t_height = 600;
			t_width = 800;
		}
		t_height = _maintainAspectRatio(t_width,t_height);
		glfwSetWindowSize(t_width, t_height);
		glfwSetWindowTitle(WINDOW_NAME);
		sm_needsWindowRefresh = true;
	}

	_UINT32 Window::init(GS::Game * const a_pGame)
	{
		m_rpGame = a_pGame;
		sm_needsWindowRefresh = false;

		// ================================ INIT STAGE =====================================
		if(!glfwInit())
			exit( EXIT_FAILURE );

		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);

		/// SOIL USES DEPRECATED CALLS(IN CERTAIN FUNCTIONS). IT IS POSSIBLE YOU WILL NOT BE ABLE TO FORWARD COMPAT!
		glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 8);

		GLFWvidmode return_struct;

		glfwGetDesktopMode( &return_struct );

		//if(!glfwOpenWindow( return_struct.Width, return_struct.Height, 0, 0, 0, 0, 32, 0, GLFW_FULLSCREEN))
		if(!glfwOpenWindow( SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 0, 32, 8, GLFW_WINDOW ) )
		{
			glfwTerminate();
			return -1;
		}

		glfwSetWindowSizeCallback( _windowResizeFunction );
		glfwSwapInterval(0);
		// Initialize GLEW
		glewExperimental = GL_TRUE;
		glewInit();
		// ===============================================================================
		/// KYLE :: glewInit() returns some kind of error 1280 Invalid_enum
		GLenum error = glGetError();
		error = glGetError();
		return 0;
	}


	_RECT<_INT32> GetPXRectFromWindow(GS::Game * const a_rpGame,				
							const ALIGNMENT & a_alignment, 
							const _RECT<_FLOAT> & a_slice)
	{
		GS::WindowNS::Window * t_pBW = a_rpGame->getGraphics()->get__m_baseWindow();
		return GetPXRectFromWindow(t_pBW, a_alignment, a_slice);
	}

	_RECT<_INT32> GetPXRectFromWindow(GS::WindowNS::Window * const a_pBW,
							const ALIGNMENT & a_alignment, 
							const _RECT<_FLOAT> & a_slice)
	{
		_RECT<_INT32> t_windowRect = a_pBW->get__m_windowScreen()->m_pxRect;

		_RECT<_INT32> returnable(0,0,0,0);

		float t_aspectRatioMulti = (4.0f/3.0f) * (float)(  t_windowRect.height / t_windowRect.width );

		switch (a_alignment)
		{
			case ALIGN_CENTER:
				returnable.set(
					(_INT32)(a_slice.left * t_windowRect.width) - (_INT32)((0.50f * a_slice.width * t_windowRect.width) * (t_aspectRatioMulti / 1.0f)),
					(_INT32)(a_slice.bottom * t_windowRect.height) - (_INT32)(0.50f * a_slice.height * t_windowRect.height),
					(_INT32)((a_slice.width * t_windowRect.width) * t_aspectRatioMulti), 
					(_INT32)(a_slice.height * t_windowRect.height));
				break;

				/*
			case ALIGN_LEFT:
				returnable.set(
					(_INT32)(a_slice.left * t_windowRect.width) - (_INT32)((0.50f * a_slice.width * t_windowRect.width) * (t_aspectRatioMulti / 1.0f)),
					(_INT32)(a_slice.bottom * t_windowRect.height) - (_INT32)(1.00f * a_slice.height * t_windowRect.height),
					(_INT32)((a_slice.width * t_windowRect.width) * t_aspectRatioMulti), 
					(_INT32)(a_slice.height * t_windowRect.height));
				break;

			case ALIGN_RIGHT:
				returnable.set(
					(_INT32)(a_slice.left * t_windowRect.width) - (_INT32)((0.50f * a_slice.width * t_windowRect.width) * (t_aspectRatioMulti / 1.0f)),
					(_INT32)(a_slice.bottom * t_windowRect.height) - (_INT32)(1.00f * a_slice.height * t_windowRect.height),
					(_INT32)((a_slice.width * t_windowRect.width) * t_aspectRatioMulti), 
					(_INT32)(a_slice.height * t_windowRect.height));
				break;
				*/

			default:
				break;
		};
		return returnable;
	}

	_RECT<_INT32> GetPXRectFromRect(const _RECT<_FLOAT> & a_slice, 
							const ALIGNMENT & a_alignment, 
							const _RECT<_INT32> & a_frame)
	{
		_RECT<_INT32> returnable(0,0,0,0);

		switch(a_alignment)
		{
			case ALIGN_CENTER:
				returnable.set(
					(_INT32)(a_slice.left * a_frame.width) - (_INT32)(0.50f * a_slice.width * a_frame.width),
					(_INT32)(a_slice.bottom * a_frame.height) - (_INT32)(0.50f * a_slice.height * a_frame.height),
					(_INT32)(a_slice.width * a_frame.width), 
					(_INT32)(a_slice.height * a_frame.height)
					);
				break;

			default:
				break;
		}

		return returnable;
	}
};
};