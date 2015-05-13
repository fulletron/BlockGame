#ifndef __GSTHREAD_H_
#define __GSTHREAD_H_

#include "typedefinitions.h"
#include <boost/thread.hpp>

namespace GS {
namespace Utilities {

namespace BT {

typedef boost::thread_group GSThreadGroup;
typedef boost::thread GSThread;
typedef boost::mutex GSMutex;

#define GSThisThread boost::this_thread
#define GSBind boost::bind
#define GSCref boost::cref
#define GSLock boost::lock
#define GSRef boost::ref
};
/*

class GSThread
{
private:
public:
	boost::thread m_thread;
	int test();
};

*/

};
};

#endif
