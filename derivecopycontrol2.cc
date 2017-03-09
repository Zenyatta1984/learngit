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

	base()
	:_pdata(new char[1])
	{
		cout<<"base()"<<endl;
	}

	base(const char * pdata)
	:_pdata(new char[strlen(pdata)+1])
	{
		cout<<"base(const char*)"<<endl;
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
		cout<<"~base() _pdata"<<endl;
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
	derived(const char * pdata,const char *pdata2)
	:base(pdata)//显示调用基类的含参构造函数
	,_pdata2(new char[strlen(pdata2)+1])
	{
		cout<<"derived(const char*)"<<endl;
		strcpy(_pdata2,pdata2);
	}

	derived(const derived & rhs)
	:base(rhs)//显式调用基类的复制构造函数
	,_pdata2(new char[strlen(rhs._pdata2)+1])
	{
		cout<<"derived (const derived &)"<<endl;
		strcpy(_pdata2,rhs._pdata2);
	}

	//重载的运算符函数也不能继承
	derived & operator=(const derived &rhs)
	{
		cout<<"derived & operator=(const derived &)"<<endl;
		if(this!=&rhs){
			base::operator=(rhs);//显式调用基类中的重构函数

			delete []_pdata2;
			_pdata2=new char[strlen(rhs._pdata2)+1];
			strcpy(_pdata2,rhs._pdata2);
		}
		return *this;
	}

	//析构函数也不能继承
	~derived(){
		cout<<"~derived() _pdata2"<<endl;
		delete []_pdata2;
	}
	
	friend std::ostream& operator<<(std::ostream &os,const derived & rhs);

private: 
	char *_pdata2;
};


std::ostream & operator<<(std::ostream &os, const base& rhs){
	os<<rhs._pdata;
	return os;
}
std::ostream & operator<<(std::ostream &os, const derived& rhs){
	os<<(base)rhs;
	return os;
}


int main(void){
	derived myd1("hello",",world");
	//cout<<"myd1="<<myd1<<endl;


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
