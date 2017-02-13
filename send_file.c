#include "pfunc.h"

void send_file(int new_fd){
	td t;
	memset(&t,0,sizeof(t));
	t.len=strlen(FILENAME);
	printf("C:len=%d\n",t.len);
	strcpy(t.buf,FILENAME);
	send_n(new_fd,(char*)&t,4+t.len);
	int fd;
	fd=open(FILENAME,O_RDONLY);
	if(-1==fd){
		perror("open");
		exit(-1);
	}

	while(memset(&t,0,sizeof(t)),(t.len=read(fd,t.buf,sizeof(t.buf)))>0){
		send_n(new_fd,(char*)&t,4+t.len);
	}
	t.len=0;
	send_n(new_fd,(char*)&t.len,4);
	close(new_fd);
}
