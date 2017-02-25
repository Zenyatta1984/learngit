#include <stdlib.h>
#include <iostream>
//atexit 进程正常退出之后会调用atexit函数中注册的函数
using namespace std;

class singleton{
public:
	static singleton* getinstance(){
		if(_pinstance==NULL){
			_pinstance=new singleton;
		}
			atexit(destroy);
		return _pinstance;
		
	}

	static void destroy(){
		if(_pinstance){
			delete _pinstance;
		}

	}

	void print(){
		cout <<"singleton::print()"<<endl;
	}
private:
	singleton(){
		cout<<"singleton()"<<endl;
	}
	~singleton(){
		cout<<"~singleton()"<<endl;
	}

private:
	static singleton* _pinstance;
};

singleton* singleton::_pinstance=NULL;//就已经创建 /进入main函数之前

int main(void){
	singleton::getinstance()->print();
//	singleton::destroy();
	
//	atexit(singleton::destroy);
	return 0;
}

