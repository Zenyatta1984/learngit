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
	int new_fd;
	int addrlen=sizeof(cli);
	new_fd=accept(sfd,(struct sockaddr*)&cli,&addrlen);
	if(-1==new_fd){
		perror("accept");
		return -1;
	}
	printf("%s %dsucceed in connecting\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
//不持续的先读后写的操作
	char buf[30];
	ret=recv(new_fd,buf,sizeof(buf),0);
	if(-1==ret){
		perror("recv");
		
		return 0;
	}
	printf("---%s\n",buf);

	ret=send(new_fd,"I am server",11,0);
	if(-1==ret){
		perror("send");
		return -1;
	}
//用完之后关闭两个套接口
	close(new_fd);
	close(sfd);

	return 0;
}




