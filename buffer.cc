 ///
 /// @file    buffer.cc
 /// @date    2017-03-15 10:10:41
 ///

#include "buffer.h"
#include <iostream>

using std::cout;
using std::endl;


namespace hello{
	
buffer::buffer(size_t size)
:_mutex()
,_notfull(_mutex)
,_notempty(_mutex)
,_size(size)
{}

bool buffer::empty(){
	return _que.size()==0;
}

bool buffer::full(){
	return _que.size()==_size;
}

void buffer::push(int number){
	_mutex.lock();
	while(full()){
		_notfull.wait();
	}

	_que.push(number);
	_notempty.notify();//激活睡眠的线程
	_mutex.unlock();
}

int buffer::pop(){
	_mutex.lock();
	while(empty()){
		_notempty.wait();
	}
	
	int ret=_que.front();
	_que.pop();

	_notfull.notify();
	_mutex.unlock();

	return ret;
}
}
//end of the namespace hello





