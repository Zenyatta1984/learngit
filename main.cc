#include <string.h>
#include <vector> 
#include <iostream>
#include <string>
#include <fstream>
using std::cout;
using std::endl;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::string;

class word{
public:
	/*构造函数*/
	word(int num,string wordname)
	:_count(num)
	,_wordname=wordname
	{}

	void word_read();

	void word_check();


public:
	int _count;
	string _wordname;
};


int main(void){
	
	word myword;
	string stemp;

	ifstream ifs("The_Holy_Bible.txt");
	if(!ifs.good()){
		cout<<"ifstream open error"<<endl;
		ifs.close();
		return -1;
	}

	ofstream ofs("to.txt");
	if(!ofs.good()){
		cout<<"ofstream open error"<<endl;
		ofs.close();
		return -1;
	}

	while(!ifs.eof()){
		ifs>>stemp;
	

















	string stemp;
	vector<word> myvec;
	myvec.reserve(20);
	vector<word>::iterator it;

	//第一个
	ifs>>str;
	word temp0(1,str);
	myvec.push_back(temp0);

	
	while(!ifs.eof()){
		ifs>>str;
		for(it=myvec.begin();it!=myvec.end();++it){
			if(!strcmp(str,(*it)._wordname)){
				++(*it)._count;
				break;
			}
		}
		if(it==myvec.end()){
			word temp(1,str);
			myvec.push_back(temp);
		}
	}
/*
	for(auto &elem:myvec){
		ofs<<elem<<endl;
	}
*/
	vector<word>::iterator it2=myvec.begin();
	for(;it2!=myvec.end();++it2){
		ofs<<(*it)._wordname<<" "<<(*it)._count<<endl;
	}

	ifs.close();
	ofs.close();
	return 0;
}

		
		
