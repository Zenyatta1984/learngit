 ///
 /// @file    testthread.cc
 /// @date    2017-03-14 20:45:34
 ///


#include "thread.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using std::cout;
using std::endl;

class producer
{
public:
	 void func(){
		int cnt=20;
		srand(time(NULL));
		while(cnt--){
			int number=rand()%100;
			cout<<"number="<<number<<endl;
			sleep(1);
		}
	}
};

int main(void){

	hello::thread thread(std::bind(&producer::func,producer()));
	thread.start();
	thread.join();

	return 0;
}
