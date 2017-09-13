#include "definitions_values.h"
#include "definitions_types.h"

// THIS NEEDS TO EXISTS STRICTLY FOR CMAKE

// THIS STRICTLY EXISTS TO SHOW MULTITHREADED FUNCTIONALITY

// THIS IS A TEST
#include <Utilities/thread/thread.h>

//std::mutex g_printout_mutex;
GS::Thread::GSMutex g_printout_mutex;

int printoutEnd(int id)
{
//	std::lock_guard<std::mutex> lock(g_printout_mutex);
	GSLOCKGUARD(g_printout_mutex);
//	g_printout_mutex.gsLock();
	DEBUG_OUT("Thread " << id << " ended");
//	g_printout_mutex.gsUnlock();
	return 0;
}

int test(int id)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	printoutEnd(id);
	return 0;
}

int doThreads(void)
{
	_VECTOR<std::thread *> threads;
	for (int i = 0; i < 1000; ++i)
	{
		{
			GSLOCKGUARD(g_printout_mutex);
			//g_printout_mutex.gsLock();
			DEBUG_OUT("Thread " << i << " started.");
			//g_printout_mutex.gsUnlock();
		}
		std::thread * t = new std::thread(test, i);
		threads.push_back(t);
	}

	for (int i = 0; i < 1000; ++i)
	{
		std::thread * t = threads.at(i);
		if (t->joinable())
		{
			t->join();
			delete t;
		}
	}

	return 0;
}
/*
#include <Windows.h>

#include <Graphics/openglincludes.h>
#include <GLFW/glfw3native.h>

int contextsharetest(void * a_window)
{
	GLFWwindow * window = (GLFWwindow *)a_window;
	HWND hWnd = glfwGetWin32Window(window);
	HDC dc = GetDC(hWnd);
	//HGLRC glrc1 = wglCreateContext(dc);
	HGLRC glrc2 = wglCreateContext(dc);

	bool error = wglShareLists(glfwGetWGLContext(window), glrc2);
	if (error == FALSE)
	{
		DWORD errorCode = GetLastError();
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
		MessageBox(NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION);
		LocalFree(lpMsgBuf);
		//Destroy the GL context and just use 1 GL context
		wglDeleteContext(glrc2);
		DEBUG_OUT_RED("LISTS CANNOT BE SHARED");
	}

	// FROM THE MAIN THREAD
	wglMakeCurrent(dc, glfwGetWGLContext(window));
	// run game here!!!!

	// IN ALL SUBSEQUENT THREADS
	//wglMakeCurrent(dc, glrc2);
	// load textures on the fly!


	return 0;
}
*/