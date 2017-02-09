#include "../head.h"
int pid_1;
int pid_1w;
int shmid_A;

void cleanfunc(void *p){
	int ret=shmctl(shmid_A,IPC_RMID,NULL);
	if(-1==ret){
		perror("shmctl");
		return ;
	}
}

void *thread_1(void*p){
	pthread_cleanup_push(cleanfunc,NULL);
	while(1);
	pthread_cleanup_pop(1);
}

int main(INPUT){
	pid_t *pid1;//本进程的pid
//	pid1=getpid();
	pid_t *getpid1;//窗口1的pid的地址
	if(argc!=3)
	{
		printf("error args!\n");
		return -1;
	}
	int fdr,fdw;
	fdr=open(argv[1],O_RDONLY);//2方先打开管道1的写
	if(-1==fdr)
	{
		perror("open1");
		return -1;
	}
	fdw=open(argv[2],O_WRONLY);//2方后打开管道2的读
	if(-1==fdw)
	{
		perror("open2");
		return -1;
	}
//	printf("user2 successfully login!\n");
	char buf[20]={0};
	fd_set rdset;

//和本用户的窗口私下互通pid

	shmid_A=shmget(1231,1<<20,IPC_CREAT|0666);//连接1232
	if(-1==shmid_A){
		perror("shmget");
		return -1;
	}

//先穿出自己的pid
	pid1=(pid_t*)shmat(shmid_A,NULL,0);
	if(pid1==(char*)-1){
		perror("shmat_sending_pid");
		return -1;
	}
	*pid1=getpid();
	pid_1=getpid();

	sleep(5);
	//接收窗口的pid
	sleep(1);
	getpid1=(pid_t*)shmat(shmid_A,NULL,0);
	if(getpid1==(char*)-1){
		perror("shmat_geting_pid");
		return -1;
	}
	pid_1w=*getpid1;

	printf("process 1 pid =%d\n",pid_1);
	printf("window 1 pid=%d\n",pid_1w);

/*------------------------------------------------*/
	//建立子线程 清理现场
	//
//	pthread_t thdid;
//	pthread_create(&thdid,NULL,thread_1,NULL);
//	pthread_join(thdid,NULL);


	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(STDIN_FILENO,&rdset);
		FD_SET(fdr,&rdset);

		int ret;
		ret=select(fdw+1,&rdset,NULL,NULL,NULL);
		if(ret>0){
			if(FD_ISSET(0,&rdset)){//从标准输入读入
				memset(buf,0,sizeof(buf));
				if(read(STDIN_FILENO,buf,sizeof(buf))>0){
					char *p;
					p=(char*)shmat(shmid_A,NULL,0);
					if(p==(char*)-1){
						perror("shmat");
						return -1;
					}
					strcpy(p,buf);
					//写入当前的时间--注意格式--右对齐--传出信号10
					//写入到管道写端
					kill(pid_1w,10);
					write(fdw,buf,strlen(buf)-1);
					//buf写入共享内存1
					
				}else{break;}
			}

			if(FD_ISSET(fdr,&rdset)){//从管道2读入
				memset(buf,0,sizeof(buf));
				if(read(fdr,buf,sizeof(buf))>0){
					
					char *p;
					p=(char*)shmat(shmid_A,NULL,0);
					if(p==(char*)-1){
						perror("shmat");
						return -1;
					}
					strcpy(p,buf);
					kill(pid_1w,12);
					//写入当前时间-- 注意格式--左对齐
					//buf写入共享内存1
				}else{break;}
			}
		}
	}
	close(fdw);

	return 0;
}
/*		memset(buf,0,sizeof(buf));
		if(read(fdr,buf,sizeof(buf)-1)>0){
			puts(buf);
		}else{break;}
		memset(buf,0,sizeof(buf));
		if(read(STDIN_FILENO,buf,sizeof(buf))>0)
		{
			write(fdw,buf,strlen(buf)-1);
		}else{break;}
	}

	close(fdr);
	return 0;
}*/
