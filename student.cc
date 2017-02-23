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


private:
	int _no;
	char *_name;
};

int main(void){
	student *s1=new student(100,"Mike");//堆对象
	s1->print();

	delete s1;

	student s2(101,"Jackie");//栈对象
	s2.print();

	return 0;
}
