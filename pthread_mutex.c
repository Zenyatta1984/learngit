#include "../head.h"
#define N 10000000
pthread_mutex_t lock;

void* thread_1 (void* p){
	int i;
	int *p1= (int *)p;
	for(i=0;i<N;i++){
		pthread_mutex_lock(&lock);
		
		*p1=*p1+1;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

int main(){
	pthread_t pthid;
	int ret;
	int *p;
	p=(int *)malloc(4);
	*p=0;

	ret=pthread_mutex_init(&lock,NULL);
	if(ret!=0){
		printf("pthread_mutex_init error.no=%d\n",ret);
		return -1;
	}

	ret=pthread_create(&pthid,NULL,thread_1,p);
	if(ret!=0){
		printf("pthread_creat errono=%d\n",ret);
		return -1;
	}

	int i;
	for(i=0;i<N;i++){
		pthread_mutex_lock(&lock);
		*p=*p+1;
		pthread_mutex_unlock(&lock);
	}

	pthread_join(pthid,NULL);
	printf("the result is = %d\n",*p);

	return 0;
}

