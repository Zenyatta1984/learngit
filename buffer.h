 ///
 /// @file    buffer.h
 /// @date    2017-03-15 09:38:33
 ///


#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "mutexlock.h"
#include "condition.h"
#include <queue>

namespace hello{

class task;
typedef task* ElemType;

class buffer{
public:
	buffer(size_t size);

	void push(ElemType elem);
	ElemType pop();

	void wakeup();

	bool empty();
	bool full();

private:
	mutexlock _mutex;

	condition _notfull;
	condition _notempty;//只有满足这个条件才激活条件变量

	size_t _size;
	std::queue<ElemType> _que;
	bool _flag;
};

}//end of the namespace hello

#endif 
