#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;
using std::list;

template<typename container>
void printcontainer(contain &con)
{
	typename container::iterator it;
	for(it=con.begin();it!=end();++it){
		cout<<*it<<" ";
	}
	cout<<endl;
}

int main(void){
	vector<int> myvec={1,2,3};

	list<int> mylist;





