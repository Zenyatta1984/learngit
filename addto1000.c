 ///
 /// @file    main.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-02-05 14:30:56
 ///
/* 
#include <iostream>
using std::cout;
using std::endl;*/

#include "../head.h"

#define M 10000000
int main(){
	int shmid;
	shmid=shmget(IPC_PRIVATE,1<<12,IPC_CREAT|0600);
	if(-1==shmid){
		perror("shmget");
		return -1;
	}

	int semid;//1235
	semid=semget(1235,1,IPC_CREAT|0600);
	if(-1==semid){
		perror("shmget");
		return -1;
	}

	int ret1;
	ret1=semctl(semid,0,SETVAL,1);
	if(-1==ret1){
		perror("semctl");
		return -1;
	}
	
	int *p=(int *)shmat(shmid,NULL,0);
	*p=0;

	if(!fork()){
		struct sembuf op_p,op_s;
		memset(&op_p,0,sizeof(op_p));
		memset(&op_s,0,sizeof(op_s));
		op_p.sem_num=0;
		op_p.sem_op=-1;
		op_p.sem_flg=SEM_UNDO;

		op_s.sem_num=0;
		op_s.sem_op=1;
		op_s.sem_flg=SEM_UNDO;

		int *p=(int *)shmat(shmid,NULL,0);
		for(int i=0;i<M;i++){
			semop(semid,&op_p,1);
			(*p)++;
			semop(semid,&op_s,1);
		}
		return 0;
	}else{
		struct sembuf op_p,op_s;
		memset(&op_p,0,sizeof(op_p));
		memset(&op_s,0,sizeof(op_s));

		op_p.sem_num=0;
		op_p.sem_op=-1;
		op_p.sem_flg=SEM_UNDO;

		op_s.sem_num=0;
		op_s.sem_op=1;
		op_s.sem_flg=SEM_UNDO;

		int *p=(int *)shmat(shmid,NULL,0);
		for(int j=0;j<M;j++){
			semop(semid,&op_p,1);
			(*p)++;
			semop(semid,&op_s,1);
		}
		wait(NULL);
		printf("the result is %d\n",*p);
		return 0;
	}
	return 0;
}







