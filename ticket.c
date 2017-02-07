#include "../head.h"
pthread_mutex_t lock;
int ticketcount=20;

void* window_1(void *p){
	while(1){
		pthread_mutex_lock(&lock);
		if(ticketcount>0){
			printf("windows 1 starts saling thickets!, %d tickets remained.\n",ticketcount);
			sleep(3);//处理售票过程;
			ticketcount--;
			printf("done saling thickets!, %d tickets remained.\n",ticketcount);
		}else{
			pthread_mutex_unlock(&lock);
			pthread_exit(NULL);
		}
		pthread_mutex_unlock(&lock);
		sleep(1);
	}
}

void* window_2(void *p){
	while(1){
		pthread_mutex_lock(&lock);
		if(ticketcount>0){
			printf("windows 2 starts saling thickets!, %d tickets remained.\n",ticketcount);
			sleep(3);//处理售票过程;
			ticketcount--;
			printf("done saling thickets!, %d tickets remained.\n",ticketcount);
		}else{
			pthread_mutex_unlock(&lock);
			pthread_exit(NULL);
		}
		pthread_mutex_unlock(&lock);
		sleep(1);
	}
}

int main(){
	pthread_t thdid1;
	pthread_t thdid2;

	pthread_mutex_init(&lock,NULL);

	pthread_create(&thdid1,NULL,window_1,NULL);
	pthread_create(&thdid2,NULL,window_2,NULL);

	pthread_join(thdid1,NULL);
	pthread_join(thdid2,NULL);

	pthread_mutex_destroy(&lock);
	return 0;
}
