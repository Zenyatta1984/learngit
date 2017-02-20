#include "pfunc.h"
//main.c
int main(INPUT){
	if (argc!=4){
		printf("error args!\n");
		return -1;
	}

	//所有的输出都重定向
	
	int fd=open("user1.txt",O_WRONLY|O_APPEND);
	if(-1==fd){
		perror("open");
		return -1;
	} 
	close(1);
	int fd_std=dup(fd);
		
	//printf("helloworld\n");



//################################################################dup
/*
	int fd=dup(STDOUT_FILENO),testfd;
	//printf("fd=[%d]\n",fd);
	testfd=open("../../log/user1.txt",O_RDWR|O_APPEND|O_CREAT);
	if(-1==testfd){
		perror("open");
		return -1;
	}

	if(-1==dup2(testfd,STDOUT_FILENO)){
		perror("dup2");
		return -1;
	}
*/
//###############################################################enddup

	//printf("should be in the 'temp'\n");

	//recover
	/*
	if(-1!=dup2(fd,STDOUT_FILENO)){
		printf("should be seen on screen!\n");
	}
	
	close(testfd);
	*/
//###########################
/*
	int stdout_sfd=-1;
	int file_fd=-1;
	int stdout_nfd=-1;
	mode_t old_mask=0;

	old_mask=umask(0);
	file_fd=open("./user1.txt",O_CREAT|O_RDWR|O_APPEND,00777);
	if(file_fd<0){
		perror("open");
		return -1;
	}

	umask(old_mask);

	stdout_sfd=dup(STDOUT_FILENO);
	stdout_nfd=dup2(file_fd,STDOUT_FILENO);
	if((stdout_nfd)<0 ||(stdout_sfd<0)){
		printf("dup failed\n");
		return -1;
	}

	printf("Log starts now!\n");
*/
//##########################
	//存储
	int count=atoi(argv[3]);//创建的进程数
	pcdata p;//结构体指针
	p=(pcdata)calloc(count,sizeof(cdata));
	make_child(p,count);
	
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd){
		perror("socket");
		return -1;
	}

	//初始化socket管道--创建好结构体以绑定bind
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);

	int ret;
	ret=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
	if(-1==ret){
		perror("bind");
		return -1;
	}

	listen(sfd,count);

	int epfd;
	epfd=epoll_create(1);
	struct epoll_event event,*evs;
	evs=(struct epoll_event*)calloc(count+1,sizeof(event));
	memset(&event,0,sizeof(event));
	event.events=EPOLLIN;
	event.data.fd=sfd;
	
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
	if(-1==ret){
		perror("epoll_ctl_add_sfd");
		return -1;
	}
	
	int i;
	for(i=0;i<count;i++){
		event.events=EPOLLIN;
		event.data.fd=p[i].fdw;
		epoll_ctl(epfd,EPOLL_CTL_ADD,p[i].fdw,&event);
	}

	int j,ret1,new_fd;
	short flag;
	time_t t;//记录用户登录时间
	while(1){
		memset(evs,0,(count+1)*sizeof(event));
		ret=epoll_wait(epfd,evs,count+1,-1);
		if(ret>0){
			for(i=0;i<ret;i++){
				if(evs[i].data.fd==sfd){
					new_fd=accept(sfd,NULL,NULL);
					printf("M:one more client linked:user1\n");
					for(j=0;j<count;j++){
						if(p[j].busy==0){
							printf("M:have already find a spare process\n");
							printf("M:sending message to it\n");
							time(&t);
							printf("user1 login time:	%s\n",ctime(&t));
							send_fd(p[j].fdw,new_fd);
							p[j].busy=1;
							break;
						}
					}
					close(new_fd);
				}

				for(j=0;j<count;j++){
					if(evs[j].data.fd==p[j].fdw){
						read(p[j].fdw,&flag,sizeof(flag));
						p[j].busy=0;
						printf("M:this child process runs OK,and already returns.\n");
					}
				}
			}
		}
	}
	close(sfd);
	close(epfd);
	
	return 0;
}
