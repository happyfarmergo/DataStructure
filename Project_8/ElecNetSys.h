#include <iostream>
#include <string>
#include <map>
#include <vector>

#define INF 0x7fffffff

using namespace std;

class ElecNetSys {
private:
	int **Graph;                               //�ڽӾ���
	vector<pair<int, int>>Path;                //��С������·��
	vector<string>Vertex;					   //��������
	map<string, int>Map;					   //����:�±�
	int verNum;								   //�������
	int mincost;							   //������������С����
private:
	void showTitle()const;					   //��ӡ����
	bool buildPrimTree(int src, int *cost, int *near);//�����ĸ�������
public:
	ElecNetSys();
	~ElecNetSys();
	void Init();                               //��ʼ��
	void AddEdge();							   //��ӱ�
	void ShowTree();						   //��ʾ��С������
	bool Build();							   //������С������
	void Clear();							   //ɾ����С������
	void Alloc();                              //����ͼ�ռ�
	void Run();								   //������
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
	cout << "�����붥��ĸ���: ";
	cin >> verNum;
	if (Graph != NULL)Clear();
	Alloc();
	string ver_name;
	cout << "��������������������: \n";
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
	while (cout << "�������������㼰��: ",cin >> verFromName >> verToName >> cost,
		verFromName != "?"&&verToName != "?"&&cost != 0) {
		Graph[Map[verFromName]][Map[verToName]] = cost;
		Graph[Map[verToName]][Map[verFromName]] = cost;
	}
}

bool ElecNetSys::Build() {
	cout << "��������ʼ����: ";
	string source;
	cin >> source;
	Path.clear();
	//cost����洢��Դ������·��,near����洢����С����������������Ķ���
	int *cost = new int[verNum], *near = new int[verNum];      
	mincost = 0;
	bool bRet = buildPrimTree(Map[source], cost, near);
	if(bRet)cout << "����Prim��С��������" << endl;
	else cout << "û����С��������" << endl;
	delete cost;delete near;
	return bRet;
}

bool ElecNetSys::buildPrimTree(int src, int *cost, int *near) {
	int i, j;
	for (i = 0; i < verNum; ++i) {                            //��ʼ��
		cost[i] = Graph[src][i];
		near[i] = Graph[src][i] == INF ? -1 : src;
	}
	cost[src] = 0;
	for (i = 1; i < verNum; ++i) {                            //verNum-1��·��
		int minCost = INF, minIndex = src;                    //��¼���·�������±�
		for (j = 0; j < verNum; ++j) {
			if (cost[j] && minCost > cost[j]) {
				minCost = cost[j];
				minIndex = j;
			}
		}
		if (minCost == INF)return false;                      //ͼ����ͨ
		mincost += minCost;                                   //��¼��С����������
		Path.push_back(make_pair(near[minIndex], minIndex));  //��¼·��
		cost[minIndex] = 0;                                   //��ʾ�����
		for (j = 0; j < verNum; ++j) {                        //�������·
			if (Graph[j][minIndex] < cost[j]) {
				cost[j] = Graph[j][minIndex];
				near[j] = minIndex;
			}
		}
	}
	return true;
}

void ElecNetSys::ShowTree() {
	cout << "��С�������Ķ��㼰��Ϊ:\n";
	int from, to;
	for (int i = 0; i < Path.size(); ++i) {
		from = Path[i].first;
		to = Path[i].second;
		cout << Vertex[from] << "-(" << Graph[from][to] 
			<< ")->" << Vertex[to] << endl;
	}
	cout << "\n��С����Ϊ: " << mincost << "��Ԫ" << endl;
}

void ElecNetSys::showTitle()const {
	cout << "**           �������ģ��ϵͳ           **\n"
		<< "==========================================\n"
		<< "**            A --- ������������        **\n"
		<< "**            B --- ��ӵ����ı�        **\n"
		<< "**            C --- ������С������      **\n"
		<< "**            D --- ��ʾ��С������      **\n"
		<< "**            E --- �˳�����            **\n"
		<< "=========================================="
		<< endl;
}

void ElecNetSys::Run() {
	char choose;
	bool bRet = true;
	showTitle();
	do {
		cout << "\n��ѡ�����: ";
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
			else cout << "û����С��������" << endl;
			break;
		case 'E':
			break;
		default:
			cout << "����Ƿ���������" << endl;
			break;
		}
	} while (choose != 'E');
}