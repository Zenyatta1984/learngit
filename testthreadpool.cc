 ///
 /// @file    testthread.cc
 /// @date    2017-03-15 10:52:32
 ///

#include "threadpool.h"
#include "task.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;

class mytask
:public hello::task

{
public:
	void execute(){
		::srand(::time(NULL));
		int number=::rand() % 100;
		cout<<"number="<<number<<endl;
	}
};

int main(void){
	shared_ptr<hello::task> sp(new mytask);
	hello::threadpool threadpool(4,10);
	threadpool.start();

	int cnt=5;
	while(cnt--){
		threadpool.addtask(sp.get());
		sleep(1);
	}

	threadpool.stop();

	return 0;
}
