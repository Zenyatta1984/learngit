//cout<<complex com1<<endl;
//重载输出流运算符
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;


class complex{

	friend complex operator+(const complex &lhs,const complex &rhs);
	friend ostream & operator<<(ostream& os,const complex&rhs);
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

	//返回值应该是流类本身 然后流类继续输出后面值 链式传递
	//并且返回值不能使流对象 不然就是cout的复制
	//严格的双操作参数
#if 0
	ostream &operator<<(ostream &os,const complex &rhs){
		os<<rhs._real<<"+"<<rhs._imag<<"i";
		return os;
	}
#endif
	private:
	double _real;
	double _imag;
};

	ostream &operator<<(ostream &os,const complex &rhs){
		os<<rhs._real<<"+"<<rhs._imag<<"i";
		return os;
	}

//重载
complex operator+(const complex &lhs,const complex &rhs){
	return complex(lhs._real+rhs._real,
				   lhs._imag+rhs._imag);
}



int main(void){
	complex c1(1,2);
//	c1.print();
	cout<<c1<<endl; 

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

