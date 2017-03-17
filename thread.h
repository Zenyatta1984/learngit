 ///
 /// @file    thread.h
 /// @date    2017-03-14 20:27:35
 ///

#ifndef __THREAD_H__
#define __THREAD_H__

#include "nocopyable.h"
#include <pthread.h>

namespace hello{

class thread
:private nocopyable
{
public:
	thread();
	virtual ~thread();

	virtual void run()=0;

	void start();
	void join();

	static void* threadfunc(void *arg);

private:
	pthread_t _pthid;
	bool _isrunning;
};

}
//end of the namespace hello
#endif


