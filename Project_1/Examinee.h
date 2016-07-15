#ifndef _Examinee_H_
#define _Examinee_H_

#define BLANK 10

//考生信息类
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Examinee {
public:
	int age;                          //年龄
	string num, name, sex, exam;      //考号、姓名、性别、报考类别
	Examinee *next;                   //指向下个成员的指针

	Examinee();
	Examinee(int age, string num, string name, 
		string sex, string exam, Examinee *next = NULL);
	Examinee &operator=(const Examinee& rhs);

	void print(ostream &os = cout);  //打印成员
	bool read();                     //读取数据
};

Examinee::Examinee() :
next(NULL) {
}

Examinee::Examinee(int age, string num, string name, string sex, string exam, Examinee *next):
age(age), num(num), name(name), sex(sex), exam(exam), next(next) {
}

bool checkNum(const string& num) {
	for (int i = 0; i < num.length(); ++i) {
		if (!isdigit(num[i]))
			return false;
	}
	return true;
}

bool Examinee::read() {
	cin >> num >> name >> sex >> age >> exam;
	if (!checkNum(num))
		return false;
	return true;
}

void Examinee::print(ostream &os) {
	os << left
		<< setw(BLANK) << this->num
		<< setw(BLANK) << this->name
		<< setw(BLANK) << this->sex
		<< setw(BLANK) << this->age
		<< setw(BLANK) << this->exam
		<< endl;
}

Examinee &Examinee::operator=(const Examinee& rhs) {
	if (this != &rhs) {
		age = rhs.age;
		num = rhs.num;
		name = rhs.name;
		sex = rhs.sex;
		exam = rhs.exam;
		next = NULL;
	}
	return *this;
}


#endif