#include <iostream>
#include <string>

using namespace std;

class Person {
public:
	string name;
	Person *firstChild;										 //��һ������
	Person *rightSibling;									 //���ֵܽڵ�
	Person *lastChild;										 //���һ������
public:
	Person();
	Person(const string &s, Person *left = NULL, Person *right = NULL);
	void showChild();                                        //��ʾ���к���
	void insertChild(const string &childName);               //���뺢��
	void rename(const string &newName);						 //������
	void dismiss();											 //��ɢ��ͥ
	void dismissHelp(Person *&p);							 //��������
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
