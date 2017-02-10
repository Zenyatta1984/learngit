#include<stdio.h>
#include<unistd.h>
#include<strings.h>
#include<string.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/select.h>
#include<sys/time.h>
#include<sys/mman.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<signal.h>
#include<pthread.h>


#define INPUT int argc,char*argv[]

//#define CK_ARGS if(argc!=2){printf("error args");return -1;}

//#define CK_OPEN if(-1==fd){perror("open");return -1;}
