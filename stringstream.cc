#include <sstream> 
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::string;

int main(void){
	int i1=512;
	int i2=1024;
	stringstream ss;
	ss<<"i1="<<i1<<" i2="<<i2;//整体变成字符串的形式
	
	string s=ss.str();// 
//	cout << s <<endl;

//	string s;
	int tmp;
	while(!ss.eof()){
		ss>>s>>tmp;
		cout<<s<<tmp<<endl;
	}

	return 0;
}
