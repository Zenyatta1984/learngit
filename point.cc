#include <math.h>
#include <iostream>
using std::cout;
using std::endl;

class line;//前向声明

class point{
	//友元类
	friend line;

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


class line{
public:
	void setpoint(point *pt, int x,int y){
		pt->_x=x;
		pt->_y=y;
	}

	float distance(const point &p1,const point &p2){
		return sqrt((p1._x-p2._x)*(p1._x-p2._x)+
					(p1._y-p2._y)*(p1._y-p2._y));
	}
};

int main(void){
	point p1(1,2);
	point p2(3,4);
	
	line myline;

	p1.print();
	cout<<"--->";
	p2.print();
	cout<<"distance="<<myline.distance(p1,p2)<<endl;



	cout<<endl;
	cout<<"check2:"<<endl;
	myline.setpoint(&p1,4,5);
	p1.print();
	cout<<"distance2="<<myline.distance(p1,p2)<<endl;

	return 0;
}







