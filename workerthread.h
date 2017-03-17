 ///
 /// @file    workerthread.h
 /// @date    2017-03-16 15:27:47
 ///

#ifndef __WORKERTHREAD_H__
#define __WORKERTHREAD_H__

#include "thread.h"
#include <iostream>
using std::endl;
using std::cout;

namespace hello{

class threadpool;

class workerthread
:public thread
{
public:
	workerthread(threadpool & threadpool);
	void run();

	~workerthread(){
		cout<<"~workerthread"<<endl;
	}

private:
	threadpool & _threadpool;
};

}//endof namespace hello

#endif


