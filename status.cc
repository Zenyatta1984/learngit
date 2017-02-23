 ///
 /// @file    status.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-02-20 15:25:55
 ///
#include <limits>
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

void printCin(){
	cout<<"badbit:"<<cin.bad()<<endl;
	cout<<"failbit:"<<cin.fail()<<endl;
	cout<<"eodbit:"<<cin.eof()<<endl;
	cout<<"goodbit:"<<cin.good()<<endl;
}

int main(void){
	int num;
	printCin();
	cout<<endl;
	
	while(cin>>num){
		cout<<"number:"<<num<<endl;
	}
	printCin();
	cout<<endl;

	cin.clear();//重置状态 failbit=0
	printCin();
	cout<<endl;

	//cin>>num;
	//不会等待输入 failbit=1 因为字符串还存在缓冲区 没有被输出 
	//需要清空缓存区才行
	cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');//
	cin>>num;
	printCin();

	return 0;
}
