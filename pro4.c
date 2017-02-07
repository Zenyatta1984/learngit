#include "../head.h"
void newhandle(int signum,siginfo_t *p,void *q){
	printf("the no.%d signal is coming\n",signum);
}
int main(){
	struct sigaction act;
	act.sa_sigaction=newhandle;
	act.sa_flags=SA_SIGINFO|SA_NODEFER;

	int ret=sigaction(SIGINT,&act,NULL);
	if(-1==ret){
		perror("sigaction");
		return -1;
	}

	//设定全程阻塞函数
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	int ret2;
	ret2=sigprocmask(SIG_BLOCK,&set,NULL);
	if(-1==ret2){
		perror("sigprocmask_block");
		return -1;
	}
	sleep(5);
	
	//检测是否2号是否被挂起
	sigset_t set2;
	sigemptyset(&set2);
	int ret3=sigpending(&set2);
	if(-1==ret3){
		perror("sigpending");
		return -1;
	}
	
	if(sigismember(&set,SIGINT)){
		printf("signal 2 is pending\n");
	}
	else{
		printf("signal 2 si not pending\n");
	}

	int ret4=sigprocmask(SIG_UNBLOCK,&set,NULL);
	if(-1==ret4){
		perror("sigprocmask_unblock");
		return -1;
	}
	return 0;
}
