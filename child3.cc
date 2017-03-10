 ///
 /// @file    child3.cc
 /// @date    2017-03-10 10:53:39
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class base{
public:
	base(){
	}

	virtual void display(){
		cout<<"base::display()"<<endl;
	}

	void callbase1(){
		display();
	}

	void callbase2(){
		base::display();
	}
};

class child
:public base
{
public:
	void display(){
		cout<<"child::display()"<<endl;
	}

	void callchild(){
		display();
	}

};

int main(void){
	base mybase;
	child mychild;

	mybase.callbase1();
	mychild.callchild();

	cout<<endl;

	base *pbase= &mybase;
	pbase->callbase1();
	pbase->callbase2();

	base * pbase2=&mychild;
	pbase2->callbase1();
	pbase2->callbase2();


	return 0;
}




