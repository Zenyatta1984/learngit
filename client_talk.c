#include "../func.h"
//客户端只有一个sfd
int main(INPUT){
	if(argc!=3){
		printf("error args!\n");
		return -1;
	}

	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd){
		perror("socket");
		return -1;
	}
//建立server
//server用于connect的连接服务器端的accept三次握手 （操作系统自己完成）
	struct sockaddr_in server;
	memset(&server,0,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[2]));
	server.sin_addr.s_addr=inet_addr(argv[1]);
//连接
	int ret;
	ret=connect(sfd,(struct sockaddr*)&server,sizeof(server));
	if(-1==ret){
		perror("connect");
		return -1;
	}

	char buf[30]={0};
	fd_set rdset;

	while(1){

	FD_ZERO(&rdset);
	FD_SET(STDIN_FILENO,&rdset);
	FD_SET(sfd,&rdset);
		ret=select(sfd+1,&rdset,NULL,NULL,NULL);
		if(ret>0){
			if(FD_ISSET(STDIN_FILENO,&rdset)){
				memset(buf,0,sizeof(buf));
				ret=read(STDIN_FILENO,buf,sizeof(buf));
				if(ret<=0){
					printf("byebye\n");
					break;
				}
				ret=send(sfd,buf,strlen(buf)-1,0);
				if(-1==ret){
					perror("send");
					return -1;
				}
			}

			if(FD_ISSET(sfd,&rdset)){
				memset(buf,0,sizeof(buf));
				ret=recv(sfd,buf,sizeof(buf),0);
				if(-1==ret){
					perror("resv");		
					return -1;
				}else if(ret==0){
					printf("byebye\n");
					break;
				}
				printf("%s\n",buf);
			}
		}
	}
	close(sfd);
	return 0;
}
	
	

