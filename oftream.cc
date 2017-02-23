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
using std::ofstream;
using std::vector;

int main(void){
	ofstream ofs("to.txt",std::ios::app);
	if(!ofs.good()){
		cout<<"ofstream open error!"<<endl;
		return -1;
	}
	string str="that's new";

	ofs<<str;
	ofs.close();

	return 0;
}
