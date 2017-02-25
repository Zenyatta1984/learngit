#include <iostream>
//考虑到自动回收：栈对象
//另外一个栈对象的析构函数中释放单例对象的空间 栈对象 全局和静态对象三个能够自动调用析构函数
//
using namespace std;
class singleton{
private:
	class autorelease{
	public:
		autorelease(){
			cout<<"autorelease()"<<endl;
		}

		~autorelease(){
			cout<<"~autorelease()"<<endl;
			if(singleton::_pinstance)
				delete singleton::_pinstance;
		}
	};

public:
	static singleton* getinstance(){
		if(_pinstance==NULL){
			_pinstance=new singleton;
		}
		return _pinstance;
	}

#if 0
	static void destroy(){
		if(_pinstance){
			delete _pinstance;
		}
	}
#endif

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
	static autorelease _ar;//不加static就编程单例模式的一部分了在堆上，不符合
};

singleton::autorelease singleton::_ar;//静态对象成员的初始化不需要传参

singleton* singleton::_pinstance=NULL;

int main(void){
	singleton::getinstance()->print();
//	singleton::destroy();

	return 0;
}

