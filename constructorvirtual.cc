 ///
 /// @file    constructorvirtual.cc
 /// @date    2017-03-10 11:08:00
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class base0
{
public:
	base0(){cout<<"base0()"<<endl;}
	~base0(){cout<<"~base0()"<<endl;}

	virtual void func1(){
		cout<<"base0::func1()"<<endl;
	}

	virtual void func2(){
		cout<<"base0::func2()"<<endl;
	}

};

class base1
:public base0
{
public:
	base1():base0()
	{
		cout<<"base1()"<<endl;
		func1();
	}

	~base1(){
		func2();
		cout<<"~base2()"<<endl;
	}

	void func1(){
		cout<<"base1::func1()"<<endl;
	}

	void func2(){
		cout<<"base1::func2()"<<endl;
	}
};

class sub:
public base1
{
public:
	sub():base1()
	{
		cout<<"sub()"<<endl;
	}

	void func1(){
		cout<<"sub::func1()"<<endl;
	}
	void func2(){
		cout<<"sub::func2()"<<endl;
	}
	
	~sub(){
		cout<<"~sub()"<<endl;
	}

};

int main(void){
	cout<<"constuctor:"<<endl;
	sub mysub;

	cout<<endl;
	cout<<"destuctor:"<<endl;
	return 0;
}

	






