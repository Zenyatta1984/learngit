 ///
 /// @file    thread.h
 /// @date    2017-03-14 20:27:35
 ///

#ifndef __THREAD_H__
#define __THREAD_H__

#include "nocopyable.h"
#include <pthread.h>
#include <functional>

using std::function;

namespace hello{

class thread
:private nocopyable
{
	typedef function<void()> threadcallback;
public:
	thread(threadcallback cb);
	~thread();

	void start();
	void join();

	static void* threadfunc(void *arg);

private:
	pthread_t _pthid;
	bool _isrunning;
	threadcallback _cb;
};

}
//end of the namespace hello
#endif


