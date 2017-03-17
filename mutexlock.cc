 ///
 /// @file    mutexlock.cc
/// @date    2017-03-15 09:51:06
 ///

#include "mutexlock.h"

namespace hello
{

mutexlock::mutexlock()
:_islocking(false)
{
	pthread_mutex_init(&_mutex,NULL);
}

mutexlock::~mutexlock(){
	pthread_mutex_destroy(&_mutex);
}

void mutexlock::lock(){
	_islocking=true;
	pthread_mutex_lock(&_mutex);
}

void mutexlock::unlock(){
	_islocking=false;
	pthread_mutex_unlock(&_mutex);
}

pthread_mutex_t * mutexlock::getmutexlockptr(){
	return &_mutex;
}

}//end of the namespace hello





