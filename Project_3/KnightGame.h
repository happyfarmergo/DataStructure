#include <iostream>
#include <Windows.h>

using namespace std;

typedef struct {
	int x;
	int y;
}Point;

class KnightGame {
private:
	HANDLE hout;							//控制台句柄
	CONSOLE_SCREEN_BUFFER_INFO binfo;		//控制台缓冲区信息
	int columns;							//迷宫的列数
	int rows;								//迷宫的行数
	Point start;							//迷宫起点
	Point end;								//迷宫终点
	char **maze;							//迷宫矩阵
	static int dir[4][2];					//移动方向
public:
	KnightGame();
	~KnightGame();
	bool index(int x, int y);               //判断(x,y)是否出界
	bool DFS(int x, int y);					//判断是否有通路
	void ShowPath();						//显示迷宫
	void PrintPath();						//显示路径
	void Init();							//初始化
	void Run();								//主程序
};

//方向数组：上右下左
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
	hout = GetStdHandle(STD_OUTPUT_HANDLE);    //获取控制台句柄
	GetConsoleScreenBufferInfo(hout, &binfo);  //获取屏幕缓冲区结构体
	SetConsoleTitleA("KnightGame");            //设置控制台标题

	cout << "请输入迷宫的行数和列数: ";
	cin >> rows >> columns;

	maze = new char *[rows];                   
	for (int i = 0; i < rows; ++i)
		maze[i] = new char[columns];
	
	cout << "请输入迷宫地图:('#'代表墙,'0'代表路,中间不要有空格)" << endl;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j)
			cin >> maze[i][j];
	}
	cout << "请输入迷宫的起点和终点坐标: ";
	cin >> start.x >> start.y >> end.x >> end.y;
}

inline bool KnightGame::index(int x, int y) {
	return x >= 0 && x < rows&&y >= 0 && y < columns;
}

bool KnightGame::DFS(int x, int y) {              
	if (x == end.x&&y == end.y) {                      //当前节点为终点，搜索完毕  
		maze[x][y] = 'x';                              //标记终点为走过的节点
		return true;
	}
	int nextx, nexty;
	for (int i = 0; i < 4; ++i) {
		nextx = x + dir[i][0];                         //下一个节点
		nexty = y + dir[i][1];
		if (index(nextx, nexty) &&
			maze[nextx][nexty] == '0') {               //试探下一个节点能否走
			maze[nextx][nexty] = 'x';                  //标记下一个节点为走过
			if (DFS(nextx, nexty))return true;
			maze[nextx][nexty] = '0';                  //重置下一个节点为未走过
		}
	}
	return false;
}

void KnightGame::ShowPath() {
	int i, j;
	for (i = 0; i < columns; ++i)
		cout << '\t' << i << "列";
	cout << endl;
	for (i = 0; i < rows; ++i) {
		cout << i << "行" << '\t';
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
	cout << "\n迷宫路径:\n" << endl;
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
	maze[start.x][start.y] = 'x';               //标记起点为已走过
	if (DFS(start.x, start.y)) {
		ShowPath();
		PrintPath();
	}
	else 
		cout << "没有通路！" << endl;
	CloseHandle(hout);
}