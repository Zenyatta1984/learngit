 ///
 /// @file    interupted_by_new_sig.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-02-06 22:24:07
 ///
/* 
#include <iostream>
using std::cout;
using std::endl;*/
#include "../head.h"
int count=0;
void newhandle (int signum){
	int this_count=++count;
	printf("%d's time enter newhandle,signo:%d\n",this_count, signum);
	sleep(3);
	printf("%d's time enter newhandle,signo:%d\n",this_count, signum);
}
int main(){
	if(SIG_ERR==signal(SIGINT,newhandle)){
		perror("signal");
		return -1;
	}
	while(1);
	return 0;
}

