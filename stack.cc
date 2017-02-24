 
#include <iostream>
using std::cout;
using std::endl;

class stack{
public:
	stack(int size)
	:_top(-1)
	,_size(size)
	,_arr(new int (size))
	{

	}

	~stack(){
		delete []_arr;
	}

	void push(int num){
		if(false==full()){
			_arr[++_top]=num;
		}
		else{
			cout<<"stack is full"<<endl;
		}
	}

	void pop(){
		if(false == empty()){
			--_top;
		}
		else{
			cout<<"stack is empty"<<endl;
		}
	}

	int top(){
		return _arr[_top];
	}

	bool empty(){
		return _top==-1;
	}

	bool full(){
		return _top==(_size-1);
	}

private:
	int _top;
	int _size;
	int *_arr;
};

int main(void){
	stack mystack(11);
	cout<<">>>if the stack is empty?  "<<mystack.empty()<<endl;
#if 0	
	mystack.push(1);
	cout<<">>>if the stack is empty?  "<<mystack.empty()<<endl;
	cout<<">>>if the stack is full?  "<<mystack.full()<<endl;
	
#endif

	for(int i=1;i<=10;++i){
		mystack.push(i);
	}
	cout<<">>>if the stack is empty?  "<<mystack.empty()<<endl;
	
	while(!mystack.empty()){
		cout<<mystack.top()<<" ";
		mystack.pop();
	}
	cout<<endl;
	return 0;

}

	
