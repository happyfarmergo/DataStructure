#include "Person.h"
#include <iomanip>

class JPGame {
private:
	Person *head, *tail;
	int n;								//������
	int s;								//��ʼλ��
	int m;								//��������
	int k;								//ʣ������
public:
	JPGame();
	~JPGame();
	void Init();					    //��ʼ��
	Person *Locate(int i)const;         //��λ��
	void Print();                       //��ӡ��������
	void Start();                       //������
};

void JPGame::Init() {
	cout << "����N��Χ��һȦ���ӵ�S���˿�ʼ���α�������M���˳��֣�������һ�˿�ʼ���������ѭ����ֱ��ʣ��K����Ϊֹ\n" << endl;
	cout << "������������Ϸ��������N��";
	cin >> n;
	cout << "��������Ϸ��ʼ��λ��S��";
	cin >> s;
	cout << "��������������M��";
	cin >> m;
	cout << "������ʣ�����������K��";
	cin >> k;
	cout << endl;

	if (n <= 0 || s > n || k > n || m <= 0) {
		cout << "�������ݲ��ԣ�" << endl;
		system("pause");
		exit(-1);
	}

	head = tail = new Person(1);
	for (int i = 2; i <= n; ++i) {
		Person *person = new Person(i);
		tail->next = person;
		tail = person;
	}
	tail->next = head;
}

JPGame::JPGame() {
	head = tail = NULL;
	n = s = k = m = 0;
}

JPGame::~JPGame() {
	Person *p = head, *del = NULL;
	int t = 0;
	while (t < k) {
		del = p;
		p = p->next;
		delete del;
		++t;
	}
}

Person *JPGame::Locate(int i)const {
	Person *p = head;
	for (int j = 1; j < i; ++j) {
		p = p->next;
	}
	return p;
}

void JPGame::Print() {
	Person *p = head;
	int i = 0;
	while (i < k) {
		cout << p->num << ' ';
		++i;
		if (i % 8 == 0)
			cout << endl;
		p = p->next;
	}
	cout << endl;
}

void JPGame::Start() {
	Person *cur = Locate(s), *pre = Locate(s == 1 ? n : s - 1);   //preָ��cur��ǰһ��λ��   
	for (int i = 1; i <= n - k; ++i) {
		for (int j = 1; j < m; ++j) {                             //�ҵ���m����
			pre = cur;
			cur = cur->next;
		}
		cout << "��" << i << "�����ߵ�λ����:\t\t" 
			<< cur->num << endl;
		pre->next = cur->next;                                    //ɾ������ڵ�

		if (cur == head)                                          //ɾ���ڵ㴦��ͷ���
			head = cur->next;
		delete cur;                                               //�ͷ��ڴ�

		cur = pre->next;
	}
	cout << endl;
	cout << "���ʣ��:" << k << "��" << endl;
	cout << "ʣ�������λ��Ϊ:" << endl;
	Print();
}