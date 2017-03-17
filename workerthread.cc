 ///
 /// @file    workerthread.cc
 /// @date    2017-03-16 15:33:07
 ///

#include "workerthread.h"
#include "threadpool.h"

namespace hello{

workerthread::workerthread(threadpool & threadpool)
:_threadpool(threadpool)
{}

void workerthread::run(){
	_threadpool.processtask();
}

}// endof namspace hello



