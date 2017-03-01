#include <string.h>
#include <stdio.h>
#include <iostream>
#include <ostream>

using std::cout;
using std::endl;
using std::ostream;
//using std::string;

class mystring{

	friend ostream& operator<<(ostream &os,const mystring &rhs);
public:
	mystring();
	mystring(const char *pstr);
	mystring(const mystring &rhs);
	~mystring();

	mystring &operator= (const mystring &rhs);

	int size() const{
		return strlen(_pstr);
	}

	const char* c_str() const{
		return _pstr;
	}
	
	//
	void initRefcount(){
		_pstr[size()+1]=1;
	}

	//
	void increaseRefcount(){
		++_pstr[size()+1];
	}

	//
	void decreaseRefcount(){
		--_pstr[size()+1];
	}
	////	
	int usecount()const {
		return _pstr[size()+1];
	}

	
	char & operator[](int x);
	//const char & operator[](int x)const;
private:
	char *_pstr;
	
};

//################本例子采用类内声明类外定义的方式


mystring::mystring()
:_pstr(new char[2])//多开一个空间存放引用计数,最大值为255
{
	//cout<<"mystring()"<<endl;
	//_pstr[size()+1]=1;
	initRefcount();
}

mystring::mystring(const char* pstr)
:_pstr(new char[strlen(pstr)+2])
{
	cout<<"mystring()"<<endl;
	strcpy(_pstr,pstr);
	//_pstr[size()+1]=1;
	initRefcount();
}

mystring::mystring(const mystring &rhs)
:_pstr(rhs._pstr)
{	
	increaseRefcount();
	//++_pstr[size()+1];
}

mystring::~mystring(){
	if(--_pstr[size()+1]==0){
		//cout<<"~mystring()"<<endl;
		delete []_pstr;
	}
}


ostream& operator<<(ostream &os,const mystring &rhs){
	os << rhs._pstr;
	return os;
}

mystring& mystring::operator=(const mystring& rhs)
{
	if(this==&rhs)
		return *this;
	decreaseRefcount();
	if(usecount()==0)
		delete []_pstr;
	_pstr=rhs._pstr;
	increaseRefcount();

	return *this;
}
//myatempt
char &mystring::operator[](int x)
{	
	static char chnull='\0';

	

char & mystring::operator[](int x)
{
	static char chnull='\0';
	if(x>=0 && x<size()){
		if(usecount()>1){
			decreaseRefcount();
			char *ptmp=new char[size()+2];
			strcpy(ptmp,_pstr);
			_pstr=ptmp;
			initRefcount();
		}
		return _pstr[x];
	}
	else 
		return chnull;
}
#if 0
const char & mystring::operator[](int x)const
{
	static char chnull2='\0';
	if(x>=0 && x<size()){
		return _pstr[x];
	}
	else return chnull2;
}
#endif
//###################main
int main(void){
	mystring s1="helloworld";
	mystring s2=s1;
	mystring s3=s2;

	cout<<"s1="<<s1<<endl;
	cout<<"s1="<<s1<<endl;
	cout<<"s1="<<s1<<endl;

	printf("&s1=%p\n",s1.c_str());
	printf("&s2=%p\n",s2.c_str());
	printf("&s3=%p\n",s3.c_str());
	cout<<"s1.usecount="<<s1.usecount()<<endl;
	cout<<"s2.usecount="<<s2.usecount()<<endl;
	cout<<"s3.usecount="<<s3.usecount()<<endl;

	cout<<"-------------"<<endl;
#if 1
	cout<<"when read happens"<<endl;
	cout<<s2[0]<<endl;

	printf("&s1=%p\n",s1.c_str());
	printf("&s2=%p\n",s2.c_str());
	printf("&s3=%p\n",s3.c_str());
	cout<<"s1.usecount="<<s1.usecount()<<endl;
	cout<<"s2.usecount="<<s2.usecount()<<endl;
	cout<<"s3.usecount="<<s3.usecount()<<endl;


	cout<<"---"<<endl;
#endif

#if 0
	cout<<"when write happens"<<endl;
	s3[0]='H';
	cout<<s3<<endl;

	printf("&s1=%p\n",s1.c_str());
	printf("&s2=%p\n",s2.c_str());
	printf("&s3=%p\n",s3.c_str());
	cout<<"s1.usecount="<<s1.usecount()<<endl;
	cout<<"s2.usecount="<<s2.usecount()<<endl;
	cout<<"s3.usecount="<<s3.usecount()<<endl;
#endif
	cout<<"-------------"<<endl;

	return 0;
}

