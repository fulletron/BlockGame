#ifndef __THREAD_GLFW_H_
#define __THREAD_GLFW_H_

#include <Graphics/openglincludes.h>

#ifdef USING_GLFW

#include <thread>
#include <mutex>

namespace GS {
namespace Thread {

class GSMutex_GLFW : public std::mutex {
public:
	inline GSMutex_GLFW()
	{
		std::mutex();
	}

	inline void gsLock()
	{
		lock();
	}

	inline void gsUnlock()
	{
		unlock();
	}
	inline void gsLockGuard()
	{
		// THIS DOESNT WORK
		std::lock_guard<std::mutex> lock(*this);
	}
};

/*
class GSThread_GLFW : public std::thread {
};
typedef GSThread_GLFW GSThread;
*/


typedef std::thread GSThread;
typedef GSMutex_GLFW GSMutex;

#define GSLOCKGUARD(x) std::lock_guard<std::mutex> lock(x)

//inline void GSLockGuard(std::mutex a_mutex)
//{
//	std::lock_guard<std::mutex> lock(a_mutex);
//}

};
};

#endif
#endif