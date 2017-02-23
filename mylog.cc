#include "Mylog.h"//本cc的头文件要写在第一行 

Mylog * Mylog::getInstance(){
	if(_pInstance==NULL){
		_pInstance=new Mylog;
	}
	return _pInstance;
}

Mylog::Mylog(){

