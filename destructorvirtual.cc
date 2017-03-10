 ///
 /// @file    destructorvirtual.cc
 /// @date    2017-03-10 11:18:55
 ///
#include <string.h>

#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

class base
{
public:
	base(const char * pdata)
	:_pdata(new char[strlen(pdata)+1])
	{
		strcpy(_pdata,pdata);
	}

	void display(){
		cout<<_pdata<<endl;
	}

	//virtual
	~base(){
		cout<<"~base()"<<endl;
		delete []_pdata;
	}

	//friend ostream& operator<<(ostream &os,const base &rhs);
private:
	char * _pdata;
};

class child
:public base
{
public:
	child(const char* p1,const char * p2)
	:base(p1)
	,_pdata2(new char[strlen(p2)+1])
	{
		strcpy(_pdata2,p2);
	}

	~child(){
		cout<<"~child()"<<endl;
		delete []_pdata2;
	}

	//friend ostream& operator<<(ostream &os,const child &rhs);
private:
	char * _pdata2;
};
#if 0
ostream& operator<<(ostream &os,const base &rhs){
	os<<rhs._pdata;
	return os;
}
ostream& operator<<(ostream &os,const child &rhs){
	
	os<<rhs._pdata2;
	return os;
}
#endif


int main(void){
	cout<<"sizeof(base)="<<sizeof(base)<<endl;
	cout<<"sizeof(child)="<<sizeof(child)<<endl;
	
	base *p=new child("hello",",world");
	//cout<<*(p+1)<<endl;
	delete p;

	return 0;
}

