#include "../head.h"
int pid1;
int pid1_w;

void ifgetsig (int signum){
	time_t t;		
	int shmid ;
	shmid=shmget(1231,1<<20,IPC_CREAT|0666);

		 char *p;
		 p=(char*)shmat(shmid,NULL,0);
		 if(p==(char*)-1){
			perror("shmat");
			return ;
		 }
	
		 printf("--------------------------------\n");
		 time(&t);
		 printf("%s\n",ctime(&t));
	if(10==signum){
		 printf("USER1	%s\n",p);
	}
	else if(12==signum){
		printf("USER2	%s\n",p);
	}else{printf("signum error!\n");}

		 printf("--------------------------------\n");
}
void sigHandler(int signum){
	
		if(SIG_ERR==signal(10,ifgetsig)){
			printf("error signal 10!\n");
			return -1;
		}
		if(SIG_ERR==signal(12,ifgetsig)){
			printf("error signal 12!\n");
			return -1;
		}
}

void InitTime(int tv_sec,int tv_usec){
	signal(SIGALRM,sigHandler);
	alarm(0);
	struct itimerval tm;
	tm.it_value.tv_sec=tv_sec;
	tm.it_value.tv_usec=tv_usec;

	tm.it_interval.tv_sec=tv_sec;
	tm.it_interval.tv_usec=tv_usec;

	if(setitimer(ITIMER_REAL,&tm,NULL)==-1){
		perror("setitimer");
		exit(-1);
	}
}

int main(){
	int shmid;
//	int shmid_sig;
	pid_t *pid1_window;//本窗口进程的pid
	pid_t *getpid1;//进程1的pid的地址
	time_t t;
//	*pid1_window=getpid();
//
//保证进程1先登录 能够直接读出
	printf("SYS---linking to sharing memory for several seconds\n");

	shmid=shmget(1231,1<<20,IPC_CREAT|0666);//创建shm
	if(-1==shmid){
		perror("shmget");
		return -1;
	}

	getpid1=(pid_t *)shmat(shmid,NULL,0);//连接1231，接受进程1的pid
	if(getpid1==(pid_t*)-1){
		perror("shmat_getpid2");
		return -1;
	}
	pid1=*getpid1;
//	printf("process 1 pid =%d\n",*getpid1);
//穿出自己的pid
	

	pid1_window=(pid_t *)shmat(shmid,NULL,0);
	if(pid1_window==(pid_t*)-1){
		perror("shmat_sendingpid");
		return -1;
	}
	*pid1_window=getpid();
	pid1_w=getpid();

	printf("process 1 pid =%d\n",pid1);
	printf("window 1 pid=%d\n",pid1_w);
	printf("now let's say hello~\n");
/*-----------------------------------------------------------*/


	//设置时间函数进行检测
	InitTime(0,1000);

	while(1){
	}
	
	return 0;
}