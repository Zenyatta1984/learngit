 
#include <iostream>
using std::cout;
using std::endl;

class singleton{
public:
	singleton* get(){
		_psingle=new(singleton);
		return _psingle;
	}

	void destroy

private:
	singleton(){
	}
private:
	singleton *_psingle; 
}

int main(void){
	singleton *ps1=new(singleton);
}
