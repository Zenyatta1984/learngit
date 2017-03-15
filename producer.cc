 ///
 /// @file    producer.cc
 /// @date    2017-03-15 10:39:09
 ///

#include "producer.h"
#include "buffer.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using std::cout;
using std::endl;

namespace hello{

producer::producer(buffer& buf)
:_buf(buf)
{}

void producer::run(){
	::srand(::time(NULL));
	while(1){
		int number=::rand()%100;
		_buf.push(number);
		cout<<"produce a number: "<<number<<endl;
		sleep(2);
	}
}

}//end of the namespace hello
