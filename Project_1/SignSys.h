#include "Examinee.h"

class SignSys {
private:
	int count;                                     //考生人数
	Examinee *head;                                //头指针

private:                                           //辅助函数
	void showTitle(ostream &os = cout)const;       //打印标题栏
	int stringToInt(string number)const;           //string转化成int的函数
	Examinee *getElemPtr(string number)const;      //获取指向考号为number的考生的指针

public:
	SignSys();
	virtual~ SignSys();
	int Length()const;
	bool Delete(string number, Examinee &e);       //删除考号为number的信息
	bool Insert(int pos, Examinee *e);             //在pos位置插入考生信息
	bool Search(string number, Examinee &e)const;  //搜索考号为number的信息
	bool Modify(string number);                    //修改考号为number的信息
	void Print(ostream &os)const;                  //打印所有考生信息
	void Clear();                                  //辅助函数
	void Init();                                   //初始化
	void Start();                                  //主过程
};

SignSys::SignSys() {
	head = new Examinee();
	if (head == NULL) {
		cerr << "内存分配错误!";
		exit(-1);
	}
	count = 0;
}

SignSys::~SignSys() {
	Clear();
	delete head;
}

int SignSys::Length()const {
	return count;
}

void SignSys::Clear() {
	Examinee *p = head->next, *del = NULL;
	while (p) {
		del = p;
		p = p->next;
		delete del;
	}
}

bool SignSys::Insert(int pos, Examinee *e) {
	int i = 1;
	Examinee *temPtr = head;
	while (i < pos&&temPtr) {                        //找到要插入位置的前一个位置
		temPtr = temPtr->next; 
		++i;
	}

	e->next = temPtr->next;                         //插入
	temPtr->next = e;

	++count;
	return true;
}

bool SignSys::Delete(string number, Examinee &e) {
	Examinee *temPtr = head, *nextPtr = head->next;
	while (nextPtr&&nextPtr->num != number) {       //找到待删除位置的前后位置
		temPtr = nextPtr;
		nextPtr = nextPtr->next;
	}

	if (!nextPtr)                                   //待删除元素不存在
		return false;

	temPtr->next = nextPtr->next;                   //删除
	e = *nextPtr;
	delete nextPtr;

	--count;
	return true;
}

bool SignSys::Search(string number, Examinee &e)const {
	Examinee *p = getElemPtr(number);
	if (!p)
		return false;
	e = *p;
	return true;
}

bool SignSys::Modify(string number) {
	Examinee *p = getElemPtr(number);
	if (!p) 
		return false;
    cout << "请输入你要修改的考生信息：";
	return p->read();
}

int SignSys::stringToInt(string number)const {
	int res = 0;
	for (int i = 0; i < number.length(); ++i)
		res = res * 10 + number[i] - '0';
	return res;
}

void SignSys::showTitle(ostream &os)const {
	os << left
		<< setw(BLANK) << "考号"
		<< setw(BLANK) << "姓名"
		<< setw(BLANK) << "性别"
		<< setw(BLANK) << "年龄"
		<< setw(BLANK) << "报考类别"
		<< endl;
}

Examinee *SignSys::getElemPtr(string number)const {
	for (Examinee *p = head->next; p; p = p->next)
	if (p->num == number)
		return p;
	return NULL;
}

void SignSys::Print(ostream &os = cout)const {
	os << endl;
	showTitle(os);
	for (Examinee *p = head->next; p; p = p->next)
		p->print(os);
}

void SignSys::Init() {
	int n, pos;
	string num;
	Examinee *p = NULL;
	cout << "首先请建立考生信息系统！" << endl;
	cout << "请输入考生人数：";
	while (getline(cin, num), !checkNum(num)) {
		cout << "考生人数输入非法！请重新输入" << endl;
	}
	n = stringToInt(num);
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
	for (pos = 1; pos <= n; ++pos) {
		p = new Examinee();
		while (!p->read()) {
			cout << "考生信息输入错误！请重新输入" << endl;
		}
		Insert(pos, p);
	}
	Print();
}

void SignSys::Start() {
	Examinee elem;
	Examinee *p = NULL;
	string num;
	int n, pos;

	do {
		cout << "\n请选择您要进行的操作(1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作)" << endl;
		p = NULL;
		//cout << "请选择您要进行的操作：";
		cin >> num;
		if (!checkNum(num)) {
			cout << "输入非法！\n" << endl;
			n = -1;
			continue;
		}
		n = stringToInt(num);

		switch (n) {
			//退出
		case 0:
			cout << "谢谢使用！再见" << endl;
			break;

			//插入
		case 1:
			cout << "请输入你要插入的考生的位置：";
			cin >> num;
			if (!checkNum(num)) {
				cout << "考生位置输入非法！\n" << endl;
				break;
			}
			pos = stringToInt(num);
			if (pos<1 || pos>count + 1) {
				cout << "插入位置错误!\n" << endl;
				break;
			}
			cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;
			p = new Examinee();
			p->read();
			Insert(pos, p);

			Print();
			break;

			//删除
		case 2:
			cout << "请输入要删除的考生的考号：";
			cin >> num;
			if (!checkNum(num)) {
				cout << "考生考号输入有误！\n" << endl;
				break;
			}
			if (Delete(num, elem)) {
				cout << "你删除的考生信息是：";
				elem.print();
			}
			else {
				cout << "考生不存在！\n" << endl;
				break;
			}
			Print();
			break;

			//查找
		case 3:
			cout << "请输入要查找的考生的考号：";
			cin >> num;
			if (!checkNum(num)) {
				cout << "考生考号输入有误！\n" << endl;
				break;
			}
			if (Search(num, elem)){
				showTitle();
				elem.print();
			} else {
				cout << "考生不存在！\n" << endl;
			}
			break;
			
			//修改
		case 4:
			cout << "请输入要修改的考生的考号：";
			cin >> num;
			if (!checkNum(num)) {
				cout << "考生考号输入有误！\n" << endl;
				break;
			}
			if (!Modify(num)) {
				cout << "考生不存在或者输入信息有误！\n" << endl;
				break;
			}
			Print();
			break;

			//统计
		case 5:
			cout << "共有考生" << Length() << "人!" << endl;
			Print();
			break;

			//输入非法
		default:
			cout << "输入无效！请重新输入\n" << endl;
			break;
		}
	} while (n);
}