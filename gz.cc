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
	return 0;
}







