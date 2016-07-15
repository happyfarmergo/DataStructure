#include <iostream>
#include <cstdio>

using namespace std;

class Queen {
private:
	int *q;											//存储皇后的数组
	bool **visit;									//标记相应列、对角线的位置是否被访问过
	int queenNum;									//皇后个数
	int solve;										//解法个数
public:
	void Init(int n);								//初始化数据
	Queen();
	~Queen();
	void search(int cur);							//回溯算法
	void Start();                                   //主程序
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
	cout << "现有N*N的棋盘，放入N个皇后，要求所有皇后不在同一行、列、和同一斜线上！\n" << endl;
	cout << "请输入皇后的个数：";
	cin >> n;
	cout << "皇后摆法：\n" << endl;
	Init(n);
	search(0);
	cout << "共有" << solve << "种解法！" << endl;
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