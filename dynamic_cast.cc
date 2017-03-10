 ///
 
#include <iostream>
using std::cout;
using std::endl;

class base
{
public:
	base(double d1)
	:_d1(d1)
	{}

	void display(){
		cout<<"base::_d1="<<_d1<<endl;
	}

private:
	double _d1;
};

class derived
:public base
{
public:
	derived(double d1,double d2)
	:base(d1)
	,_d2(d2)
	{}

	void display(){
		base::display();
		cout<<"derived::_d2="<<_d2<<endl;
	}
private:
	int _d2;
};

int main(void){
	base mybase(1.1);
	base mybase2=mybase;
	mybase2.display();

	base* p1=&mybase;
	derived * p2=(derived*)p1;
	p2->display();

	cout<<endl;
	cout<<"---dynamic_cast---"<<endl;
	derived *p3=dynamic_cast<derived*>(p1);
	if(p3){
		p3->display();
	}
	else{
		cout<<"unsafe conversion"<<endl;
	}



	return 0;
}

