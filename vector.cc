//#include <vector> 
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;


void showcapacity(vector<int> & myvec){
	cout<<"vec size="<<myvec.size()<<endl;
	cout<<"vec capacity="<<myvec.capacity()<<endl;
	cout<<"-----------------------------------"<<endl;
}


int main(void){
	vector<int> myvec;//注意类型声明
	myvec.reserve(5);
	showcapacity(myvec);
	cout<<endl;

	myvec.push_back(1);
	showcapacity(myvec);
	myvec.push_back(2);
	showcapacity(myvec);
	myvec.push_back(4);
	showcapacity(myvec);
	myvec.push_back(3);
	showcapacity(myvec);
	myvec.push_back(5);
	showcapacity(myvec);
	myvec.push_back(9);
	showcapacity(myvec);

	int i=3;//顺序输出vector的三种方法
	if(i==1){//size_t 数组
		for(size_t k=0;k!=myvec.size();++k){
			cout<<myvec[k]<<" ";
		}
		cout<<endl;
	}
	else if(2==i){
		vector<int>::iterator it;
		for(it=myvec.begin();it!=myvec.end();++it){
			cout<<*it<<" ";
		}
		cout<<endl;
	}
	else if(3==i){
		for(auto & elem: myvec){
			cout<<elem<<" ";
		}
		cout<<endl;
	}
	return 0;
}

