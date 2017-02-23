#ifndef __MYLOG_H_
#define __MYLOG_H_

#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class Mylog{//单例模式
public:
	static Mylog *getInstance();
	static Mylog *destroy();

	void warn (const string & msg);
	void error (const string & msg);
	void info (const string & msg);
	void debug (const string & msg);

private:
	Mylog();
	~Mylog();
private:
	static Mylog *_pInstance();
};
#endif
