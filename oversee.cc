 ///
/// @file    oversee.cc
 /// @date    2017-03-09 08:46:28
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Base{
public:
	int func(int i){
		return _x;
	}

protected:
	int _x;
};

class Derive:public Base
{
public:
	int func(){
		_x=9;
		Base::_x=22;
		cout<<"Base::_x="<<Base::_x<<endl;
		cout<<"Derive::_x="<<Derive::_x<<endl;
		return this->_x;
	}
public:
	int _x;
};

int main(void){
	Derive myd;

	cout<<myd.func()<<endl;
	cout<<"--"<<endl;
	cout<<myd.Base::func(1)<<endl;

	return 0;
}


