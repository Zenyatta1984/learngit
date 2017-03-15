 ///
 /// @file    condition.cc
 /// @date    2017-03-15 09:44:28
 ///

#include "condition.h"
#include "mutexlock.h"

namespace hello{

condition::condition(mutexlock& mutex)
:_mutex(mutex)
{
	pthread_cond_init(&_cond,NULL);
}

condition::~condition(){
	pthread_cond_destroy(&_cond);
}

void condition::wait(){
	pthread_cond_wait(&_cond,_mutex.getmutexlockptr());
}

void condition::notify(){
	pthread_cond_signal(&_cond);
}

void condition::notifyall(){
	pthread_cond_broadcast(&_cond);
}

}//end of namespace hello

