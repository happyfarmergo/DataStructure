#include "Person.h"
#include <iomanip>

class JPGame {
private:
	Person *head, *tail;
	int n;								//总人数
	int s;								//开始位置
	int m;								//死亡数字
	int k;								//剩余人数
public:
	JPGame();
	~JPGame();
	void Init();					    //初始化
	Person *Locate(int i)const;         //定位人
	void Print();                       //打印最终人数
	void Start();                       //主程序
};

void JPGame::Init() {
	cout << "现在N人围成一圈，从第S个人开始依次报数，报M的人出局，再由下一人开始报数，如此循环，直至剩下K个人为止\n" << endl;
	cout << "请输入生死游戏的总人数N：";
	cin >> n;
	cout << "请输入游戏开始的位置S：";
	cin >> s;
	cout << "请输入死亡数字M：";
	cin >> m;
	cout << "请输入剩余的生者人数K：";
	cin >> k;
	cout << endl;

	if (n <= 0 || s > n || k > n || m <= 0) {
		cout << "输入数据不对！" << endl;
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
	Person *cur = Locate(s), *pre = Locate(s == 1 ? n : s - 1);   //pre指向cur的前一个位置   
	for (int i = 1; i <= n - k; ++i) {
		for (int j = 1; j < m; ++j) {                             //找到第m个人
			pre = cur;
			cur = cur->next;
		}
		cout << "第" << i << "个死者的位置是:\t\t" 
			<< cur->num << endl;
		pre->next = cur->next;                                    //删除链表节点

		if (cur == head)                                          //删除节点处于头结点
			head = cur->next;
		delete cur;                                               //释放内存

		cur = pre->next;
	}
	cout << endl;
	cout << "最后剩下:" << k << "人" << endl;
	cout << "剩余的死者位置为:" << endl;
	Print();
}