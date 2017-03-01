#include <string> 
#include <iostream>
using std::cout;
using std::endl;
using std::string;

template <typename T, int size=10>
class stack
{
public:
	stack();

	bool empty();
	bool full();
	void push(const T &);
	void pop();
	const T &top() const;

private:
	int _top;
	T _arr[size];
};

template <typename T,int size>
stack<T,size>::stack()
:_top(-1)
{
}

template <typename T,int size>
bool stack<T,size>::empty()
{
	return (_top==-1);
}

template <typename T,int size>
bool stack<T,size>::full()
{
	return (_top==size-1);
}

template <typename T,int size>
void stack<T,size>::push(const T& elem)
{
	if(!full()){
		_arr[++_top]=elem;
	}
	else cout<<"stack is full!"<<endl;
}

template <typename T,int size>
void stack<T,size>::pop()
{
	if(!empty())
		--_top;
	else
		cout<<"stack is empty!"<<endl;
}

template <typename T,int size>
const T & stack<T,size>::top() const
{
	return _arr[_top];
}

int main(void){
	stack<string> mystack;
	cout << "is the stack empty?"<<mystack.empty()<<endl;

	mystack.push("AA");
	cout << "is the stack empty?"<<mystack.empty()<<endl;

	for(int i=1;i!=11;++i){
		char ch=i+'A';
		string s(3,ch);
		mystack.push(s);
	}

	cout<<"is the stack full?"<<mystack.full()<<endl;

	while(!mystack.empty()){
		cout<<mystack.top()<<" ";
		mystack.pop();
	}

	cout<<endl;
	cout<<"is the stack empty?"<<mystack.empty()<<endl;

	return 0;
}




