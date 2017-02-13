#ifndef __NORMAL_H__
#define __NORMAL_H__
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#define FILENAME "The_Holy_Bible.txt"
typedef struct tdata{
	int len;//代表后面真实数据长度
	char buf[1000];//火车车厢
}td,*ptd;

void send_n(int,char*,int);
void recv_n(int,char*,int);
#endif
