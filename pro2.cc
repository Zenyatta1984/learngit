 ///
 /// @file    pro2.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-02-04 08:26:44
 ///
#include <stdio.h>
#include <string.h>

#include <iostream>
using std::cout;
using std::endl;

class string{
public:
	string(){
		_pstr=new(char[20]);
		cout<<"hiden gz function"<<endl;
	}
	string(const char *pstr)
	:_pstr(new char[strlen(pstr)+1]){
		strcpy(this->_pstr,pstr);
		cout<<"gz function"<<endl;
	}

	string (const string & rhs)
	:_pstr(new char[strlen(rhs._pstr)+1]){
		strcpy(this->_pstr,rhs._pstr);
	}

	string & operator=(const string & rhs)
	{
		if(this==&rhs) return *this;
		delete []this->_pstr;
		_pstr=new char[strlen(rhs._pstr)+1];
		strcpy(this->_pstr,rhs._pstr);
	}

	~string(){
		delete []_pstr;
		cout<<"hiden xg function"<<endl;
	}

	void print(){
		cout<<"void print()"<<endl;
		printf("string=%s\n",_pstr);
	}
private:
	char *_pstr;
};

int main(void){
	string str1;
	str1.print();
	
	string str2="hello,world";
	string str3="wangdao";
	str2.print();
	str3.print();

	str2=str3;
	str2.print();
	
	string str4=str3;
	str4.print();
	return 0;
}
