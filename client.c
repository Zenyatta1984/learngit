#include "pfunc.h"

int main(INPUT){
	if(argc!=3){
		printf("error inputs\n");
		return -1;
	}

	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1){
		perror("socket");
		return -1;
	}

	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);

	int ret;
	ret=connect(sfd,(struct sockaddr*)&ser,sizeof(ser));
	if(-1==ret){
		perror("connect");
		return -1;
	}
	printf("C:linked\n");

	int len;
	char buf[1000]={0};
	recv_n(sfd,(char*)&len,4);//接收一个四个字节的整数 该整数写着应该接收多长的文件名字节
	
	printf("already linked to server,Filename's len=%d\n",len);
	recv_n(sfd,buf,len);//接收文件名
	int fd;
	fd=open(buf,O_RDWR|O_CREAT,0666);//在当前目录相同文件名的文件
	if(-1==fd){
		perror("open");
		return -1;
	}
	while(1){
		recv_n(sfd,(char*)&len,4);
		memset(buf,0,sizeof(buf));
		if(len>0){
			recv_n(sfd,buf,len);
			write(fd,buf,len);
		}
		else{
			break;
		}
	}
	close(fd);
	close(sfd);
}

