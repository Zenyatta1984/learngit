#include <functional>
#include <iostream>
using std::cout;
using std::endl;

int func(int x,int y){
	return x+y;
}


int main(void){
	using namespace std::placeholders;
	auto f1=std::bind(func,10,20);
	cout<<f1()<<endl;


	return 0;
}
