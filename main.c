#include "factory.h"

void* threadfunc(void *p){
	pfac pf=(pfac)p;
	pque pq=&pf->que;
	pNode pn;
	while(1){
		pthread_mutex_lock(&pq->mutex);
		if(0==pq->size){
			pthread_cond_wait(&pf->cond,&pq->mutex);
		}
		que_get(pq,&pn);
		pthread_mutex_unlock(&pq->mutex);
		send_file(pn->new_fd);
		free(pn);
	}
}

int main(int argc,char* argv[]){
	if(argc!=5){
		printf("error input!\n");
		return -1;
	}	

	fac f;//以后的线程池的所有数据都放在f中
	//初始化f
	f.tnum=atoi(argv[3]);
	f.capability=atoi(argv[4]);
	factory_init(&f,threadfunc);
	factory_start(&f);

	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd){
		perror("socket");
		return -1;
	}

	set_init(sfd,argv[1],argv[2]);
	listen(sfd,f.capability);

	int new_fd;
	while(1){
		new_fd=accept(sfd,NULL,NULL);
		que_add(&f.que,new_fd);
		pthread_cond_signal(&f.cond);
	}
	return 0;
}
