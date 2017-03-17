 ///
 /// @file    threadpool.cc
 /// @date    2017-03-16 15:26:43
 ///


#include "threadpool.h"
#include "workerthread.h"
#include "task.h"
#include <unistd.h>

namespace hello{

threadpool::threadpool(size_t threadnum,size_t bufsize)
:_isexit(false)
,_threadnum(threadnum)
,_bufsize(bufsize)
,_buff(bufsize)
{
	_threads.reserve(_threadnum);
}

threadpool::~threadpool(){
	if(!_isexit)
		stop();//整个池退出
}

void threadpool::start(){
	for(size_t x=0;x!=_threadnum;++x){

		thread* p=new workerthread(*this);
		shared_ptr<thread> sp(p);
		_threads.push_back(sp);
		sp->start();
	}
}

void threadpool::stop(){
	if(!_isexit){
		while(!_buff.empty()){
			sleep(1);
		}

		_isexit=true;
		_buff.wakeup();
		for(auto &elem :_threads){
			elem->join();
			cout<<"thread's use_count()="<<elem.use_count()<<endl;
		}
		_threads.clear();
	}
}

void threadpool::addtask(task * ptask){
	_buff.push(ptask);
}

task* threadpool::gettask(){
	return _buff.pop();
}

void threadpool::processtask(){
	while(!_isexit){
		task* ptask=gettask();
		if(ptask)
			ptask->execute();
	}
}

}//end of namespace hello

	







