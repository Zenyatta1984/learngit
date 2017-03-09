 ///
 /// @file    derivecopycontrol1.cc
 /// @date    2017-03-09 08:53:06
 ///
 //
 //
#include <string.h>

#include <memory> 
#include <iostream>

using std::cout;
using std::endl;

class base{
public:
	base(const char * pdata)
	:_pdata(new char[strlen(pdata)+1])
	{
		cout<<"base(const char*"<<endl;
		strcpy(_pdata,pdata);
	}

	base(const base &rhs)
	:_pdata(new char[strlen(rhs._pdata)+1])
	{
		cout<<"base(const base&)"<<endl;
		strcpy(_pdata,rhs._pdata);
	}

	base& operator=(const base& rhs)
	{
		cout<<"base & operator=(const base&)"<<endl;
		if(this!=&rhs){
			delete []_pdata;
			_pdata=new char[strlen(rhs._pdata)+1];
			strcpy(_pdata,rhs._pdata);
		}
		return *this;
	}

	~base(){
		//cout<<"~base()"<<endl;
		delete []_pdata;
	}


	friend std::ostream& operator<<(std::ostream &os,const base& rhs);

private:
	char* _pdata;
};


class derived
:public base
{
public:
	derived(const char * pdata)
	:base(pdata)//显示调用基类的含参构造函数
	{
		cout<<"derived(const char*)"<<endl;
	}

	friend std::ostream& operator<<(std::ostream &os,const derived & rhs);
};


std::ostream & operator<<(std::ostream &os, const base& rhs){
	os<<rhs._pdata;
	return os;
}
std::ostream & operator<<(std::ostream &os, const derived& rhs){
	os<<(base)rhs;//???????????
	return os;
}


int main(void){
	derived myd1("hello");
	cout<<"myd1="<<myd1<<endl;

	//derived myd2=myd1;
	//cout<<"myd2="<<myd2<<endl;
#if 0
	cout<<"--"<<endl;
	derived myd3(",world");

	cout<<myd3<<endl;
	myd3=myd1;
	cout<<myd3<<endl;
#endif
	return 0;
}
