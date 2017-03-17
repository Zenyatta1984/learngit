 ///
 /// @file    threadpool.h
 /// @date    2017-03-16 15:16:48
 ///

#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "buffer.h"

#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

namespace hello{

class thread;
class threadpool{
	friend class workerthread;

public:
	threadpool(size_t threadnum,size_t bufsize);
	~threadpool();

	void start();
	void stop();

	void addtask(task*);

private:
	task * gettask();
	void processtask();
private:
	bool _isexit;
	size_t _threadnum;
	size_t _bufsize;
	buffer _buff;
	vector<shared_ptr<thread> > _threads;
};

}//end of namespace hello

#endif


