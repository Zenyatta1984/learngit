 ///
 /// @file    1.cc
 /// @date    2017-03-08 21:22:12
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class base{
private:
	int _x;
public:
	base(){
		cout<<"base()"<<endl;
	}

	base(int x=0)
	:_x(x)
	{
		cout<<"base(int)"<<endl;
	}
};

class derive
:public base
{
	derive(){
		cout<<"derive()"<<endl;
	}

	derive(int y)
	:_y(y)
	{
		cout<<"derive(int)"<<endl;
	}

private:
	int _y;

};

int main(void){
	derive myderive1(10);
	//derive myderive2;
	//
	return 0;
}

