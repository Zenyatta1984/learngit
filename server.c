#include "pfunc.h"
//main.c
int main(INPUT){
	if (argc!=4){
		printf("error args!\n");
		return -1;
	}

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
	while(1){
		memset(evs,0,(count+1)*sizeof(event));
		ret=epoll_wait(epfd,evs,count+1,-1);
		if(ret>0){
			for(i=0;i<ret;i++){
				if(evs[i].data.fd==sfd){
					new_fd=accept(sfd,NULL,NULL);
					printf("M:one more client linked\n");
					for(j=0;j<count;j++){
						if(p[j].busy==0){
							printf("M:have already find a spare process\n");
							printf("M:sending message to it\n");
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
