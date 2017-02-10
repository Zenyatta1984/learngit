#include "../func.h"
//#define h->addr h->addr->list[0]
int main(INPUT){
	if (argc!=2){
		printf("error input!\n");
		return -1;
	}

	char *ptr, **pptr;
	struct hostent *hptr;
	char str[32]={'\0'};
	ptr=argv[1];

	if((hptr=gethostbyname(ptr))==NULL){
		//h_error number 不用perror
		printf("gethostbyname err for host:%s\n",ptr);
		return 0;
	}

	printf("official hostname:%s\n",hptr->h_name);

	//打出所有的主机别名;
	//pptr耳机指针偏移
	for(pptr=hptr->h_aliases;*pptr!=NULL;pptr++){
		printf("h_alias:%s\n",*pptr);
	}


	switch(hptr->h_addrtype){
		case AF_INET:
		case AF_INET6:
		pptr=hptr->h_addr_list;
		for(;*pptr!=NULL;pptr++){
			printf("address:%s\n",inet_ntop(hptr->h_addrtype,*pptr,str,sizeof(str)));
		}

		printf("first address:%s\n",inet_ntop(hptr->h_addrtype,hptr->h_addr,str,sizeof(str)));
		break;
		default:printf("unknown address type\n");
	}

	return 0;
}
