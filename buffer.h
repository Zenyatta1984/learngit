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

class buffer{
public:
	buffer(size_t size);

	void push(int);
	int pop();

	bool empty();
	bool full();

private:
	mutexlock _mutex;

	condition _notfull;
	condition _notempty;

	size_t _size;
	std::queue<int> _que;
};

}//end of the namespace hello

#endif


