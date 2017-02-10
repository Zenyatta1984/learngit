#include "../func.h"

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
//持续的操作
//while
//select
	char buf[30]={0};
	fd_set rdset,tmpset;
	int new_fd;
	FD_ZERO(&tmpset);
	FD_SET(STDIN_FILENO,&tmpset);
	FD_SET(sfd,&tmpset);

	while(1){
		FD_ZERO(&rdset);
		memcpy(&rdset,&tmpset,sizeof(fd_set));
		ret=select(13,&rdset,NULL,NULL,NULL);
		if(ret>0){
			if(FD_ISSET(sfd,&rdset)){
				int addrlen=sizeof(cli);
				new_fd=accept(sfd,(struct sockaddr*)&cli,&addrlen);
				if(-1==new_fd){
					perror("accept");
					return -1;
				}
				FD_SET(new_fd,&tmpset);
				printf("client ip=%s,client port=%d\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
			}

			if(FD_ISSET(new_fd,&rdset)){
				memset(buf,0,sizeof(buf));
				ret=recv(new_fd,buf,sizeof(buf),0);
				if(-1==ret){
					perror("recv");
					return 0;
				}else if(0==ret){
					printf("byebye\n");
					close(new_fd);
					FD_CLR(new_fd,&tmpset);
					continue;
				}
				printf("%s\n",buf);
			}

			if(FD_ISSET(STDIN_FILENO,&rdset)){
				memset(buf,0,sizeof(buf));
				ret=read(STDIN_FILENO,buf,sizeof(buf));
				if(ret<=0){
					printf("byebye\n");
					close(new_fd);
					FD_CLR(new_fd,&tmpset);
					continue;
				}
				ret=send(new_fd,buf,strlen(buf)-1,0);
				if(-1==ret){
					perror("send");
					return -1;
				}
			}
		}
	}
//用完之后关闭两个套接口
	close(sfd);

	return 0;
}




