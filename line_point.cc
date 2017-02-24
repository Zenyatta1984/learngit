#include <math.h>
#include <iostream>
using std::cout;
using std::endl;

			//line 放上面要求有point
			//point放上面要求i有line的友元
class point;//前向声明

class line{
public:
	float distance(const point &p1,const point &p2);//内部不要写明point的具体使用 因为还没有定义point
};

class point{
	//全局函数之友元函数
	friend float line::distance(const point&,const point &);//类内部开头申明友元
	//由于调用了line类的函数 因此需要知道line的实现 而相对来说line不需要point的实现 只要知道是一个类就行

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

float line::distance(const point &p1,const point &p2){
	return sqrt((p1._x-p2._x)*(p1._x-p2._x)+
				(p1._y-p2._y)*(p1._y-p2._y));
}

int main(void){
	point p1(1,2);
	point p2(3,4);
	line myline;

	p1.print();
	cout<<"--->";
	p2.print();
	cout<<"distance="<<myline.distance(p1,p2)<<endl;
	return 0;
}
