#include "head.h"

void *thread(void *parg){
	int iarg=(int)parg;
	sleep(iarg);
	if(iarg<3) return(void*)(iarg*2);
	else{
		pthread_exit((void*)(iarg*2));
	}
}
	int main(){
		pthread_t thdid;
		pthread_create(&thdid,NULL,thread,(void*)2);
		
		int ret;
		pthread_join(thdid,(void**)&ret);

		pthread_create(&thdid,NULL,thread,(void*)2);
		pthread_join(thdid,(void**)&ret);
		printf("the second child thread ret is :%d\n",ret);

		return 0;
	}
