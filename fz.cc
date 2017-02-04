 ///
 /// @file    fzgzhs.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-02-03 10:52:05
 ///
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class computer{
private:
	char * _brand;
	int _price;
public:
	computer(){
		cout<<"hiden gz function"<<endl;
	}
	computer(const char * sb, int p)
	:_brand(new char[strlen(sb)+1])
	, _price(p)
	{
		strcpy(_brand,sb);
		cout<<"gz function"<<endl;
	}

//默认的赋值构造函数不能满足类成员中有指针这个要求
//应该自定义复制构造函数，可以不用显式调用
	computer(const computer & rhs)
	:_brand(new char[strlen(rhs._brand)+1])
	,_price(rhs._price)
	{
		strcpy(this->_brand,rhs._brand);
		cout<<"self def fzgz function"<<endl;
	}


	~computer(){
		delete []_brand;
		cout<<"xg function"<<endl;
	}

	void setbrand(const char *sb){
		strcpy(_brand,sb);
	}

	void setprice(int p){
		_price=p;
	}

	void print(){
		cout<<"brand:"<<_brand<<endl;
		cout<<"price:"<<_price<<endl;
	}
};
/*void computer::setbrand(const char *sb)
{
	strcpy(_brand,sb);
}

void computer::setprice(int p)
:_price(p)
{
}

void print(){
	cout<<"brand:"<<_brand<<endl
		<<"price:"<<_price<<endl;
}
*/

void func(computer com_temp){
	com_temp.print();
}

computer getcom(){
	computer com5("lianxiang",50000);
	return com5;
}

int main(){
	
//	com1.setbrand("HP");
//	com1.setprice(1000);

	computer com2("thinkpad",500);
	com2.print();
//	com1.print();
	
	cout<<"------------"<<endl;

	computer *pcom=new computer("Mac",1000);
	pcom->setbrand("MMac");
	pcom->setprice(1001);
	pcom->print();

//	cout<<"---------+++++++"<<endl;
//	computer com3;
//	com3.print();
	
	cout<<"++++++"<<endl;
	computer com4=com2;
	cout<<"cout4.print()"<<endl;
	com4.print();
	cout<<"yishang"<<endl;

	cout<<endl;
	cout<<endl;
	func(com4);
	cout<<"11111"<<endl;

	computer com6=getcom();
	return 0;
}







