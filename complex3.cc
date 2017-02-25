 
#include <iostream>
using std::cout;
using std::endl;
using std::istream;

class complex{

	friend complex operator+(const complex &lhs,const complex &rhs);
	friend istream & operator>>(istream &,complex &rhs);

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

istream& is operator>>(istream &is,complex &rhs){
	is>>is._real;
	while(is.get()!='*');//*是虚部的开始 中间可以打其他杂七杂八的东西
	is >>rhs._imag;
	return is;
}
	 

int main(void){
	complex c1(1,2);
	c1.print();
#if 0
	complex c2(3,4);
	c2.print();

	complex c3=c1+c2;
	c3.print();

	c3=c1+complex(5,0);
	c3.print();

	c3=5+c1;
	c3.print();

	cout<<1+2<<endl;
#endif 
	return 0;
}

