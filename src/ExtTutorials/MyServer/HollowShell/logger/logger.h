#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>
#include <mutex>
#include <strstream>

template <class T>
std::string toString(T num)
{
	std::string strNum = "";

	{
		std::strstream buf;
		buf << num << std::ends;
		strNum = buf.str();
		buf.freeze(false);
	}

	return strNum;

	//lint -e{818} parameter num could be declared as a pointer to const
}



/*
#include <tchar.h>
#include <strstream>

//#ifdef _UNICODE
//typedef std::wstring _tstring;
//#else
typedef std::string _tstring;
//#endif

template <class T>
_tstring ToString(T num)
{
	_tstring strNum = _T("");

	{
		std::strstream buf;

		buf << num << std::ends;

//#ifdef _UNICODE
//		std::string temp = buf.str();
//
//		USES_CONVERSION;
//
//		strNum = A2W(temp.c_str());
#//else 
		strNum = buf.str();
//#endif
		buf.freeze(false);
	}

	return strNum;

	//lint -e{818} parameter num could be declared as a pointer to const
}
*/
class Logger
{
private:
	std::mutex m_lock;
public:
	void log(int a_color, std::string a_str);
	//void log_t(const _tstring &msg);

// SINGLETON IMPLEMENTATION
public:
	static Logger& get()
	{
		static Logger    instance;
		return instance;
	}
private:
	Logger() {}
	Logger(Logger const&);              // Don't Implement.
	void operator=(Logger const&); // Don't implement
};

#endif