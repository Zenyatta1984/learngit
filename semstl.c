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
	
	int ret;
	ret=semctl(semid,0,SETVAL,1);
	if(-1==ret){
		perror("semctl");
		return 0;
	}

	int ret2;
	ret2=semctl(semid,0,GETVAL,NULL);
	printf("the semval=%d\n",ret2);
	return 0;
}
