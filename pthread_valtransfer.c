#include "../head.h"
void* thread_1(void * p){
//	int i=5;
	int p1=(int )p;
	p1=p1+1;
//	printf("thread_1 : number=%d\n",*p1);
//	int i=*p;
	return (void*)p1;
//return (void*)p1;
}
int main(){
	pthread_t pthid;
	
	int ret=pthread_create(&pthid,NULL,thread_1,(void*)1);
	if(ret!=0){
		printf("phread_create errno=%d\n",ret);
		return -1;
	}

	int p_return;
//	int i;		
	ret=pthread_join(pthid,(void**)&p_return);
	if(ret!=0){
		printf("pthread_join errno=%d\n",ret);
		return -1;
	}

	printf("the result is %d\n",p_return);
	return 0;
}
