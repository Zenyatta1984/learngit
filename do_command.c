#include "pfunc.h"

void func(struct stat stat1,char *name,int new_fd){
	char qx[11]={0};
	char sss[9]="rwxrwxrwx";

	if ((stat1.st_mode>>12)==4){
		qx[0]='d';
	}
	else if((stat1.st_mode>>12)==8){
		qx[0]='-';
	}
	else{qx[0]='?';}

	for(int i=0;i<9;i++){
		if(stat1.st_mode&(1<<8-i)) qx[i+1]=sss[1];
		else qx[i+1]='-';
	}

	char *a;
	char b[50]={0};
	a=ctime(&stat1.st_mtime);
	for(int j=0;j<=11;j++){
		b[j]=*(a+j+4);
	}
	
	td t_out;
	memset(&t_out,0,sizeof(t_out));
	sprintf(t_out.buf,"%-10s %2ld %8s %8s %9ld %12s %s\n",qx,stat1.st_nlink,getpwuid(stat1.st_uid)->pw_name,getgrgid(stat1.st_gid)->gr_name,stat1.st_size,b,name);
	t_out.len=strlen(t_out.buf);
	send_n(new_fd,(char*)&t_out,4+t_out.len);
}

void do_ls_l(char *path,int new_fd){
	DIR *dir;
	struct stat mystat;
	memset(&mystat,0,sizeof(mystat));
	struct dirent *p;
	dir=opendir(path);

	while((p=readdir(dir))!=NULL){
		int ret1;
		ret1=stat(p->d_name,&mystat);
		if(-1==ret1){
			perror("stat");
			return;
		}
		if(!strcmp(p->d_name,".") || !strcmp(p->d_name,"..")){}
		else{
			func(mystat,p->d_name,new_fd);
		}
	}
	closedir(dir);
	return;
}

void do_ls(char *path,int new_fd){
	DIR *dir;
	struct stat mystat;
	memset(&mystat,0,sizeof(mystat));
	struct dirent *p;
	dir=opendir(path);
	td t_out;
	char type[10]={0};

	while((p=readdir(dir))!=NULL){
		memset(&t_out,0,sizeof(t_out));
		int ret1;
		ret1=stat(p->d_name,&mystat);
		if(-1==ret1){
			perror("stat");
			return;
		}
	
	//标注类型
		if((mystat.st_mode>>12)==4){
			strcpy(type,"Content:  ");
		}
		else if((mystat.st_mode>>12)==8){
			strcpy(type,"File:     ");
		}
		strcpy(t_out.buf,type);
	
	//strcat(t_out.buf,"\n");
		strcat(t_out.buf,p->d_name);
		t_out.len=strlen(t_out.buf);
		send_n(new_fd,(char*)&t_out,4+t_out.len);
	}
	closedir(dir);
	return;
}

void check_send_file(char *name,int new_fd,long size){
	DIR *dir;
	struct stat mystat;
	memset(&mystat,0,sizeof(mystat));
	struct dirent *p;
	char * path=NULL;
	path=getcwd(NULL,0);
	dir=opendir(path);
	printf("client file name:%s\n",name);
	
	while((p=readdir(dir))!=NULL){
		int ret1;
		ret1=stat(p->d_name,&mystat);
		if(-1==ret1){
			perror("stat");
			return;
		}

		if(!strcmp(p->d_name,name) && (8==(mystat.st_mode>>12))){
			//send_file
			printf("find the file in server:%s\n",p->d_name);
			td t;
			memset(&t,0,sizeof(t));
			t.len=strlen(p->d_name);
			strcpy(t.buf,p->d_name);
			send_n(new_fd,(char*)&t,4+t.len);
			int fd;
			fd=open(p->d_name,O_RDONLY);
			if(-1==fd){
				perror("open1");
				exit(-3);
			}
			lseek(fd,size,SEEK_SET);
			while(memset(&t,0,sizeof(t)),(t.len=read(fd,t.buf,sizeof(t.buf)))>0){
				send_n(new_fd,(char*)&t,4+t.len);
			}
			t.len=0;
			send_n(new_fd,(char*)&t.len,4);
			close(fd);
			break;
		}
	}
}


void deliver_command(int new_fd){
	td t_in,t_out;
	//check到底是什么命令
	//给出回应
	char order_head[10]={0};
	char order_path[1000]={0};
	char *path=NULL;//getcwd专用path
	

	chdir("../../user1");
	while(1){
		memset(&t_in,0,sizeof(t_in));
		recv_n(new_fd,(char*)&t_in.len,4);
		recv_n(new_fd,t_in.buf,t_in.len);
		printf("client:%s\n",t_in.buf);
		printf("len=%d\n",t_in.len);		
		//传出这个命令并处理
		
		memset(&t_out,0,sizeof(t_out));	
		if(!strcmp(t_in.buf,"pwd")){//pwd
			/*memset(path,0,sizeof(path));*/
			int cutlen=strlen("/home/ziboris/FTP_ziboris");
			path=NULL;
			path=getcwd(NULL,0);
			char path2[100]={0};
			int cutc;//cutcheck
			for(cutc=0;cutc<strlen(path)-cutlen;cutc++){
				path2[cutc]=path[cutc+cutlen];
			}
			strcpy(t_out.buf,path2);
			t_out.len=strlen(t_out.buf);
			free(path);
			send_n(new_fd,(char*)&t_out,4+t_out.len);
		}
		
		else if(!strncmp(t_in.buf,"ls",2)){//ls
			if(!strcmp(t_in.buf,"ls -l")){//纯粹的ls -l
				path=NULL;
				path=getcwd(NULL,0);
				do_ls_l(path,new_fd);
				//printf("1\n");
			}
			else if(!strcmp(t_in.buf,"ls")){//纯粹的ls
				path=NULL;
				path=getcwd(NULL,0);
				do_ls(path,new_fd);
			}
			else{//跟了路径参数的ls
				printf("2\n");
			}
		}

		else if(!strncmp(t_in.buf,"cd",2)){//cd
			int cd_l;//cd lenth
			cd_l=strlen(t_in.buf);
			int cd_c;//cd count 
			char cd_p[100]={0};//cd path
			for(cd_c=0;cd_c<=(cd_l-4);cd_c++){
				cd_p[cd_c]=t_in.buf[cd_c+3];
			}

			if(!strcmp(cd_p,".")){
			}
			else if(!strcmp(cd_p,"..")){
				//比较路径 如果pwd小于应该的路径则无效
				int cutlen1=strlen("/home/ziboris/FTP_ziboris/user1/");
				if(strlen(getcwd(NULL,0))>cutlen1){
					chdir("../");
				}
				else{
					td cd_back;//"this is root content!"
					cd_back.len=strlen("this is root content!");
					strcpy(cd_back.buf,"this is root content!");
					send_n(new_fd,(char*)&cd_back,4+cd_back.len);
				}
			}
			else{
				chdir(cd_p);
			}
		}

		else if(!strncmp(t_in.buf,"gets",4)){//gets
			//接收客户端本地文件到小并偏移
				
			int gets_l;
			gets_l=strlen(t_in.buf);
			int gets_c;
			char gets_p[100]={0};
			for(gets_c=0;gets_c<=(gets_l-6);gets_c++){
				gets_p[gets_c]=t_in.buf[gets_c+5];
			}
			//接受大小
			long* psize;
			recv_n(new_fd,(char*)psize,4);
			check_send_file(gets_p,new_fd,*psize);
		}
			
		else if(!strncmp(t_in.buf,"remove",6)){//remove
			int rm_l;
			rm_l=strlen(t_in.buf);
			int rm_c;
			char rm_p[100]={0};
			for(rm_c=0;rm_c<=(rm_l-8);rm_c++){
				rm_p[rm_c]=t_in.buf[rm_c+7];
			}
			remove(rm_p);

			td rm_back;//"remove success"
			rm_back.len=strlen("remove success");
			strcpy(rm_back.buf,"remove success");
			send_n(new_fd,(char*)&rm_back,4+rm_back.len);
		}

		else if(!strncmp(t_in.buf,"puts",4)){//puts
			int pt_l;
			pt_l=strlen(t_in.buf);
			int pt_c;
			char pt_p[100]={0};
			for(pt_c=0;pt_c<=(pt_l-6);pt_c++){
				pt_p[pt_c]=t_in.buf[pt_c+5];
			}
			
			int fd;
			fd=open(pt_p,O_RDWR|O_CREAT,0666);
			if(-1==fd){
				perror("open2");
				exit(-4);
			}

			memset(&t_in,0,sizeof(t_in));
			while(1){
				recv_n(new_fd,(char*)&t_in.len,4);
				if(t_in.len>0){
					recv_n(new_fd,t_in.buf,t_in.len);
					write(fd,t_in.buf,t_in.len);
				}
				else{
					break;
				}
			}
			td pt_back;//"upload success"
			pt_back.len=strlen("upload success");
			strcpy(pt_back.buf,"upload success");
			send_n(new_fd,(char*)&pt_back,4+pt_back.len);
		}

		else if(!strncmp(t_in.buf,"mkdir",5)){//mkdir 
				system(t_in.buf);
		}

		else{}

		//sleep(5);
	}
	return ;
}
	


/*
		int i=0;
		while(t.buf[i]!=' '){
			i++;
		}//求出空格位在字符串数组中的位置

		int m;
		for(m=0;m<i;m++){
			order_head[m]=t.buf[m];
		}
		for(m=0;m<strlen(t.buf)-i-1;m++){
			order_path[m]=t.buf[m+i+1];
		}
		printf("head=%s\n",order_head);
		printf("path=%s\n",order_path);
		//收到对应应该答应什么
		//memset(&t,0,sizeof(t));*/
		
