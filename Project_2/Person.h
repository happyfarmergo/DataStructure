#ifndef _Person_H_
#define _Person_H_

#include <iostream>
using namespace std;
class Person {
public:
	int num;
	Person *next;
	Person(int pos, Person *link = NULL) :
		num(pos), next(link) {}
};

#endif