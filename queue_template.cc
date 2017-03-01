#include <string>
#include <iostream>

#define M 10
using std::cout;
using std::endl;
using std::string;

template<typename T,int size=M>
class queue{
public:
	queue();
	//~queue();

	void push(const T&);
	void pop();
	bool empty();
	bool full();
	const T& gethead();
	const T& gettail();

private:
	int _head;
	int _tail;
	int _size;
	T _arr[size];
};

template<typename T,int size>
queue<T,size>::queue()
:_size(size)
,_head(0)
,_tail(0)
//,_arr(new T[size])
{
}

template<typename T,int size>
bool queue<T,size>::empty()
{
	return (_head==_tail);
}

template<typename T,int size>
bool queue<T,size>::full()
{
	return (0==(_tail+1+_size-_head)%_size);
}

template<typename T,int size>
const T& queue<T,size>::gethead()
{
	return _arr[_head];
}

template<typename T,int size>
const T& queue<T,size>::gettail()
{
	return _arr[(_size+_tail-1)%_size];
}

template<typename T,int size>
void queue<T,size>::push(const T& elem)
{
	if(!full()){
		_arr[_tail++]=elem;
		_tail=_tail%_size;
	}
	else cout<<"the queue is full!"<<endl;
}

template<typename T,int size>
void queue<T,size>::pop(){
	if(!empty()){
		++_head;
		_head=_head%_size;
	}
	else cout<<"the queue is empty!"<<endl;
}

int test1(void){
	queue<int,10> myqueue;
	cout<<"is the queue empty?"<<myqueue.empty()<<endl;

	myqueue.push(0);
	cout<<"is the queue empty?"<<myqueue.empty()<<endl;

	for(int i=1;i!=11;++i){
		myqueue.push(i);
	}

	while(!myqueue.empty()){
		cout<<myqueue.gethead()<<" ";
		myqueue.pop();
	}

	cout<<endl;

	return 0;
}


int main(void){
	queue<string,11> myqueue;
	cout<<"is the queue empty?"<<myqueue.empty()<<endl;

	myqueue.push("AA");
	cout<<"is the queue empty?"<<myqueue.empty()<<endl;

	for(int i=1;i!=11;++i){
		char ch='A'+i;
		string s(2,ch);
		myqueue.push(s);
	}

	while(!myqueue.empty()){
		cout<<myqueue.gethead()<<" ";
		myqueue.pop();
	}

	cout<<endl;
	return 0;
}

