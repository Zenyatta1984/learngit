 ///
 /// @file    sigaciton.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-02-06 22:39:16
 ///
/* 
#include <iostream>
using std::cout;
using std::endl;*/
#include "../head.h"
void newhandle(int signum,siginfo_t *p,void *q){
	printf("the signal no.%d is coming\n",signum);
	sleep(3);
	printf("after sleep, no%d is leaving\n",signum);
}


int main(){
	struct sigaction act1;
	memset(&act1,0,sizeof(act1));
	
	act1.sa_sigaction=newhandle;
	act1.sa_flags=SA_NODEFER|SA_SIGINFO;

	int ret=sigaction(SIGINT,&act1,NULL);
	if(-1==ret){
		perror("sigaction");
		return -1;
	}
	while(1);
	return 0;
}
