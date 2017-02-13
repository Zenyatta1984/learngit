#include "pfunc.h"
//发送描述符控制信息
void send_fd(int fdw,int fd){
	struct msghdr msg;
	memset(&msg,0,sizeof(msg));
	
	char buf[10]="hello ";
	char buf1[10]="world";
	struct iovec iov[2];
	iov[0].iov_base=buf;
	iov[0].iov_len=6;
	iov[1].iov_base=buf1;
	iov[1].iov_len=5;
	msg.msg_iov=iov;
	msg.msg_iovlen=2;
	
	struct cmsghdr *cmsg;
	int len=CMSG_LEN(sizeof(int));
	cmsg=(struct cmsghdr*)calloc(1,len);
	cmsg->cmsg_len=len;
	cmsg->cmsg_level=SOL_SOCKET;
	cmsg->cmsg_type=SCM_RIGHTS;
	*(int *)CMSG_DATA(cmsg)=fd;
	 
	msg.msg_control=cmsg;
	msg.msg_controllen=len;

	int ret;
	ret=sendmsg(fdw,&msg,0);
	if(-1==ret){
		perror("sendmsg");
		exit(-1);
	}
}
//接收描述符控制信息
void recv_fd(int fdr,int *fd){
	struct msghdr msg;
	memset(&msg,0,sizeof(msg));
	
	char buf[10]={0};
	char buf1[10]={0};
	struct iovec iov[2];
	iov[0].iov_base=buf;
	iov[0].iov_len=6;
	iov[1].iov_base=buf1;
	iov[1].iov_len=5;
	msg.msg_iov=iov;
	msg.msg_iovlen=2;
	
	struct cmsghdr *cmsg;
	int len=CMSG_LEN(sizeof(int));
	cmsg=(struct cmsghdr*)calloc(1,len);
	cmsg->cmsg_len=len;
	cmsg->cmsg_level=SOL_SOCKET;
	cmsg->cmsg_type=SCM_RIGHTS;
	 
	msg.msg_control=cmsg;
	msg.msg_controllen=len;

	int ret;
	ret=recvmsg(fdr,&msg,0);
	if(-1==ret){
		perror("recvmsg");
		exit(-1);
	}
	*fd=*(int*)CMSG_DATA(cmsg);
}

