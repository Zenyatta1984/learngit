#include <vector>
#include <list>
#include <iostream>
using std::cout;
using std::endl;

using std::list;
using std::vector;

template<typename container>
void printcontainer(container & con)
{
	typename container::iterator it;
	for(it=con.begin();it!=con.end();++it){
		cout<<*it<<" ";
	}
	cout<<endl;
}

int main(void){

	cout<<"-----vector----"<<endl;
	vector<int> myvec={1,2,3,4,5};
	printcontainer(myvec);
#if 0
	myvec.push_back(6);
	printcontainer(myvec);

	myvec.pop_back();
	printcontainer(myvec);
#endif

#if 0
	cout<<"vec's push from head:"<<endl;
	myvec.push_front(10);
	printcontainer(myvec);
#endif
	cout<<">>>when contains 5 members:"<<endl;
	cout<<"vec size="<<myvec.size()<<endl;
	cout<<"vec capacity="<<myvec.capacity()<<endl;
	myvec.clear();
	printcontainer(myvec);
	cout<<">>>when clear()"<<endl;
	cout<<"vec size="<<myvec.size()<<endl;
	cout<<"vec capacity="<<myvec.capacity()<<endl;

	cout<<">>>when shrink_to_fit()"<<endl;
	myvec.shrink_to_fit();
	cout<<"vec size="<<myvec.size()<<endl;
	cout<<"vec capacity="<<myvec.capacity()<<endl;


#if 0
	cout<<"-----list-----"<<endl;

	
	double arr[5]={1.1,2.2,3.3,4.4,5.5};
	list<double> mylist(arr,arr+5);
	
	printcontainer(mylist);
	mylist.push_front(7.7);
	printcontainer(mylist);
#endif
	return 0;
}
