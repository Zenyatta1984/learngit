//有亲缘关系的信号量进程间通信
//消费者-生产者模式

#include "../head.h"
union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int main(){
	int semid=semget(IPC_PRIVATE,1,0666|IPC_CREAT);
	if(semid==-1){
		perror("semget");
		return -1;
	}
	if(fork()==0){
		struct sembuf sem;
		memset(&sem,0,sizeof(sem));
		sem.sem_num=0;
		sem.sem_op=1;
		sem.sem_flg=SEM_UNDO;

		union semun arg;
		arg.val=0;
		semctl(semid,0,SETALL,arg);
		while(1){
			semop(semid,&sem,1);
			printf("productor total number=%d\n",semctl(semid,0,GETVAL));
			sleep(1);
		}
		return 0;
	}else{
		sleep(2);
		struct sembuf sem;
		memset(&sem,0,sizeof(sem));
		sem.sem_num=0;
		sem.sem_op=-1;
		sem.sem_flg=SEM_UNDO;
		
		while(1){
			semop(semid,&sem,1);
			printf("costomer total number:%d\n",semctl(semid,0,GETVAL));

			sleep(2);
		}
	}
	return 0;
}

