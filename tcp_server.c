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

	close(sfd);
	return 0;
}




