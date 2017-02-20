#include "pfunc.h"

void get_salt(char * salt,char * passwd){
	int i,j;
	for(i=0,j=0;passwd[i]&&j!=3;++i){
		if(passwd[i]=='$'){
			++j;
		}
	}
	strncpy(salt,passwd,i-1);
}

void check_send_file(char* name,int sfd){
	DIR *dir;
	struct stat mystat;
	memset(&mystat,0,sizeof(mystat));
	struct dirent *p;
	char* path=NULL;
	path=getcwd(NULL,0);
	dir=opendir(path);
	while((p=readdir(dir))!=NULL){
		int ret;
		ret=stat(p->d_name,&mystat);
		if(-1==ret){
			perror("stat");
			return;
		}

		if(!strcmp(p->d_name,name) && (8==(mystat.st_mode>>12))){
			td t;
			memset(&t,0,sizeof(t));
			t.len=strlen(p->d_name);
			strcpy(t.buf,p->d_name);
			//send_n(sfd,(char*)&t,4+t.len);
			int fd;
			fd=open(p->d_name,O_RDONLY);
			if(-1==fd){
				perror("open");
				return;
			}

			while(memset(&t,0,sizeof(t)),(t.len=read(fd,t.buf,sizeof(t.buf)))>0){
				send_n(sfd,(char*)&t,4+t.len);
			}

			t.len=0;
			send_n(sfd,(char*)&t.len,4);
			close(fd);
			break;
		}
	}
}

int main(INPUT){
	if(argc!=3){
		printf("---error inputs\n");
		return -1;
	}
	
	system("clear");
	printf("...Builing the socket pipe!\n");
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1){
		printf("--->\n");
		perror("socket");
		return -1;
	}

	printf("...Connecting to the server accroding to IP and PORT!\n");
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);

	int ret;
	ret=connect(sfd,(struct sockaddr*)&ser,sizeof(ser));
	if(-1==ret){
		printf("--->\n");
		perror("connect");
		return -1;
	}
	printf("...Linked to server successfully!\n");

	//记得回来设置登录界面和登录接口
//	td account;

	printf("\n");
	printf("---------------------\n");
	
	
	//##############################################
	//客户端：发送name接收服务器从数据库里面读取的salt 生成密文发送回去比对
	//接收flag
/*以下部分写在服务器 服务器永远root登录	
	uid_t uid=getuid();//设置uid为root
	if(setuid(0)){//成功set返回值为0 这里是失败
		return -3;
	}

	struct spwd *sp;
	char *passwd=NULL;
	char salt[512]={0};
	passwd=getpass("Password:");
	sp=getspnam(argv[3]);
	if(NULL==sp){
		perror("getspnam");
		return -2;
	}
	get_salt(salt,sp->sp_pwdp);
	if(strcmp(sp->sp_pwdp,crypt(passwd,salt))==0){
		printf("login success!\n");
		sleep(2);
	}else {
		goto label_1;
	}

	if(setuid(uid)){//恢复uid
		return -4;
	}
*/
	td account;
label_2:
	memset(&account,0,sizeof(account));
	char usrname[20]={0};
	printf("Username:\n");
	read(0,usrname,sizeof(usrname));
	strcpy(account.buf,usrname);
	account.len=strlen(account.buf)-1;
	//printf("strlen=%d\n",account.len);
	send_n(sfd,(char*)&account,4+account.len);

	//接salt
	char salt[512]={0};
	memset(&account,0,sizeof(account));
	recv_n(sfd,(char*)&account.len,4);
	printf("salt len recv=%d\n",account.len);
	recv_n(sfd,account.buf,account.len);
	strcpy(salt,account.buf);
	if(!strcmp(salt,"wrongname")){
		printf("wrongname,please reinput!\n");
		goto label_2;
	}

	//输入密码
	char *passwd=NULL;
	char *miwen=NULL;//密文
label_1:
	passwd=getpass("Password:");
	//printf("passlen=%d\n",strlen(passwd));
	miwen=crypt(passwd,salt);
	//printf("miwen=%s\n",miwen);
	if(NULL==miwen){
		perror("crypt");
		return -4;
	}
	
	//发送密文给服务器作比对
	memset(&account,0,sizeof(account));
	strcpy(account.buf,miwen);
	account.len=strlen(account.buf);
	send_n(sfd,(char*)&account,4+account.len);

	//接收信息到底是通不通过
	char flag[10]={0};
	memset(&account,0,sizeof(account));
	recv_n(sfd,(char*)&account.len,4);
	recv_n(sfd,account.buf,account.len);
	strcpy(flag,account.buf);

	if(!strcmp(flag,"success")){
		printf("Login success!\n");
		sleep(2);
	}
	else {
		printf("error password!reinput!\n");
		sleep(3);
		goto label_1;
	}
	


	//传命令 t.len是实际的命令长度 不包括最后的\0
	char buf2[1000]={0};//读入时候
	char buf3[1000]={0};
	char buf4[1000]={0};

	system("clear");	
	td t_in,t_out;

	//由于客户端发出一条指令有可能收到的不止一条 要用多路复用的监控
	fd_set rdset;
	int findname=0;
	long size;
	int mark=0;//标记客户端应该让服务器传来的内容打印还是重定向到文件中
	while(1){
		FD_ZERO(&rdset);
		FD_SET(0,&rdset);
		FD_SET(sfd,&rdset);
		int ret2;
		ret2=select(sfd+1,&rdset,NULL,NULL,NULL);
		
		if(ret2>0){
			if(FD_ISSET(0,&rdset)){
				memset(buf2,0,sizeof(buf2));
				read(0,buf2,sizeof(buf2));
			//删开头空格	
				int i=0;//记录buff开头开始有多少个空格
				while(buf2[i]==' '){
					i++;
				}
				int j;
				memset(buf3,0,sizeof(buf3));
				for(j=0;j<strlen(buf2)-i;j++){//将更改之后的传到bufff中
					buf3[j]=buf2[j+i];
				}
			//删buf3结尾空格
				int k;
				for(k=strlen(buf3)-1;buf3[k]==' ';k--){}//算出有多少个前面
				int a;
				memset(buf4,0,sizeof(buf4));
				for(a=0;a<=k;a++){
				buf4[a]=buf3[a];
				}
			
			//小火车
				memset(&t_out,0,sizeof(t_out));
				t_out.len=strlen(buf4)-1;
			//printf("the command above lenth is %d\n",t.len);
				strcpy(t_out.buf,buf4);
				
				send_n(sfd,(char*)&t_out,4+t_out.len);
				
				if(strstr(t_out.buf,"gets")){
					mark=1;
					//发送应该偏移的大小
					int gt_l;
					gt_l=strlen(t_out.buf);
					int gt_c;
					char gt_p[100]={0};
					for(gt_c=0;gt_c<(gt_l-6);gt_c++){
						gt_p[gt_c]=t_out.buf[gt_c+5];
					}//得到名字是gt_p
					DIR *dir=opendir((char*)getcwd(NULL,0));
					struct dirent *p;
					struct stat mystat;
					memset(&mystat,0,sizeof(mystat));
					
					
					
					while((p=readdir(dir))!=NULL){
						int ret_get;
						ret_get=stat(p->d_name,&mystat);
						if(-1==ret_get){
							perror("stat");
							return -1;
						}
						if(!strcmp(p->d_name,gt_p) && (8==(mystat.st_mode>>12))){
							FILE *pFILE;
							pFILE=fopen(gt_p,"r+");
							if(pFILE==NULL){
								perror("fopen");
								return -1;
							}
							fseek(pFILE,0,SEEK_END);
							size=ftell(pFILE);
							fclose(pFILE);
							send_n(sfd,(char*)&size,4);
							findname=1;
							break;
						}
					}
					if(findname==0){
						size=0;
						send_n(sfd,(char*)&size,4);
					}
				}
			
				if(strstr(t_out.buf,"puts")){
				//发送文件
					int pt_l;
					pt_l=strlen(t_out.buf);
					int pt_c;
					char pt_p[100]={0};
					for(pt_c=0;pt_c<(pt_l-6);pt_c++){
						pt_p[pt_c]=t_out.buf[pt_c+5];
					}

					check_send_file(pt_p,sfd);
				}
			}
			

			if(FD_ISSET(sfd,&rdset)){
			//每次发送一个命令都会受到一个回应
			//printf("system reply\n");
				if(mark==0){
					memset(&t_in,0,sizeof(t_in));
					recv_n(sfd,(char*)&t_in.len,4);
					if(t_in.len>0){
						recv_n(sfd,t_in.buf,t_in.len);
						printf("%s\n",t_in.buf);
					}
				}
				
				if(mark==1){//gets
					chdir("./");
					int fd;
					//判断本地是否有
						//如果有传出大小，偏移到结尾等待继续接受
						//如果没有则创建，在write之前记录大小
					

					fd=open(t_in.buf,O_RDWR|O_CREAT,0666);
					if(-1==fd){
						perror("open");
						return -1;
					}
					if(findname==1){
						lseek(fd,size,SEEK_SET);
					}
					memset(&t_in,0,sizeof(t_in));
					while(1){
						recv_n(sfd,(char*)&t_in.len,4);
						if(t_in.len>0){
							recv_n(sfd,t_in.buf,t_in.len);
							write(fd,t_in.buf,t_in.len);
						}
						else{
							break;
						}
					}

					printf("\n");
					printf("download success!\n");
					if(findname==1){
						size=0;
						findname=0;
					}
					close(fd);
					mark=0;	
				}
			//printf("t.len=%d\n",t.len);
			}
		}
	}
	close(sfd);
	return 0;
}
	
/*
	int len;
	char buf[1000]={0};
	recv_n(sfd,(char*)&len,4);//接收一个四个字节的整数 该整数写着应该接收多长的文件名字节
	
	printf("already linked to server,Filename's len=%d\n",len);
	recv_n(sfd,buf,len);//接收文件名
	

	//接受文件的总大小
	long lenth;
	recv_n(sfd,(char*)&lenth,8);



	int fd;
	fd=open(buf,O_RDWR|O_CREAT,0666);//在当前目录相同文件名的文件
	if(-1==fd){
		perror("open");
		return -1;
	}

	long count=0;
	printf("..............................\n");
	printf("...");
	fflush(stdout);
	while(1){
		recv_n(sfd,(char*)&len,4);
		memset(buf,0,sizeof(buf));
		count=count+len;
		if(count>(lenth/10)){
			printf("...");
			fflush(stdout);
			count=0;
		}
		if(len>0){
			recv_n(sfd,buf,len);
			write(fd,buf,len);
		}
		else{
			break;
		}
	}

	printf("\n");
	printf("download successfully!\n");
	close(fd);
	close(sfd);
}
*/