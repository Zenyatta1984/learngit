#include "../func.h"
int main(INPUT){
	if(argc!=3){
		printf("error args'\n");
		return -1;
	}
	int sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(-1==sfd){
		perror("socket");
		return -1;
	}

	struct sockaddr_in ser;
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);

	int ret=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
	if(-1==ret){
		perror("bind");
		return -1;
	}

	struct sockaddr_in cli;
	memset(&cli,0,sizeof(cli));
	int addrlen=sizeof(cli);

//recvfrom
	char buf[50]={0};
	ret=recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&cli,&addrlen);
	if(ret==-1){
		perror("recvfrom");
		return -1;
	}

	printf("client ip=%s, client port=%d\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
	printf("%s\n",buf);

//sendto
	ret=sendto(sfd,"this is server",14,0,(struct sockaddr*)&cli,addrlen);
	if(-1==ret){
		perror("sendto");
		return -1;
	}

	close(sfd);
	return 0;
}




