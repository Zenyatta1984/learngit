 ///
 /// @file    thread.cc
 /// @date    2017-03-14 20:35:44
 ///


#include "thread.h"
#include <iostream>
using std::cout;
using std::endl;

namespace hello{

thread::thread(threadcallback cb)
:_pthid(0)
,_isrunning(false)
,_cb(cb)
{}

void thread::start(){
	pthread_create(&_pthid,NULL,threadfunc,this);
	_isrunning=true;
}

void thread::join(){
	if(_isrunning){
		pthread_join(_pthid,NULL);
		_isrunning=false;
	}
}

void* thread::threadfunc(void *arg){
	thread * p=static_cast<thread*>(arg);
	if(p)
		p->_cb();
	return NULL;
}

thread::~thread(){
	if(_isrunning){
		pthread_detach(_pthid);
		_isrunning=false;
	}

}



}//end of the namespace hello
