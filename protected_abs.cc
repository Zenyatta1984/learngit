 ///
 /// @file    protected_abs.cc
 /// @date    2017-03-10 12:40:24
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class base{
protected:
	base(int x)
	:_x(x){}

public:
	void display(){
		cout<<"base::_x="<<_x<<endl;
	}

private:
	int _x;
};

class child
:public base
{
public:
	child(int x)
	:base(x)
	{
		cout<<"child(int)"<<endl;
	}

};

int main(void){
	child child(1);
	child.display();

	return 0;
}
