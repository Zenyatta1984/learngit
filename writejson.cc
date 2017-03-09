 ///
 /// @file    writejson.cc
 /// @date    2017-03-08 19:28:49
 ///


#include <json/json.h>
#include <string>
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::ofstream;

int main(void){
	Json::Value myroot;
	Json::Value arr;

	Json::Value elem;
	elem["title"]="baidu";
	elem["url"]="www.baidu.com";
	elem["abstract"]="searching";
	arr.append(elem);

	elem["title"]="tencent";
	elem["url"]="www.qq.com";
	elem["abstract"]="chating";
	arr.append(elem);

	elem["title"]="alibaba";
	elem["url"]="www.1688.com";
	elem["abstract"]="selling";
	arr.append(elem);

	myroot["BAT"]=arr;

	Json::FastWriter mywriter;
	string msg=mywriter.write(myroot);
	cout<<msg<<endl;
	
	ofstream ofs("BAT.json");
	if(!ofs.good()){
		cout<<"ofstream open error!"<<endl;
		ofs.close();
		return -1;
	}
	ofs<<msg;

	ofs.close();
	return 0;
}


