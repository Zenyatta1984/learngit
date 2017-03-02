#include <deque>
#include <list>
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::deque;
using std::vector;
using std::list;

template<typename container>
void printcontainer(container & con){
	typename container::iterator it;
	for(it=con.begin();it!=con.end();++it){
		cout<<*it<<" ";
	}
	cout<<endl;
}

int main(void){
	deque<int> mydeque={1,2,3,4,5};
	cout<<"random [] to get"<<endl;
	for(size_t x=0;x!=mydeque.size();++x){
		cout<<mydeque[x]<<endl;
	}
	cout<<endl;
	
	cout<<"iterator to get"<<endl;
	deque<int>::iterator it;
	for(it=mydeque.begin();it!=mydeque.end();++it){
		cout<<*it<<endl;
	}
	cout<<endl;

	cout<<"using func to get"<<endl;
	printcontainer(mydeque);


	cout<<"---"<<endl;

	deque<int> yourdeque(3,5);
	cout<<"yourdeque_origin:";
	printcontainer(yourdeque);
	yourdeque.swap(mydeque);
	cout<<"youdeque been swapt:";
	printcontainer(yourdeque);
	return 0;
}


