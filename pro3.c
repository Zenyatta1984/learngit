 ///
 /// @file    main.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-02-06 23:06:58
 ///
/* 
#include <iostream>
using std::cout;
using std::endl;*/
#include "../head.h"
void newhandle(int signum,siginfo_t* p, void *q){
	printf("the signal no.%d si coming\n",signum);
	//屏蔽
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGQUIT);
	sigprocmask(SIG_BLOCK,&set,NULL);
	printf("after been blocked, now goto sleep\n");
	sleep(3);

	//判断新来的3号信号是否被挂起
	sigset_t set2;
	sigemptyset(&set2);
	sigpending(&set2);
	if(sigismember(&set2,SIGQUIT)){
		printf("signal 3 is pending while signal 2 is sleeping\n");
	}else{
		printf("signal 3 is not pending!\n");
	}
	
	//解除屏蔽
	sigprocmask(SIG_UNBLOCK,&set,NULL);
	printf("signal 3 isnot blocked now\n");
}


int main(){
	struct sigaction act;
	act.sa_sigaction=newhandle;
	act.sa_flags=SA_SIGINFO|SA_RESTART;

//	act.sa_mask
	int ret1=sigaction(SIGINT,&act,NULL);
	if(-1==ret1){
		perror("sigaction");
		return -1;
	}

	while(1);
	return 0;
}

