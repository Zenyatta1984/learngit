#include <iostream>

using namespace std;

class singleton{
public:
	static singleton* getinstance(){
		if(_pinstance==NULL){
			_pinstance=new singleton;
		}
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

singleton* singleton::_pinstance=NULL;

int main(void){
	singleton::getinstance()->print();
//	singleton::destroy();

	return 0;
}

