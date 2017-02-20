#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <errno.h>
#include <wait.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <time.h>
#include <shadow.h>
#include <crypt.h>
//#define _GNU_SOURCE
//#define _XOPEN_SOURCE

typedef struct child_process_data{
	pid_t pid;
	int fdw;
	short busy;
}cdata,*pcdata;

typedef struct train_data_in_file{
	int len;
	char buf[1000];
}td,*ptd;

void send_file(int);
void make_child(pcdata,int);
void handle_request(int);
void send_fd(int,int);
void recv_fd(int,int*);
void send_n(int,char*,int);
void recv_n(int,char*,int);
void deliver_command(int);

#define INPUT int argc,char* argv[]
