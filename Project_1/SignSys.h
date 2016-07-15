#include "Examinee.h"

class SignSys {
private:
	int count;                                     //��������
	Examinee *head;                                //ͷָ��

private:                                           //��������
	void showTitle(ostream &os = cout)const;       //��ӡ������
	int stringToInt(string number)const;           //stringת����int�ĺ���
	Examinee *getElemPtr(string number)const;      //��ȡָ�򿼺�Ϊnumber�Ŀ�����ָ��

public:
	SignSys();
	virtual~ SignSys();
	int Length()const;
	bool Delete(string number, Examinee &e);       //ɾ������Ϊnumber����Ϣ
	bool Insert(int pos, Examinee *e);             //��posλ�ò��뿼����Ϣ
	bool Search(string number, Examinee &e)const;  //��������Ϊnumber����Ϣ
	bool Modify(string number);                    //�޸Ŀ���Ϊnumber����Ϣ
	void Print(ostream &os)const;                  //��ӡ���п�����Ϣ
	void Clear();                                  //��������
	void Init();                                   //��ʼ��
	void Start();                                  //������
};

SignSys::SignSys() {
	head = new Examinee();
	if (head == NULL) {
		cerr << "�ڴ�������!";
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
	while (i < pos&&temPtr) {                        //�ҵ�Ҫ����λ�õ�ǰһ��λ��
		temPtr = temPtr->next; 
		++i;
	}

	e->next = temPtr->next;                         //����
	temPtr->next = e;

	++count;
	return true;
}

bool SignSys::Delete(string number, Examinee &e) {
	Examinee *temPtr = head, *nextPtr = head->next;
	while (nextPtr&&nextPtr->num != number) {       //�ҵ���ɾ��λ�õ�ǰ��λ��
		temPtr = nextPtr;
		nextPtr = nextPtr->next;
	}

	if (!nextPtr)                                   //��ɾ��Ԫ�ز�����
		return false;

	temPtr->next = nextPtr->next;                   //ɾ��
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
    cout << "��������Ҫ�޸ĵĿ�����Ϣ��";
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
		<< setw(BLANK) << "����"
		<< setw(BLANK) << "����"
		<< setw(BLANK) << "�Ա�"
		<< setw(BLANK) << "����"
		<< setw(BLANK) << "�������"
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
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	cout << "�����뿼��������";
	while (getline(cin, num), !checkNum(num)) {
		cout << "������������Ƿ�������������" << endl;
	}
	n = stringToInt(num);
	cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
	for (pos = 1; pos <= n; ++pos) {
		p = new Examinee();
		while (!p->read()) {
			cout << "������Ϣ�����������������" << endl;
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
		cout << "\n��ѡ����Ҫ���еĲ���(1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ������)" << endl;
		p = NULL;
		//cout << "��ѡ����Ҫ���еĲ�����";
		cin >> num;
		if (!checkNum(num)) {
			cout << "����Ƿ���\n" << endl;
			n = -1;
			continue;
		}
		n = stringToInt(num);

		switch (n) {
			//�˳�
		case 0:
			cout << "ллʹ�ã��ټ�" << endl;
			break;

			//����
		case 1:
			cout << "��������Ҫ����Ŀ�����λ�ã�";
			cin >> num;
			if (!checkNum(num)) {
				cout << "����λ������Ƿ���\n" << endl;
				break;
			}
			pos = stringToInt(num);
			if (pos<1 || pos>count + 1) {
				cout << "����λ�ô���!\n" << endl;
				break;
			}
			cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������" << endl;
			p = new Examinee();
			p->read();
			Insert(pos, p);

			Print();
			break;

			//ɾ��
		case 2:
			cout << "������Ҫɾ���Ŀ����Ŀ��ţ�";
			cin >> num;
			if (!checkNum(num)) {
				cout << "����������������\n" << endl;
				break;
			}
			if (Delete(num, elem)) {
				cout << "��ɾ���Ŀ�����Ϣ�ǣ�";
				elem.print();
			}
			else {
				cout << "���������ڣ�\n" << endl;
				break;
			}
			Print();
			break;

			//����
		case 3:
			cout << "������Ҫ���ҵĿ����Ŀ��ţ�";
			cin >> num;
			if (!checkNum(num)) {
				cout << "����������������\n" << endl;
				break;
			}
			if (Search(num, elem)){
				showTitle();
				elem.print();
			} else {
				cout << "���������ڣ�\n" << endl;
			}
			break;
			
			//�޸�
		case 4:
			cout << "������Ҫ�޸ĵĿ����Ŀ��ţ�";
			cin >> num;
			if (!checkNum(num)) {
				cout << "����������������\n" << endl;
				break;
			}
			if (!Modify(num)) {
				cout << "���������ڻ���������Ϣ����\n" << endl;
				break;
			}
			Print();
			break;

			//ͳ��
		case 5:
			cout << "���п���" << Length() << "��!" << endl;
			Print();
			break;

			//����Ƿ�
		default:
			cout << "������Ч������������\n" << endl;
			break;
		}
	} while (n);
}