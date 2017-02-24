 
#include <iostream>
using std::cout;
using std::endl;

class queue{
public:
	queue(int size)
	:_front(0)
	,_rear(0)
	,_size(size)
	,_arr(new int[size])
	{
	}

	~queue(){
		delete []_arr;
	}
	
	void push(int num){//rear先赋值 再++
		if(!full()){
			_arr[_rear++]=num;
			_rear=_rear%_size;
		}
		else{
			cout<<"queue is full"<<endl;
		}
	}

	void pop(){
		if(!empty()){
			++_front;
			_front=_front%_size;
		}
		else{
			cout<<"queue is full"<<endl;
		}
	}

	bool full(){//队列大小=size-1
		return (_rear+1)%_size==_front;
	}

	bool empty(){
		return _front==_rear;
	}

	int gethead(){
		return _arr[_front];
	}

	int gettail(){
		return _arr[(_rear+_size-1)%_size];
	}

private:
	int _front;
	int _rear;
	int _size;
	int *_arr;
};

int main(void){
	queue que(10);
	cout<<">>>check if queue is empty?	"<<que.empty()<<endl;

	for(int i=1;i<=10;++i){
		que.push(i);
	}
	cout<<">>>check if queue is empty?	"<<que.empty()<<endl;
	
	while(!que.empty()){
		cout<<que.gethead()<<" ";
		que.pop();
	}
	cout<<endl;

	return 0;
}
	





