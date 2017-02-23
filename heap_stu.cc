#include <string.h>
#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;

class student{
public:
	student(int no,const char *name)
	:_no(no)
	,_name(new char[strlen(name)+1])
	{
		cout<<"student(int,const char)"<<endl;
		strcpy(_name,name);
	}

	void print(){
		cout<<"number:"<<_no<<endl;
		cout<<"name:"<<_name<<endl;
	}

	void *operator new(size_t size){//size=sizeof(student)编译时候自动转换
		cout<<"void* operator new(size_t)"<<endl;
		void *p=malloc(size);
		return p;
	}

	void operator delete(void *p){//p=s1
		cout<<"void operator delete(void*)"<<endl;
		free(p);
	}

	void destroy(){
		cout<<"void destroy()"<<endl;
		delete this;
	}
private:
//public:
	~student(){
		cout<<"~student"<<endl;
		delete []_name;
	}

private:
	int _no;
	char *_name;
};

int main(void){
	student *s1=new student(100,"DUI");//堆对象
	s1->print();
	s1->destroy();		
//	delete s1;
/*
	student s2(101,"Zhan");//栈对象
	s2.print();
	s2.destroy();
*/
	return 0;
}
