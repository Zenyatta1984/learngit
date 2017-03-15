 ///
 /// @file    testthread.cc
 /// @date    2017-03-15 10:52:32
 ///


#include "buffer.h"
#include "producer.h"
#include "consumer.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

int main(void){
	hello::buffer buffer(10);
	hello::producer mypro(buffer);
	hello::consumer mycon(buffer);

	mypro.start();
	mycon.start();

	mypro.join();
	mycon.join();

	return 0;
}
