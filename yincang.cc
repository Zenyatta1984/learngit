 ///
 /// @file    yincang.cc
 /// @date    2017-03-10 09:52:55
 ///
 
#include <iostream>
using std::cout;
using std::endl;


class base{
public:
	virtual int func(int x)
	{
		cout<<"this is ths base func"<<endl;
		return x;
	}
};

class subclass
:public base 
{
public:
	virtual int func(int x)
	{
		cout<<"this is the sub func"<<endl;
		int y=x;
		return y;
	}
};

void test(base & X){
	cout<<"X="<<X.func(10)<<endl;
}


int main(void){
	base mybase;
	subclass mysub;
	
	cout<<"test(base)"<<endl;
	test(mybase);
	cout<<"test(subclass)"<<endl;
	test(mysub);

	cout<<endl;
	cout<<"成员函数调用func"<<endl;
	mybase.func(10);
	mysub.func(10);
	
	cout<<endl;
	cout<<"ref 1.refbase 2. redsub"<<endl;
	base &refbase=mysub;
	refbase.func(10);
	//subclass &refsub=mybase;
	//refsub.func(10);
#if 0
	cout<<endl;
	cout<<"test ref"<<endl;
	test(refbase);
	test(refsub);
#endif
	return 0;
}


