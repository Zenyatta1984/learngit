#include <algorithm> 
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

void print(int num){
	cout<<num<<endl;
}

int main(void){
	vector<int> myvec={1,2,3,4,5};
	for_each(myvec.begin(),myvec.end(),print);

	return 0;
}
