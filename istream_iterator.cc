#include "../include.h"

int main(void){
	vector<int> myvec;
	cout<<"vec capacity="<<myvec.capacity()<<endl;

	istream_iterator<int,string> isi(cin);
	copy(isi,istream_iterator<int>(),back_inserter(myvec));

	cout<<"vec's capacity="<<myvec.capacity()<<endl;

	for(auto & elem:myvec){
		cout<<elem<<" ";
	}

	cout<<endl;
	return 0;
}
