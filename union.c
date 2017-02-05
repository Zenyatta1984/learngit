 ///
 /// @file    union.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-02-05 17:23:08
 ///
/*
#include <iostream>
using std::cout;
using std::endl;*/

#include "../head.h"
int main(){
	int semid=semget(1234,2,IPC_CREAT|0600);
	if(-1==semid){
		perror("semget");
		return -1;
	}
	//通过union同时设置信号量组内的两个信号
	
	unsigned short a[2]={1,5};
	int ret=semctl(semid,0,SETALL,a);
	if(-1==ret){
		perror("semctl");
		return -1;
	}
	
	memset(a,0,sizeof(a));
	int ret2=semctl(semid,0,GETALL,a);
	if(-1==ret2){
		perror("semctl");
		return -1;
	}
	printf("semvalue1=%d,semvalue2=%d\n",a[0],a[1]);
	return 0;
}
