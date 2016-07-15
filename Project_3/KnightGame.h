#include <iostream>
#include <Windows.h>

using namespace std;

typedef struct {
	int x;
	int y;
}Point;

class KnightGame {
private:
	HANDLE hout;							//����̨���
	CONSOLE_SCREEN_BUFFER_INFO binfo;		//����̨��������Ϣ
	int columns;							//�Թ�������
	int rows;								//�Թ�������
	Point start;							//�Թ����
	Point end;								//�Թ��յ�
	char **maze;							//�Թ�����
	static int dir[4][2];					//�ƶ�����
public:
	KnightGame();
	~KnightGame();
	bool index(int x, int y);               //�ж�(x,y)�Ƿ����
	bool DFS(int x, int y);					//�ж��Ƿ���ͨ·
	void ShowPath();						//��ʾ�Թ�
	void PrintPath();						//��ʾ·��
	void Init();							//��ʼ��
	void Run();								//������
};

//�������飺��������
int KnightGame::dir[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

KnightGame::KnightGame():
maze(NULL){
	
}

KnightGame::~KnightGame() {
	for (int i = 0; i < rows; ++i)
		delete[]maze[i];
	delete[]maze;
}

void KnightGame::Init() {
	hout = GetStdHandle(STD_OUTPUT_HANDLE);    //��ȡ����̨���
	GetConsoleScreenBufferInfo(hout, &binfo);  //��ȡ��Ļ�������ṹ��
	SetConsoleTitleA("KnightGame");            //���ÿ���̨����

	cout << "�������Թ�������������: ";
	cin >> rows >> columns;

	maze = new char *[rows];                   
	for (int i = 0; i < rows; ++i)
		maze[i] = new char[columns];
	
	cout << "�������Թ���ͼ:('#'����ǽ,'0'����·,�м䲻Ҫ�пո�)" << endl;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j)
			cin >> maze[i][j];
	}
	cout << "�������Թ��������յ�����: ";
	cin >> start.x >> start.y >> end.x >> end.y;
}

inline bool KnightGame::index(int x, int y) {
	return x >= 0 && x < rows&&y >= 0 && y < columns;
}

bool KnightGame::DFS(int x, int y) {              
	if (x == end.x&&y == end.y) {                      //��ǰ�ڵ�Ϊ�յ㣬�������  
		maze[x][y] = 'x';                              //����յ�Ϊ�߹��Ľڵ�
		return true;
	}
	int nextx, nexty;
	for (int i = 0; i < 4; ++i) {
		nextx = x + dir[i][0];                         //��һ���ڵ�
		nexty = y + dir[i][1];
		if (index(nextx, nexty) &&
			maze[nextx][nexty] == '0') {               //��̽��һ���ڵ��ܷ���
			maze[nextx][nexty] = 'x';                  //�����һ���ڵ�Ϊ�߹�
			if (DFS(nextx, nexty))return true;
			maze[nextx][nexty] = '0';                  //������һ���ڵ�Ϊδ�߹�
		}
	}
	return false;
}

void KnightGame::ShowPath() {
	int i, j;
	for (i = 0; i < columns; ++i)
		cout << '\t' << i << "��";
	cout << endl;
	for (i = 0; i < rows; ++i) {
		cout << i << "��" << '\t';
		for (j = 0; j < columns; ++j) {
			if (maze[i][j] == 'x')
				SetConsoleTextAttribute(hout, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << maze[i][j] << '\t';
			SetConsoleTextAttribute(hout, binfo.wAttributes);
		}
		cout << '\n' << endl;
	}
}

void KnightGame::PrintPath() {
	cout << "\n�Թ�·��:\n" << endl;
	int i, j, k;
	for (i = start.x, j = start.y; i != end.x || j != end.y;) {
		cout << '(' << i << ',' << j << ')' << " ---> ";
		maze[i][j] = '0';
		for (k = 0; k < 4; ++k)
		if (maze[i + dir[k][0]][j + dir[k][1]] == 'x') {
			i += dir[k][0];
			j += dir[k][1];
			break;
		}
	}
	cout << '(' << end.x << ',' << end.y << ')' << endl;
}

void KnightGame::Run() {
	maze[start.x][start.y] = 'x';               //������Ϊ���߹�
	if (DFS(start.x, start.y)) {
		ShowPath();
		PrintPath();
	}
	else 
		cout << "û��ͨ·��" << endl;
	CloseHandle(hout);
}