 ///
 /// @file    consumer.cc
 /// @date    2017-03-15 10:48:39
 ///

#include "consumer.h"
#include "buffer.h"

#include <unistd.h>

#include <iostream>

using std::cout;
using std::endl;

namespace hello{

consumer::consumer(buffer & buf)
:_buf(buf)
{}

void consumer::run(){
	while(1){
		int number= _buf.pop();
		cout<<"---consumer a number:"<<number<<endl;
		sleep(1);
	}
}

}//end of the namespace hello











