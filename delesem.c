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
	
	int ret=semctl(semid,0,IPC_RMID);
	if(-1==ret){
		perror("semctl");
		return -1;
	}
	return 0;
}
