 ///
 /// @file    test.cc
 /// @date    2017-03-08 21:59:36
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class a{
public:
	a(){
		cout<<"a()"<<endl;
	}
	~a(){
		cout<<"~a()"<<endl;
	}
};

class b:public a
{
public:
	b(){
		cout<<"b()"<<endl;
	}

	~b(){
		cout<<"~b()"<<endl;
	}


	class c{
	public:
		c(){
			cout<<"c()"<<endl;
		}

		~c(){
			cout<<"~c()"<<endl;
		}

	};
};

int main(){
	a mya;
	b myb;
	b::c myc;
	
	cout<<"----"<<endl;
	return 0;
}

