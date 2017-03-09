 ///
 /// @file    inheCons.cc
 /// @date    2017-03-09 13:41:16
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class base{
public:

#if 1
	base(){
		cout<<"base()"<<endl;
	}
#endif

#if 1
	base(int x)
	:_x(x)
	{
		cout<<"base(int)"<<endl;
	}
#endif
public:
//private:
	int _x;
};

class derived
:public base
{
public:
	derived(){
		cout<<"derived()"<<endl;
	}

	derived(int o=0,int i=0)
	:base(o)
	,_i(i)
	{
		cout<<"derived(int)"<<endl;
		cout<<"_x="<<_x<<endl;
		cout<<"_i="<<_i<<endl;
	}
private:
	int _i;
};

int main(void){
	derived myd1(1,2);
	
	return 0;
}


