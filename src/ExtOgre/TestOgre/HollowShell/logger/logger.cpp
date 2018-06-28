#include "logger.h"
#include <thread>
#include <iostream>
#include <Windows.h>

void Logger::log(int a_color, std::string a_str)
{
	std::lock_guard<std::mutex> lock(m_lock);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a_color);

	std::thread::id this_id = std::this_thread::get_id();

	std::cout << this_id << ": " << a_str << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
}
/*
void Logger::log_t(const _tstring &msg)
{
#ifdef _DEBUG
	std::lock_guard<std::mutex> lock(m_lock);

//#ifdef _UNICODE
//	std::wcout << ToString(GetCurrentThreadId()) << _T(": ") << msg << std::endl;
//#else
	std::cout << ToString(GetCurrentThreadId()) << _T(": ") << msg << std::endl;
//#endif

	const _tstring msg = ToString(GetCurrentThreadId()) + _T(": ") + msg + _T("\n");

	OutputDebugString(msg.c_str());

	if (!s_debugOut.is_open())
	{
		s_debugOut.open(s_logFileName.c_str(), std::ios_base::out | std::ios_base::app);

		s_debugOut << _T("****************New Log*****************") << endl;
	}

	s_debugOut << ToString(GetCurrentThreadId()) << _T(": ") << message << endl;

#else
	//lint -e{715} symbol 'message' not referenced
#endif //_DEBUG
}
*/