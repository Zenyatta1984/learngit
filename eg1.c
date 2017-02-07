#include "head.h"

void * thread( void * parg){
	int i;
	for(i=0;i<10;i++){
		printf("I am child thread, arg is %d\n",(int)parg);
		sleep(1);
	}
	pthread_exit(NULL);
}

int main(){
	pthread_t thdid;
	pthread_create(&thdid,NULL,thread,(void*)30);

	int i;
	for(i=0;i<10;i++){
		printf("I am main thread,child thread id =%d\n",thdid);
		sleep(1);
	}

	return 0;
}
