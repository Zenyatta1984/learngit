#include <math.h>
#include <iostream>
using std::cout;
using std::endl;

class point{
	//全局函数之友元函数
	friend float distance(const point&,const point &);//类内部开头申明友元

public:
	point(int x,int y)
	:_x(x)
	,_y(y)
	{
		cout<<"point(int,int)"<<endl;
	}

	void print(){
		cout<<"("<<_x
			<<","<<_y
			<<")"<<endl;
	}
private:
	int _x;
	int _y;
};

float distance(const point &p1,const point &p2){
	return sqrt((p1._x-p2._x)*(p1._x-p2._x)+
				(p1._y-p2._y)*(p1._y-p2._y));
}

int main(void){
	point p1(1,2);
	point p2(3,4);

	p1.print();
	cout<<"--->";
	p2.print();
	cout<<"distance="<<distance(p1,p2)<<endl;
	return 0;
}
