 
#include <iostream>
using std::cout;
using std::endl;

class complex{

	friend complex operator+(const complex &lhs,const complex &rhs);
public:
	complex(double real=0,double imag=0)
	:_real(real)
	,_imag(imag)
	{
		cout<<"complex(double,double)"<<endl;
	}

//	~complex(){
//		cout<<"~"<<endl;
//	}

	void print(){
		cout<<_real<<"+"<<_imag<<"i"<<endl;
	}


	private:
	double _real;
	double _imag;
};


//重载
complex operator+(const complex &lhs,const complex &rhs){
	return complex(lhs._real+rhs._real,
				   lhs._imag+rhs._imag);
}



int main(void){
	complex c1(1,2);
	c1.print();

	complex c2(3,4);
	c2.print();

	complex c3=c1+c2;
	c3.print();

	c3=c1+complex(5,0);
	c3.print();

	c3=5+c1;
	c3.print();

	cout<<1+2<<endl;

	return 0;
}

