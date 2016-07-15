#include <iostream>
#include <string>

using namespace std;

class Person {
public:
	string name;
	Person *firstChild;										 //第一个孩子
	Person *rightSibling;									 //右兄弟节点
	Person *lastChild;										 //最后一个孩子
public:
	Person();
	Person(const string &s, Person *left = NULL, Person *right = NULL);
	void showChild();                                        //显示所有孩子
	void insertChild(const string &childName);               //插入孩子
	void rename(const string &newName);						 //重命名
	void dismiss();											 //解散家庭
	void dismissHelp(Person *&p);							 //辅助函数
};

Person::Person() :
firstChild(NULL), rightSibling(NULL), lastChild(NULL) {
}

Person::Person(const string &s, Person *left, Person *right) :
name(s), firstChild(left), rightSibling(right), lastChild(NULL) {
}

void Person::showChild() {
	for (Person *child = firstChild; child; child = child->rightSibling) {
		cout << child->name << ' ';
	}
	cout << endl;
}

void Person::insertChild(const string &childName) {
	if (lastChild == NULL) {
		firstChild = new Person(childName);
		lastChild = firstChild;
		return;
	}
	lastChild->rightSibling = new Person(childName);
	lastChild = lastChild->rightSibling;
}

void Person::rename(const string &newName) {
	name = newName;
}

void Person::dismiss() {
	dismissHelp(firstChild);
	lastChild = NULL;
}

void Person::dismissHelp(Person *&p) {
	if (p) {
		dismissHelp(p->firstChild);
		dismissHelp(p->rightSibling);
		delete p;
		p = NULL;
	}
}
