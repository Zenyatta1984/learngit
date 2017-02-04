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
	char _brand[20];
	int _price;
public:
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
	computer com1;
	com1.setbrand("HP");
	com1.setprice(1000);
	com1.print();
	return 0;
}







