#include <algorithm> 
#include <iostream>
#include <vector>
#include <deque>
#include <string>

using std::string;
using std::deque;
using std::cout;
using std::endl;
using std::vector;

void print(int num){
	cout<<num<<endl;
}

void func(string &str){
	str=str+"123";
}

int main(void){
	vector<int> myvec={1,2,3,4,5};
	for_each(myvec.begin(),myvec.end(),print);


	cout<<"---"<<endl;
	string arr[3]={"hello","my","world"};
	deque<string> mydeque(arr,arr+3);

	for_each(mydeque.begin(),mydeque.end(),func);

	deque<string>::iterator it;
	for(it=mydeque.begin();it!=mydeque.end();++it){
		cout<<*it<<endl;
	}

	return 0;
}
