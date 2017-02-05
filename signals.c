 ///
 /// @file    signals.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-02-05 16:50:50
 ///
/* 
#include <iostream>
using std::cout;
using std::endl;*/
#include "../head.h"
void func(int kernel_input){
	printf("b4 func been interupted,sig number is %d\n",kernel_input);
	sleep(4);	
	printf("after func been interupted,sig number is %d\n",kernel_input);
}
int main(){
	signal(SIGINT,func);
	signal(SIGQUIT,func);

	while(1);
	return 0;
}
