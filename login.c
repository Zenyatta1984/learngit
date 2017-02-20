#include "pfunc.h"

void login(int new_fd){
	td account;
	//将所有的登录信息存储在数据库中
	//查找的时候也是在对应的数据库查找
/*	
	while(1){
		memset(&account,0,sizeof(account));
		recv_n(new_fd,(char*)account.len,4);
		//recv_n
	}
*/
	
	char name[]="ziboris";
	char salt[]="$1$fu7ri2lG";
	char wname[]="wrongname";
	char encode[]="$1$fu7ri2lG$4lA1xpHgyNEECLjjEulwS1";
	char flag1[]="success";
	char flag2[]="failed";

	printf("encode len=%d\n",(int)strlen(encode));
	printf("salt len=%d\n",(int)strlen(salt));
	time_t t;
	//接收name发送salt
label_1:
	memset(&account,0,sizeof(account));
	recv_n(new_fd,(char*)&account.len,4);
	recv_n(new_fd,account.buf,account.len);
	printf("-----------------\n");
	printf("Client trying to login:>>>%s\n",account.buf);
	time(&t);
	printf("Time is %s\n",ctime(&t));
	if(!strcmp(account.buf,name)){
		//成功返回salt
		memset(&account,0,sizeof(account));
		strcpy(account.buf,salt);
		account.len=strlen(account.buf);
		send_n(new_fd,(char*)&account,4+account.len);
	}
	else{
		//不匹配名字则返回wrongname；
		memset(&account,0,sizeof(account));
		strcpy(account.buf,wname);
		account.len=strlen(account.buf);
		send_n(new_fd,(char*)&account,4+account.len);
		printf("No such a name,reinput a name!\n");
		goto label_1;
	}
		
	//接收encode并比对
label_2:
	memset(&account,0,sizeof(account));
	recv_n(new_fd,(char*)&account.len,4);
	printf("client encode len=%d\n",account.len);
	recv_n(new_fd,account.buf,account.len);
	if(!strcmp(account.buf,encode)){
		//发送内容为success的flag
		memset(&account,0,sizeof(account));
		strcpy(account.buf,flag1);
		account.len=strlen(account.buf);
		send_n(new_fd,(char*)&account,4+account.len);
	}
	else{
		memset(&account,0,sizeof(account));
		strcpy(account.buf,flag2);
		account.len=strlen(account.buf);
		send_n(new_fd,(char*)&account,4+account.len);
		printf("login filed,reinput the password!\n");
		goto label_2;
	}
	return;
}

	
