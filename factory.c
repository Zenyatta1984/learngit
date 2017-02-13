#include "factory.h"

void factory_init(pfac p,pthfunc entry){
	p->pth=(pthread_t*)calloc(p->tnum,sizeof(pthread_t));
	pthread_cond_init(&p->cond,NULL);
	p->entry=entry;
	que_init(&p->que);
	p->start=0;
}


void factory_start(pfac p){
	int i;
	if(0==p->start){
		for(i=0;i<p->tnum;i++){
			pthread_create(&p->pth[i],NULL,p->entry,p);
		}
		p->start=1;
	}
	else{
		printf("Factory has started!\n");
	}
	return ;
}
