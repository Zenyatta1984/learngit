#include "../func.h"
void change_noblock(int fd){
	int status;
	status=fcntl(fd,F_GETFL);
	status=status|O_NONBLOCK;
	int ret=fcntl(fd,F_SETFL,status);
	if(-1==ret){
		perror("fcntl");
		exit -1;
	}
}

int main(INPUT){
	if(argc!=3){
		printf("error args!\n");
		return -1;
	}

	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1){
		perror("socket");
		exit (-1);
	}
//	printf("套接字sfd=%d\n",sfd);

	struct sockaddr_in server;
	memset(&server,0,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[2]));
	server.sin_addr.s_addr=inet_addr(argv[1]);

//	printf("net_port=%s\n",server.sin_port);
//	printf("net_addr=%s\n",server.sin_addr.s_addr);

	int ret;
	ret=bind(sfd,(struct sockaddr*)&server,sizeof(server));
	if(-1==ret){
		perror("bind");
		return -1;
	}
	
//监听
	listen(sfd,10);//最多可以监听10个客户端

//连接客户端accept,会建立new_fd
	struct sockaddr_in cli;
	memset(&cli,0,sizeof(cli));

//epoll
	int epfd=epoll_create(1);
	struct epoll_event event,eves[3];
	//监控sfd
	memset(&event,0,sizeof(event));
	event.events=EPOLLIN;
	event.data.fd=sfd;

	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
	if(-1==ret){
		perror("epoll_ctl");
		return -1;
	}
	//监控标准输入
	memset(&event,0,sizeof(event));
	event.events=EPOLLIN;
	event.data.fd=STDIN_FILENO;
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
	if(-1==ret){
		perror("epoll_ctl");
		return -1;
	}

//持续的操作
//while
//select
	char buf[5]={0};
	char buf2[50]={0};

	int new_fd=-1;
	int i;
	int ret2;

	while(1){
		memset(eves,0,sizeof(eves));
		ret=epoll_wait(epfd,eves,3,-1);

		if(ret>0){
			for(i=0;i<ret;i++){
				if(eves[i].data.fd==sfd){
					int addrlen=sizeof(cli);
					new_fd=accept(sfd,(struct sockaddr*)&cli,&addrlen);
					if(-1==new_fd){
						perror("accept");
						return -1;
					}
					printf("client ip=%s,client port=%d\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
					change_noblock(new_fd);
					memset(&event,0,sizeof(event));
					event.events=EPOLLIN|EPOLLET;
					event.data.fd=new_fd;
					ret=epoll_ctl(epfd,EPOLL_CTL_ADD,new_fd,&event);
				}

				if(eves[i].data.fd==new_fd){
					while(1){
						memset(buf,0,sizeof(buf));
						ret2=recv(new_fd,buf,sizeof(buf),0);
						if(-1==ret2 && errno==EAGAIN){
							break;
						}else if(0==ret2){
							printf("byebye");
							close(new_fd);
							memset(&event,0,sizeof(event));
							event.events=EPOLLIN;
							event.data.fd=new_fd;
							ret2=epoll_ctl(epfd,EPOLL_CTL_DEL,new_fd,&event);
							break;
						}
						printf("%s",buf);
					}
					printf("\n");
				}

				if(eves[i].events==EPOLLIN && eves[i].data.fd==0){
					memset(buf2,0,sizeof(buf2));
					ret2=read(STDIN_FILENO,buf2,sizeof(buf2));
					if(ret2<=0){
						printf("byebye\n");
						close(new_fd);
						memset(&event,0,sizeof(event));
						event.events=EPOLLIN;
						event.data.fd=new_fd;
						ret2=epoll_ctl(epfd,EPOLL_CTL_DEL,new_fd,&event);
						continue;
					}
					ret2=send(new_fd,buf2,strlen(buf2)-1,0);
					if(-1==ret2){
						perror("send");
						return -1;
					}
				}
			}
		}
	}
//用完之后关闭两个套接口
	close(sfd);

	return 0;
}




