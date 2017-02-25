 
#include <iostream>
using std::cout;
using std::endl;

class data{
public:
	int lenth(){
		return 5;
	}

};

class dataptr{

public:
	dataptr()
	:_p(new data)
	{
	}

	~dataptr(){
		delete _p;
	}

	data *operator->(){
		return _p;
	}

private:
	data *_p;
};

int main(void){
	dataptr dp;
	cout<<dp->lenth()<<endl;;
	cout<<(dp.operator->())->lenth()<<endl;
	return 0;
}
