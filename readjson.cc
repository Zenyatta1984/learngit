 ///
 /// @file    testjson.cc
 /// @date    2017-03-08 10:01:25
 ///
#pragma comment(lib,"json_mtd.lib")

#include <fstream>
#include <cassert>
#include "json/json.h"
#include <string>

using std::string;
using std::ifstream;
using std::endl;
using std::cout;


int main(){
	ifstream ifs("testjson.json");
	//ifs.open("testjson.json")
	if(!ifs.good()){
		cout<<"ifstream open error!"<<endl;
		return -1;
	}

	//assert(ifs.is_open());---------???

	Json::Reader reader;
	Json::Value myroot;
	if(!reader.parse(ifs,myroot,false)){
		cout<<"json parse error!"<<endl;
		ifs.close();
		return -1;
	}

	//std::string name =root["name"].asString();
	//int age=root["age"].asInt();

	//std::cout<<name<<std::endl;
	//std::cout<<age<<std::endl;
		
	string title;
	string url;
	string abstract;
	Json::Value arr=myroot["BAT"];

	for(size_t idx=0;idx!=arr.size();++idx){

		title=arr[idx]["title"].asString();
		url=arr[idx]["url"].asString();
		abstract=arr[idx]["abstract"].asString();
		cout<<"title:"<<title<<endl;
		cout<<"url:"<<url<<endl;
		cout<<"abstract:"<<abstract<<endl;
		cout <<endl;
	}

	return 0;
}
