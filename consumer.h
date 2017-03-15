 ///
 /// @file    consumer.h
 /// @date    2017-03-15 10:45:54
 ///

#ifndef __CONSUMER_H__
#define __CONSUMER_H__

#include "thread.h"

namespace hello{

class buffer;
class consumer
:public thread
{
public: 
	consumer(buffer& buf);
	virtual void run();

private:
	buffer & _buf;
};

}//end of the namespace hello

#endif



