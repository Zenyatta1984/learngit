 ///
 /// @file    virtualfunc1.cc
 /// @date    2017-03-10 09:47:05
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class base{
public:
	virtual void display(){
		cout<<"base::display()"<<endl;
	}

private:
	double _d0;
};

class child1
:public base
{
public:
	void display()
	{
		cout<<"child1: display()"<<endl;
	}

private:
	double _d1;
};

class child2
:public base
{
public:
	void display(){
		cout<<"chils2:display()"<<endl;
	}
private:
	double _d2;
};

void display(base* X){
	X->display();
}

int main(void){
	base base;
	child1 child1;
	child2 child2;

	//通过对象名调用和虚函数没有关系
	base.display();
	child1.display();
	child2.display();

	//如何证明display是虚函数呢：
	//含有该虚函数的类的对象都能直接使用该函数名
	display(&child1);
	display(&child2);
	display(&base);

	return 0;
}
