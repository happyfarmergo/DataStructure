#include <iostream>
#include <string>
#include <map>
#include <vector>

#define INF 0x7fffffff

using namespace std;

class ElecNetSys {
private:
	int **Graph;                               //邻接矩阵
	vector<pair<int, int>>Path;                //最小生成树路径
	vector<string>Vertex;					   //顶点名称
	map<string, int>Map;					   //名称:下标
	int verNum;								   //顶点个数
	int mincost;							   //建立电网的最小代价
private:
	void showTitle()const;					   //打印标题
	bool buildPrimTree(int src, int *cost, int *near);//建树的辅助函数
public:
	ElecNetSys();
	~ElecNetSys();
	void Init();                               //初始化
	void AddEdge();							   //添加边
	void ShowTree();						   //显示最小生成树
	bool Build();							   //建立最小生成树
	void Clear();							   //删除最小生成树
	void Alloc();                              //分配图空间
	void Run();								   //主程序
};

ElecNetSys::ElecNetSys() :
Graph(NULL), verNum(0), mincost(0) {

}

ElecNetSys::~ElecNetSys() {
	Clear();
}

void ElecNetSys::Alloc() {
	Graph = new int *[verNum];
	for (int i = 0; i < verNum; ++i) {
		Graph[i] = new int[verNum];
		for (int j = 0; j < verNum; ++j)
			Graph[i][j] = INF;
	}

}
void ElecNetSys::Clear() {
	for (int i = 0; i < verNum; ++i)
		delete[]Graph[i];
	delete[]Graph;
	Graph = NULL;
}

void ElecNetSys::Init() {
	cout << "请输入顶点的个数: ";
	cin >> verNum;
	if (Graph != NULL)Clear();
	Alloc();
	string ver_name;
	cout << "请依次输入各顶点的名称: \n";
	Map.clear();
	Vertex.clear();
	for (int i = 0; i < verNum; ++i) {
		cin >> ver_name;
		Vertex.push_back(ver_name);
		Map[ver_name] = i;
	}
}

void ElecNetSys::AddEdge() {
	string verFromName, verToName;
	int cost;
	while (cout << "请输入两个顶点及边: ",cin >> verFromName >> verToName >> cost,
		verFromName != "?"&&verToName != "?"&&cost != 0) {
		Graph[Map[verFromName]][Map[verToName]] = cost;
		Graph[Map[verToName]][Map[verFromName]] = cost;
	}
}

bool ElecNetSys::Build() {
	cout << "请输入起始顶点: ";
	string source;
	cin >> source;
	Path.clear();
	//cost数组存储到源点的最短路径,near数组存储到最小生成树集合中最近的顶点
	int *cost = new int[verNum], *near = new int[verNum];      
	mincost = 0;
	bool bRet = buildPrimTree(Map[source], cost, near);
	if(bRet)cout << "生成Prim最小生成树！" << endl;
	else cout << "没有最小生成树！" << endl;
	delete cost;delete near;
	return bRet;
}

bool ElecNetSys::buildPrimTree(int src, int *cost, int *near) {
	int i, j;
	for (i = 0; i < verNum; ++i) {                            //初始化
		cost[i] = Graph[src][i];
		near[i] = Graph[src][i] == INF ? -1 : src;
	}
	cost[src] = 0;
	for (i = 1; i < verNum; ++i) {                            //verNum-1条路径
		int minCost = INF, minIndex = src;                    //记录最短路径及其下标
		for (j = 0; j < verNum; ++j) {
			if (cost[j] && minCost > cost[j]) {
				minCost = cost[j];
				minIndex = j;
			}
		}
		if (minCost == INF)return false;                      //图不连通
		mincost += minCost;                                   //记录最小生成树代价
		Path.push_back(make_pair(near[minIndex], minIndex));  //记录路径
		cost[minIndex] = 0;                                   //表示已添加
		for (j = 0; j < verNum; ++j) {                        //更新最短路
			if (Graph[j][minIndex] < cost[j]) {
				cost[j] = Graph[j][minIndex];
				near[j] = minIndex;
			}
		}
	}
	return true;
}

void ElecNetSys::ShowTree() {
	cout << "最小生成树的顶点及边为:\n";
	int from, to;
	for (int i = 0; i < Path.size(); ++i) {
		from = Path[i].first;
		to = Path[i].second;
		cout << Vertex[from] << "-(" << Graph[from][to] 
			<< ")->" << Vertex[to] << endl;
	}
	cout << "\n最小代价为: " << mincost << "万元" << endl;
}

void ElecNetSys::showTitle()const {
	cout << "**           电网造价模拟系统           **\n"
		<< "==========================================\n"
		<< "**            A --- 创建电网顶点        **\n"
		<< "**            B --- 添加电网的边        **\n"
		<< "**            C --- 构造最小生成树      **\n"
		<< "**            D --- 显示最小生成树      **\n"
		<< "**            E --- 退出程序            **\n"
		<< "=========================================="
		<< endl;
}

void ElecNetSys::Run() {
	char choose;
	bool bRet = true;
	showTitle();
	do {
		cout << "\n请选择操作: ";
		cin >> choose;
		switch (choose) {
		case 'A':
			Init();
			break;
		case 'B':
			AddEdge();
			break;
		case 'C':
			bRet = Build();
			break;
		case 'D':
			if(bRet)ShowTree();
			else cout << "没有最小生成树！" << endl;
			break;
		case 'E':
			break;
		default:
			cout << "输入非法！请重试" << endl;
			break;
		}
	} while (choose != 'E');
}