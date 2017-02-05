 ///
 /// @file    main.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-02-05 16:42:56
 ///
/* 
#include <iostream>
using std::cout;
using std::endl;*/
#include "../head.h"
void func(int kernal_input){
	printf("the sig num=%d\n",kernal_input);
}

int main(){
	if(SIG_ERR==signal(SIGINT,func)){
		perror("signal");
		return -1;
	}
	
	while(1);
	return 0;
}
