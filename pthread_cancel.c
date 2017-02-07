#include "../head.h"
void clean_func(void *p){
	printf("clean the thread_1\n");
	free(p);
}

void* thread_1(void *p){
	int *k;
	k=(int *)malloc(4);
	pthread_cleanup_push(clean_func,(void*)k);
	printf("thread_1 created successfully!\n");
	sleep(3);
	printf("thread_1 is awake now.\n");
	pthread_exit(NULL);
	pthread_cleanup_pop(1);
}

int main(){
	pthread_t pthid;
	int ret;
	ret=pthread_create(&pthid,NULL,thread_1,NULL);
	if(ret!=0){
		printf("pthread_create errno is %d\n",ret);
		return -1;
	}

	pthread_cancel(pthid);
	pthread_join(pthid,NULL);

	return 0;
}
