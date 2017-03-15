 ///
 /// @file    nocopyable.h
 /// @date    2017-03-14 20:24:18
 ///
 

#ifndef __NOCOPYABLE_H__
#define __NOCOPYABLE_H__

namespace hello
{
	class nocopyable{
	protected:
		nocopyable(){}
		~nocopyable(){}
	
	private:
		nocopyable(const nocopyable &);
		nocopyable & operator=(const nocopyable &);
	};
}//end of the namespace hello

#endif


