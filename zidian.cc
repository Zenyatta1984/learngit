#include<stdio.h>
#include<iostream>
#include<vector>
#include<fstream>
#include<string.h>
#include<string>


using namespace std;
class word{
	public:	word(string name1):name(name1)
	{   count=1;
		name=name1;
	}
	public:
		string name;
		int count;

};
int main (int argc,char**argv)
{  
	if(argc!=3)
	{
		printf("error args\n");
		return -1;
	}
	ifstream ifs (argv[1]);
	if(!ifs.good())
	{
		cout<<"打开初始文件失败\n"<<endl;
		return -1;
	}
	string ss;
	vector<word> xia;
	vector<word>::iterator it;

	while(!ifs.eof())
	{
		ifs>>ss;
			for(it=xia.begin();it!=xia.end();++it)
		{
			if(ss==it->name)
			{
				(it->count)++;
				break;
			}
		}
            if(it==xia.end())
			{ word s1(ss);
			  xia.push_back(s1);
		
			}
		}
	

      


	ofstream ofs (argv[2]);
	if(!ofs.good())
	{
		cout<<"打开输出文件失败\n"<<endl;
		return -1;
	}
	
	  for(it=xia.begin();it!=xia.end();it++)
	  {
		  ofs<<it->name<<it->count<<endl;
	  }
}

		  



