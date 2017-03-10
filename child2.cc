 ///
 /// @file    child2.cc
 /// @date    2017-03-10 10:32:41
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class base{
public:
	virtual base display()
	{
		cout<<"base::display()"<<endl;
	}
#if 1
	void print(){
		cout<<"base::print()"<<endl;
	}
#endif
private:
	int _x;
};

class child
:public base{
public:
	base display()
	{
		cout<<"child::display()"<<endl;
	}
#if 1
	void print(){
		cout<<"child::print()"<<endl;
	}
#endif
};

int test(void){
	cout<<"sizeof(base)="<<sizeof(base)<<endl;
	cout<<"sizeof(child)="<<sizeof(child)<<endl;

	base mybase;
	base *pbase=&mybase;
	pbase->display();

	child mychild;
	child *pchild=&mychild;
	pchild->display();

	cout<<"--"<<endl;

	pbase=&mychild;
	cout<<"pbase->display():"<<endl;
	pbase->display();

	pchild=(child*)&mybase;//报错
	cout<<"pchild->display():"<<endl;
	pchild->display();
	return 0;
}


int main(void){
	//
	//1.对象直接调用
	//2.通过指针或者引用调用函数
	//	2.1 函数是虚函数的话，和指针指向的对象有关
	//	2.2 函数非虚函数的话，和指针的类型有关
}