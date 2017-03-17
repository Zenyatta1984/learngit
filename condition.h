 ///
 /// @file    condition.h
 /// @date    2017-03-15 09:39:34
 ///

#ifndef __CONDITION_H__
#define __CONDITION_H__

#include "nocopyable.h"
#include <pthread.h>


namespace hello{

class mutexlock;

class condition
:nocopyable 
{
public:
	condition(mutexlock & mutex);
	~condition();

	void wait();
	void notify();
	void notifyall();

private:
	pthread_cond_t _cond;
	mutexlock & _mutex;
};

}//end of the namespace hello

#endif 
