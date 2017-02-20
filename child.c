#include "pfunc.h"
//子进程

void handle_request(int fdr){
	int new_fd;
	short flag;
	while(1){
		recv_fd(fdr,&new_fd);
		printf("C:child process is handling new_fd=%d\n",new_fd);
		login(new_fd);
		deliver_command(new_fd);
		printf("C:already reply!,going to tell main process jobs are done!\n");
		write(fdr,&flag,sizeof(flag));
	}
}

void make_child(pcdata p,int count){
	//创建一对
	int fds[2];
	int i;
	pid_t pid;

	for(i=0;i<count;i++){
		socketpair(AF_LOCAL,SOCK_STREAM,0,fds);//放到循环里 fork之前
		//才能够产生一条无名管道
		
		pid=fork();//返回两个pid
		if(0==pid){
			close(fds[1]);
			handle_request(fds[0]);
		}
		p[i].pid=pid;
		p[i].fdw=fds[1];
		p[i].busy=0;
		close(fds[0]);
	}
}
