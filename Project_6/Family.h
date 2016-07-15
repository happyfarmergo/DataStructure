#include "Person.h"
#include <iomanip>

class Family {
private:
	Person *root;
private:
	void showTitle()const;                                    //打印标题
	Person *search(const string &name, Person *r)const;		  //搜索节点
public:
	Family();
	~Family();
	void Clear(Person *&r);									  //销毁以r祖先的家谱
	bool Build(const string &name);							  //建立name为祖先的家谱
	bool AddChild(const string &name);						  //为name添加孩子
	bool Dismiss(const string &name);						  //解散name的后代
	bool Rename(const string &name);						  //为name重命名
	void Init();											  //初始化
	void Run();												  //主程序
};

Family::Family() :
root(NULL) {
}

Family::~Family() {
	Clear(root);
}

void Family::Clear(Person *&r) {
	if (r) {
		Clear(r->firstChild);
		Clear(r->rightSibling);
		delete r;
		r = NULL;
	}
}

Person *Family::search(const string &name, Person *r)const {
	if (!r)															//r为NULL
		return NULL;
	if (r->name == name)											//找到节点
		return r;
	Person *p;
	if ((p = search(name, r->firstChild)) != NULL)return p;			//在左孩子树中
	if ((p = search(name, r->rightSibling)) != NULL)return p;		//在右兄弟树中
	return NULL;
}

void Family::showTitle()const {
	cout << "**             家谱管理系统             **\n"
		<< "==========================================\n"
		<< "**            请选择要执行的操作        **\n"
		<< "**            A --- 完善家庭            **\n"
		<< "**            B --- 添加家庭成员        **\n"
		<< "**            C --- 解散局部家庭        **\n"
		<< "**            D --- 更改家庭成员姓名    **\n"
		<< "**            E --- 退出程序            **\n"
		<< "=========================================="
		<< endl;
}
void Family::Init() {
	showTitle();
	string name;
	cout << "首先建立一个家谱！\n请输入祖先的姓名: ";
	cin >> name;
	root = new Person(name);
	cout << "此家谱的祖先是: " << name << endl;
}

bool Family::Build(const string &name) {
	Person *cur = search(name, root);
	if (!cur)
		return false;
	int childNum;
	string childName;
	cout << "请输入" << name << "的儿女个数: ";
	cin >> childNum;
	cout << "请依次输入" << name << "的儿女的姓名: ";
	while (childNum--) {
		cin >> childName;
		cur->insertChild(childName);
	}
	cout << name << "的第一代子孙是: ";
	cur->showChild();
	return true;
}

bool Family::AddChild(const string &name) {
	Person *cur = search(name, root);
	if (!cur)
		return false;
	string childName;
	cout << "请输入" << name << "要添加的儿女的姓名: ";
	cin >> childName;
	cur->insertChild(childName);
	cout << name << "的第一代子孙是: ";
	cur->showChild();
	return true;
}

bool Family::Dismiss(const string &name) {
	Person *cur = search(name, root);
	if (!cur)
		return false;
	cout << "要解散家庭的人是: " << name << endl;
	cout << name << "的第一代子孙是: ";
	cur->showChild();
	cur->dismiss();
	return true;
}

bool Family::Rename(const string &name) {
	Person *cur = search(name, root);
	if (!cur)
		return false;
	string newName;
	cout << "请输入更改后的姓名: ";
	cin >> newName;
	cur->rename(newName);
	cout << name << "已更名为" << newName << endl;
	return true;
}

void Family::Run() {
	string parName;
	char choose;
	do {
		cout << "\n请选择要执行的操作: ";
		cin >> choose;
		switch (choose) {
		case 'A':
			cout << "请输入要建立家庭的人的姓名: ";
			cin >> parName;
			if (!Build(parName)) {
				cout << parName << "不存在！" << endl;
				break;
			}
			break;

		case 'B':
			cout << "请输入要添加儿女的人的姓名: ";
			cin >> parName;
			if (!AddChild(parName)) {
				cout << parName << "不存在！" << endl;
				break;
			}
			break;

		case 'C':
			cout << "请输入要解散家庭的人的姓名: ";
			cin >> parName;
			if (!Dismiss(parName)) {
				cout << parName << "不存在！" << endl;
				break;
			}
			break;

		case 'D':
			cout << "请输入要更改姓名的人的目前姓名: ";
			cin >> parName;
			if (!Rename(parName)) {
				cout << parName << "不存在！" << endl;
				break;
			}
			break;

		case 'E':
			break;

		default:
			cout << "输入无效！" << endl;
			break;
		}
	} while (choose != 'E');
}