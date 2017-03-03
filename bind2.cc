#include <functional>
#include <iostream>
using std::cout;
using std::endl;

int func(int x,int y){
	return x+y;
}

class hello{
public:
	int world(int x,int y,int z);
};

int hello::world(int x,int y,int z){
	return (x+y)*z;
}

int main(void){
	using namespace std::placeholders;
	auto f1=std::bind(func,10,_1);
	cout<<f1(30)<<endl;
	
	cout<<"--2--"<<endl;

	hello myhello;
	auto f2=std::bind(&hello::world,myhello,10,_1,_2);
	cout<<f2(10,3,2)<<endl;

	return 0;
}
