 ///
/// @file    producer.h
 /// @date    2017-03-15 09:38:07
 ///

#ifndef __PRODUCER_H__
#define __PRODUCER_H__

#include "thread.h"

namespace hello{

class buffer;
class producer
:public thread
{
public:
	producer(buffer&);
	virtual void run();

private:
	buffer & _buf;
};

}//end of the namespace hello

#endif


