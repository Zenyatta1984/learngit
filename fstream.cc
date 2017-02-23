#include <fstream> 
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::cin;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;


int main(void){
	fstream fs("abc.txt");
	if(!fs.good()){
		cout<<"fstream open error"<<endl;
		fs.close();
		return -1;
	}

	int ival;
	for(int i=0;i!=10;++i){
		cin >> ival;
		fs << ival <<" ";//扮演输出流
	}
	
	int pos;
	pos=fs.tellp();
	fs.seekg(0,std::ios::beg);

	for(int j=0;j!=10;++j){
		fs >> ival;
		cout<<ival<<" ";
	}
	cout <<endl;
	
	fs.close();
	return 0;
}
