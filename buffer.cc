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
,_flag(true)
{}

bool buffer::empty(){
	return _que.size()==0;
}

bool buffer::full(){
	return _que.size()==_size;
}

void buffer::push(ElemType elem){

	mutexlockguard guard(_mutex);
	while(full()){
		_notfull.wait();
	}

	_que.push(elem);
	_notempty.notify();//激活睡眠的线程
}

ElemType buffer::pop(){
	
	mutexlockguard guard(_mutex);
	while(_flag && empty()){
		_notempty.wait();
	}
	
	if(_flag){
		ElemType ret=_que.front();
		_que.pop();

		_notfull.notify();
		return ret;
	}
	else{
		return NULL;
	}
}

void buffer::wakeup(){
	_flag=false;
	_notempty.notifyall();
}

}//end of the namespace hello





