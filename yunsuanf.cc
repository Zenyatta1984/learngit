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
	computer(const char * sb, int p)
	:_brand(new char[strlen(sb)+1])
	, _price(p)
	{
		strcpy(_brand,sb);
		cout<<"gz function"<<endl;
	}

	~computer(){
		delete []_brand;
		cout<<"xg function"<<endl;
	}

//试一试只定义一个复制构造函数看看是否能够满足赋值运算符的要求
//不行 还是会出现double free问题 因此复制构造函数确实不进行调用
	computer(const computer & rhs)
	:_brand(new char[strlen(rhs._brand)+1])
	,_price(rhs._price)
	{
		strcpy(this->_brand,rhs._brand);
		cout<<"fuzhi gz function"<<endl;
	}
//因此还是要创建赋值表达式函数
	computer &operator=(const computer &rhs){
		cout<<"fuzhi biaodashi function"<<endl;
		delete []this->_brand;
		_brand=new char[strlen(rhs._brand)+1];
		this->_price=rhs._price;
		return *this;
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
int main(){
	
//	com1.setbrand("HP");
//	com1.setprice(1000);

	computer com2("thinkpad",500);
	com2.print();

//	com1.print();
	cout<<endl;
	computer com3("lianxiang",100);
	com3=com2;
	cout<<"fuzhi yuansuanfu end"<<endl;
	return 0;
}







