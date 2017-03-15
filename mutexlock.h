 ///
 /// @file    mutexlock.h
 /// @date    2017-03-15 09:44:56
 ///

#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__

#include "nocopyable.h"
#include <pthread.h>

namespace hello{

class mutexlock
:nocopyable{
public:
	mutexlock();
	~mutexlock();

	void lock();
	void unlock();

	pthread_mutex_t * getmutexlockptr();

private:
	pthread_mutex_t _mutex;
	bool _islocking;
};

}//end of the namespace hello

#endif 


