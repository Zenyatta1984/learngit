#include <string.h>
#include <iostream>
#include <string> 

using namespace std;

class chararr{
private:
	int _len;
	char *_pstr;

public:
	chararr(int size)
	:_len(size)
	,_pstr(new char[_len])
	{
		cout<<"chararr(int)"<<endl;
	}

	~chararr(){
		cout<<"~chararr()"<<endl;
		delete []_pstr;
	}

	char &operator[](int x){
		cout<<"char& operator[](int)"<<endl;
		static char ch='\0';
		if(x>=0 && x<_len)
			return _pstr[x];
		else{
			cout<<"out of the range"<<endl;
			return ch;
		}
	}
};



int main(void){
	const char *pstr="helloworld";
	int len=strlen(pstr);
	chararr ca(len);

	int idx;
	for ( idx=0;idx!=len;++idx){
		ca[idx]=pstr[idx];//此处会调用[]
	}

	for(idx=0;idx!=len;++idx){
		cout<<ca[idx];//次数也会调用[]
	}
	cout<<endl;

	return 0;
}



