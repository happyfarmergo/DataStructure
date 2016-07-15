#include "Person.h"
#include <iomanip>

class Family {
private:
	Person *root;
private:
	void showTitle()const;                                    //��ӡ����
	Person *search(const string &name, Person *r)const;		  //�����ڵ�
public:
	Family();
	~Family();
	void Clear(Person *&r);									  //������r���ȵļ���
	bool Build(const string &name);							  //����nameΪ���ȵļ���
	bool AddChild(const string &name);						  //Ϊname��Ӻ���
	bool Dismiss(const string &name);						  //��ɢname�ĺ��
	bool Rename(const string &name);						  //Ϊname������
	void Init();											  //��ʼ��
	void Run();												  //������
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
	if (!r)															//rΪNULL
		return NULL;
	if (r->name == name)											//�ҵ��ڵ�
		return r;
	Person *p;
	if ((p = search(name, r->firstChild)) != NULL)return p;			//����������
	if ((p = search(name, r->rightSibling)) != NULL)return p;		//�����ֵ�����
	return NULL;
}

void Family::showTitle()const {
	cout << "**             ���׹���ϵͳ             **\n"
		<< "==========================================\n"
		<< "**            ��ѡ��Ҫִ�еĲ���        **\n"
		<< "**            A --- ���Ƽ�ͥ            **\n"
		<< "**            B --- ��Ӽ�ͥ��Ա        **\n"
		<< "**            C --- ��ɢ�ֲ���ͥ        **\n"
		<< "**            D --- ���ļ�ͥ��Ա����    **\n"
		<< "**            E --- �˳�����            **\n"
		<< "=========================================="
		<< endl;
}
void Family::Init() {
	showTitle();
	string name;
	cout << "���Ƚ���һ�����ף�\n���������ȵ�����: ";
	cin >> name;
	root = new Person(name);
	cout << "�˼��׵�������: " << name << endl;
}

bool Family::Build(const string &name) {
	Person *cur = search(name, root);
	if (!cur)
		return false;
	int childNum;
	string childName;
	cout << "������" << name << "�Ķ�Ů����: ";
	cin >> childNum;
	cout << "����������" << name << "�Ķ�Ů������: ";
	while (childNum--) {
		cin >> childName;
		cur->insertChild(childName);
	}
	cout << name << "�ĵ�һ��������: ";
	cur->showChild();
	return true;
}

bool Family::AddChild(const string &name) {
	Person *cur = search(name, root);
	if (!cur)
		return false;
	string childName;
	cout << "������" << name << "Ҫ��ӵĶ�Ů������: ";
	cin >> childName;
	cur->insertChild(childName);
	cout << name << "�ĵ�һ��������: ";
	cur->showChild();
	return true;
}

bool Family::Dismiss(const string &name) {
	Person *cur = search(name, root);
	if (!cur)
		return false;
	cout << "Ҫ��ɢ��ͥ������: " << name << endl;
	cout << name << "�ĵ�һ��������: ";
	cur->showChild();
	cur->dismiss();
	return true;
}

bool Family::Rename(const string &name) {
	Person *cur = search(name, root);
	if (!cur)
		return false;
	string newName;
	cout << "��������ĺ������: ";
	cin >> newName;
	cur->rename(newName);
	cout << name << "�Ѹ���Ϊ" << newName << endl;
	return true;
}

void Family::Run() {
	string parName;
	char choose;
	do {
		cout << "\n��ѡ��Ҫִ�еĲ���: ";
		cin >> choose;
		switch (choose) {
		case 'A':
			cout << "������Ҫ������ͥ���˵�����: ";
			cin >> parName;
			if (!Build(parName)) {
				cout << parName << "�����ڣ�" << endl;
				break;
			}
			break;

		case 'B':
			cout << "������Ҫ��Ӷ�Ů���˵�����: ";
			cin >> parName;
			if (!AddChild(parName)) {
				cout << parName << "�����ڣ�" << endl;
				break;
			}
			break;

		case 'C':
			cout << "������Ҫ��ɢ��ͥ���˵�����: ";
			cin >> parName;
			if (!Dismiss(parName)) {
				cout << parName << "�����ڣ�" << endl;
				break;
			}
			break;

		case 'D':
			cout << "������Ҫ�����������˵�Ŀǰ����: ";
			cin >> parName;
			if (!Rename(parName)) {
				cout << parName << "�����ڣ�" << endl;
				break;
			}
			break;

		case 'E':
			break;

		default:
			cout << "������Ч��" << endl;
			break;
		}
	} while (choose != 'E');
}