#include <iterator> 
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::ostream_iterator;
using std::vector;

int main(){
	vector<int> myvec={1,2,3,4,5};
	
	ostream_iterator<int> osi(cout," ");
	std::copy(myvec.begin(),myvec.end(),osi);

	return 0;
}

