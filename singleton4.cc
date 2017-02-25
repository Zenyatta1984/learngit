#include <stdlib.h>
#include <pthread.h>
#include <iostream>
//atexit 进程正常退出之后会调用atexit函数中注册的函数
using namespace std;

class singleton{
public:

	static singleton *getinstance(){
		pthread_once(&_once,init);
		return _pinstance;
	}

	static void init(){
		_pinstance=new singleton;
		atexit(destroy);
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
	static pthread_once_t _once;
};

singleton* singleton::_pinstance=NULL;//就已经创建 /进入main函数之前
pthread_once_t singleton::_once=PTHREAD_ONCE_INIT;

int main(void){
	singleton::getinstance()->print();
//	singleton::destroy();
	
//	atexit(singleton::destroy);
	return 0;
}

