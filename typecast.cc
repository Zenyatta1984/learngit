 ///
 /// @file    typecast.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-03-08 19:58:52
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class point{
public:
	point(int x=0,int y=0)
	:_x(x)
	,_y(y)
	{
		//cout<<"point(int,int)"<<endl;
	}

	~point(){
		//cout<<"~point(){}"<<endl;
	}

	void print(){
		cout<<"("<<_x
			<<","<<_y
			<<")"<<endl;
	}

	int getx() const{
		return _x;
	}

	int gety() const{
		return _y;
	}
	
private:
	int _x;
	int _y;
};

class point3d
:public point
{
public: 
	point3d(int x,int y,int z)
	:point(x,y)
	,_z(z)
	{
		//cout<<"point3d(int ,int ,int)"<<endl;
	}

	~point3d(){
		//cout<<"~point3d()"<<endl;
	}

	void print(){
		cout<<"("<<getx()
			<<","<<gety()
			<<","<<_z
			<<")"<<endl;
	}

private:
	int _z;
};

int main(void){
	cout<<"sizeof point="<<sizeof(point)<<endl;
	cout<<"sizeof point3d="<<sizeof(point3d)<<endl;

	cout<<"--"<<endl;

	point p1(1,2);
//	p1.print();

	point3d p2(3,4,5);
//	p2.print();

	cout<<"begin"<<endl;
	point* pp1=&p2;
	pp1->print();

	return 0;

}



