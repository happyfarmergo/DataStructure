#include <iostream>
#include <cstdio>

using namespace std;

class Queen {
private:
	int *q;											//�洢�ʺ������
	bool **visit;									//�����Ӧ�С��Խ��ߵ�λ���Ƿ񱻷��ʹ�
	int queenNum;									//�ʺ����
	int solve;										//�ⷨ����
public:
	void Init(int n);								//��ʼ������
	Queen();
	~Queen();
	void search(int cur);							//�����㷨
	void Start();                                   //������
};

Queen::Queen() {
	q = NULL;
	queenNum = 0;
	solve = 0;
}

Queen::~Queen() {
	for (int i = 0; i < 3; ++i)
		delete[]visit[i];
	delete[]visit;
	delete[]q;
}

void Queen::Init(int n) {
	q = new int[n];
	visit = new bool *[3];
	for (int i = 0; i < 3; ++i)
		visit[i] = new bool[2 * n];
	for (int i = 0; i < 3; ++i)
	for (int j = 0; j < 2 * n; ++j)
		visit[i][j] = false;
	queenNum = n;
}

void Queen::Start() {
	int n;
	cout << "����N*N�����̣�����N���ʺ�Ҫ�����лʺ���ͬһ�С��С���ͬһб���ϣ�\n" << endl;
	cout << "������ʺ�ĸ�����";
	cin >> n;
	cout << "�ʺ�ڷ���\n" << endl;
	Init(n);
	search(0);
	cout << "����" << solve << "�ֽⷨ��" << endl;
}

void Queen::search(int cur) {
	if (cur == queenNum) {
		for (int i = 0; i < queenNum; ++i) {
			for (int j = 0; j < queenNum; ++j) {
				printf("%s", j == q[i] ? "X " : "0 ");
			}
			printf("\n");
		}
		printf("\n");
		++solve;
	} else {
		for (int i = 0; i < queenNum; ++i) {
			if (!visit[0][i] && !visit[1][cur + i] && !visit[2][cur - i + queenNum]) {
				q[cur] = i;
				visit[0][i] = visit[1][cur + i] = visit[2][cur - i + queenNum] = true;
				search(cur + 1);
				visit[0][i] = visit[1][cur + i] = visit[2][cur - i + queenNum] = false;
			}
		}
	}
}