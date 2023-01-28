/*
 * gobo.cpp
 *
 *  Created on: 2023 Jan 7
 *      Author: Kaloyan KRASTEV
 */

#include "include/gobo.h"
using namespace std;

int gobo::objectCount = 0;

gobo::gobo(string s) {
	const char *c = s.c_str();
	this->reset(c);
	std::cout << "gobo counter: " << ++gobo::objectCount << std::endl;
}

gobo::~gobo() {
	delete this->sBof;
	//this->sBof = 0;
}

int gobo::getCount() {
	return objectCount;
}

bool gobo::reset(const char *c) {
	bool send = false;
	if (this->sBof != 0) {
		delete this->sBof;
		send = true;
	}
	this->sBof = new string(c);
	return send;
}

void gobo::expo(void) {
	cout << "s -> " << sBof << endl << "*s -> " << *sBof << endl;
}

string* gobo::get(void) {
	return this->sBof;
}

void gobo::cpp_version(string &ver) {/* C++ version
 */
	switch (__cplusplus) {
	case 202002L:
		ver = "C++20\n";
		break;
	case 201703L:
		ver = "C++17\n";
		break;
	case 201402L:
		ver = "C++14\n";
		break;
	case 201103L:
		ver = "C++11\n";
		break;
	case 199711L:
		ver = "C++98\n";
		break;
	default:
		ver = "pre-standard C++\n";
	}

	cout << ver;
}
