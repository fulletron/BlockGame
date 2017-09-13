#ifndef __BACKLOADER_H_
#define __BACKLOADER_H_

#include <Utilities/definitions_values.h>
#include <Graphics/openglincludes.h>
#include <Graphics/window/window.h>
#include <Utilities/thread/thread.h>

#ifdef USING_GLFW
#ifdef _WIN32
#include <Windows.h>
#include <GLFW/glfw3native.h>
#endif
#endif

namespace GS {
namespace Backloader {

class Backloader {
selective:
	_VECTOR<GS::Thread::GSThread *> m_pThreads;

	GS::Graphics::Window * m_pWindow;
#ifdef _WIN32
	HGLRC m_hglrc_loader;
	HDC m_dc;
#endif


selective:
	/*
	* WORKER THREAD FUNCTION
	*/
	void loadSomething(int a_test)
	{
#ifdef _WIN32
		// bind thread to certain context
		wglMakeCurrent(m_dc, m_hglrc_loader);
#endif
		return;
	}

public:
	_UINT32 init(GS::Graphics::Window * a_pWindow)
	{
#ifdef USING_GLFW
#ifdef _WIN32
		m_dc = 0;
		m_hglrc_loader = 0;
		m_pWindow = a_pWindow; // MIGHT COME IN USEFUL LATER, I CAN ALWAYS DELETE IT
		GLFWwindow * window = a_pWindow->getGLFWwindow();
		HWND hWnd = glfwGetWin32Window(window);
		m_dc = GetDC(hWnd);
		//HGLRC glrc1 = wglCreateContext(dc);
		m_hglrc_loader = wglCreateContext(m_dc);

		bool error = wglShareLists(glfwGetWGLContext(window), m_hglrc_loader);
		if (error == FALSE)
		{
			DWORD errorCode = GetLastError();
			LPVOID lpMsgBuf;
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
			MessageBox(NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION);
			LocalFree(lpMsgBuf);
			//Destroy the GL context and just use 1 GL context
			wglDeleteContext(m_hglrc_loader);
			DEBUG_OUT_RED("LISTS CANNOT BE SHARED");
		}

		// FROM THE MAIN THREAD
		wglMakeCurrent(m_dc, glfwGetWGLContext(window));
		// run game here!!!!

		// IN ALL SUBSEQUENT THREADS
		//wglMakeCurrent(dc, glrc2);
		// load textures on the fly!
#endif
#endif

		return 0;
	}


	/*
	* CALLED FROM MAIN THREAD
	* spawns a thread with data a_test
	*/
	void spawn(int a_test)
	{
		GS::Thread::GSThread * t = new GS::Thread::GSThread(&Backloader::loadSomething, this, a_test);
		m_pThreads.push_back(t);
	}

	/*
	* CALLED FROM MAIN THREAD
	* cleans up all loader threads that are done
	*/
	void joinFinishedThreads()
	{
		for (_VECTOR<GS::Thread::GSThread *>::iterator iter = m_pThreads.begin(); iter < m_pThreads.end();)
		{
			GS::Thread::GSThread * t = (*iter);
			if (t->joinable())
			{
				t->join();
				iter = m_pThreads.erase(iter);
				delete t;
			}
			else
				iter++;
		}
	}

	_UINT32 shutdown()
	{
#ifdef _WIN32
		wglDeleteContext(m_hglrc_loader);
#endif
		return 0;
	}
};

};
};

#endif
