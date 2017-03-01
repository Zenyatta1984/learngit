 
#include <iostream>
using std::cout;
using std::endl;

template<typename T1>
class convert{
public:
	template <typename T2>
	T2 func(T1 t);
};

template<typename T1>
template<typename T2>
T2 convert<T1>::func(T1 t)
{
	return T2(t);
}

int main(void){
	convert<int> myconvert;
	cout<<myconvert.func<char>(65)<<endl;

	return 0;
}
