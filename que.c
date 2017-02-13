#include "work_que.h"

void que_init(pque pq){
	memset(pq,0,sizeof(que_t));
	pthread_mutex_init(&pq->mutex,NULL);
}

void que_add(pque pq,int new_fd){
	pNode pnew=(pNode)calloc(1,sizeof(Node));
	pnew->new_fd=new_fd;
	pthread_mutex_lock(&pq->mutex);
	if(0==pq->ptail){
		pq->ptail=pnew;
		pq->phead=pnew;
	}else{
		pq->ptail->pnext=pnew;
		pq->ptail=pnew;
	}
//	pthread_mutex_unlock(&pq->mutex);
	(pq->size)++;
	pthread_mutex_unlock(&pq->mutex);
}

void que_get(pque pq,pNode* ppNode){
	*ppNode=pq->phead;
	pq->phead=pq->phead->pnext;
	(pq->size)--;
}
