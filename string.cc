#include <stdio.h>
#include <string.h>
#include <string> 
#include <iostream>
using std::cout;
using std::endl;
using std::string;

int main(void){
	string s1="helloworld";
	string s2="dcbkjsbdckjsbd";
	string s3=s1;

	cout<<"sizeof(s1)="<<sizeof(s1)<<endl;
	cout<<"sizeof(s2)="<<sizeof(s2)<<endl;
	cout<<"sizeof(s3)="<<sizeof(s3)<<endl;
//####	
	const char *p1=s1.c_str();
	const char *p2=s2.c_str();
	const char *p3=s3.c_str();

	printf("p1=%p\n",p1);
	printf("p2=%p\n",p2);
	printf("p3=%p\n",p3);


	cout<<"------------"<<endl;
	s3[0]='a';
//####	
	p1=s1.c_str();
	p2=s2.c_str();
	p3=s3.c_str();

	printf("p1=%p\n",p1);
	printf("p2=%p\n",p2);
	printf("p3=%p\n",p3);


	return 0;
}
