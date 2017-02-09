#include "../head.h"
#define N 1000
typedef struct data{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}thd,*pthd;

void *thread_1(void *p){
	pthd pd=(pthd)p;
	printf("I am child thread,I will wait\n");
	
	pthread_mutex_lock(&pd->mutex);
	pthread_cond_wait(&pd->cond,&pd->mutex);
	pthread_mutex_unlock(&pd->mutex);

	printf("I am child thread, I am awake\n");
	pthread_exit(NULL);
}


int main(){
	thd d;
	pthread_mutex_init(&d.mutex,NULL);
	pthread_cond_init(&d.cond,NULL);

	pthread_t thdid;
	pthread_create(&thdid,NULL,thread_1,&d);
	printf("create thread1 success\n");
	
	usleep(N);
	pthread_cond_signal(&d.cond);
	pthread_join(thdid,NULL);

	return 0;
}
