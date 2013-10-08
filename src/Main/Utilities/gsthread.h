#ifndef __GSTHREAD_H_
#define __GSTHREAD_H_

#include "typedefinitions.h"
#include <boost/thread.hpp>

namespace GS {
namespace Utilities {

class GSThread
{
private:
public:
	boost::thread m_thread;
	int test();
};

};
};

#endif
