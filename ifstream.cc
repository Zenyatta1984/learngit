#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;

int main(void){
	ifstream ifs("from.txt");
	if(!ifs.good()){
		cout<<"ifstream open error"<<endl;
		return -1;
	}

	string str;
	vector<string> myvec;
	myvec.reserve(100);
	

	while(getline(ifs,str)){
//		cout<<str<<endl;
		myvec.push_back(str);
	}
	
	for(auto &elem: myvec){
		cout<<elem<<endl;
	}
	return 0;
}

