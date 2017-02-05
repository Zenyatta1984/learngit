 ///
 /// @file    semget.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-02-05 11:26:29
 ///
/* 
#include <iostream>
using std::cout;
using std::endl;*/

#include "../head.h"
int main(){
	int semid;
	semid=semget(1234,1/*个数*/,IPC_CREAT|0600);
	if(-1==semid){
		perror("semget");
		return -1;
	}
//获取信号量的详细信息	
	struct semid_ds buf;
	memset(&buf,0,sizeof(buf));
	int ret=semctl(semid,0,IPC_STAT,&buf);
	if(ret==-1){
		perror("semctl");
		return -1;
	}
	printf("uid=%d,mode=%o,sem_num=%d\n",buf.sem_perm.uid,buf.sem_perm.mode,buf.sem_nsems);
//修改信号量的部分信息
//修改sem_num

	buf.sem_perm.mode=0666;
	int ret2=semctl(semid,0,IPC_SET,&buf);
	if(ret==-1){
		perror("semcel2");
		return -1;
	}

	return 0;
}
