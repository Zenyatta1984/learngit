 
#include <iostream>
using std::cout;
using std::endl;

template<typename T1,typename T2>
class convert{
public:
	T2 excute(T1 t)
	{
		return (T2)t;
	}
};

int main(void){
	convert<int,double> myconvert;
	cout<<myconvert.excute('A')<<endl;

	return 0;
}
