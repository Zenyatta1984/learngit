 
#include <iostream>
using std::cout;
using std::endl;

class singleton{
public:
	static singleton* getp(){
		if(NULL==_p0){
			_p0=new singleton;
		}
		return _p0;
	}

	static void destroy(){
		if(_p0)
			delete _p0;
	}
private:
	static singleton * _p0;
	singleton(){}
	~singleton(){}
};

singleton* singleton::_p0=NULL;

int main(){
	singleton *s1=singleton::getp();
	singleton *s2=singleton::getp();

	cout<<s1<<endl;
	cout<<s2<<endl;

	singleton::destroy();
	return 0;
}
