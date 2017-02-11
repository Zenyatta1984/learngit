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


//sendto
	int ret=sendto(sfd,"this is client",14,0,(struct sockaddr*)&ser,sizeof(ser));
	if(-1==ret){
		perror("sendto");
		return -1;
	}
//recvfrom
	char buf[50]={0};
	int addrlen=sizeof(ser);
	ret=recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&ser,&addrlen);
	if(ret==-1){
		perror("recvfrom");
		return -1;
	}

	printf("%s\n",buf);

	close(sfd);
	return 0;
}




