 ///
 /// @file    easyfz.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-02-03 17:23:48
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class point{
private:
	int _x;
	int _y;
public:
	point(int a,int b)
	:_x(a)
	,_y(b)
	{
		cout<<"hiden gz function"<<endl;
	}

	point(const point & rhs)
	:_x(rhs._x)
	,_y(rhs._y){
		cout<<"hiden fz function"<<endl;
	}

	~point(){
		cout<<"hiden xg function"<<endl;
	}
};

int main(){
	point p1(1,2);
	point p2=p1;

	return 0;
}
