/*
 * gobo.h
 *
 *  Created on: 2023 Jan 7
 *      Author: Kaloyan KRASTEV
 */
#ifndef INCLUDE_GOBO_H_
#define INCLUDE_GOBO_H_
//#include <stdio.h>
//#include <stdlib.h>
#include <iostream>

using namespace std;

class gobo {
public:
	static int getCount();
	string*get(void);
	gobo(string);
	virtual ~gobo();
	void expo(void);
	void cpp_version(string&);
private:
	static int objectCount;
	string*sBof;
	bool reset(const char*);
/*******************************/
//protected:
};

#endif /* INCLUDE_GOBO_H_ */
