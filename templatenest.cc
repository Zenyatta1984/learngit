 
#include <iostream>
using std::cout;
using std::endl;

template<typename O>
class outside{
public:

	template<typename I>
	class inside{
	public:
		inside(I i)
		:_i(i)
		{}

		void display(){
			cout<<"inside:"<<_i<<endl;
		}
	private:
		I _i;
	};

public:
	outside(O o)
	:_in(o)
	{}

	void display(){
		cout<<"outside:";
		_in.display();
	}
private:
	inside<O> _in;
};

int main(void){
	outside<int>::inside<double> myinside(3.5);

	myinside.display();

	outside<int> myoutside(1);
	myoutside.display();
	return 0;
}

