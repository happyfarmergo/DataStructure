#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Sys {
public:
	Sys() {}
	~Sys() {}
	int search();							 //搜索模式串出现次数
	void Start();							 //主程序
	void readFile(string &fileName);		 //读取目标串
	void showFile(string &fileName);		 //打印目标串
private:
	int KMP(int pos, int *next);			 //KMP匹配
	void getNext(int *next);				 //创建next数组
private:
	string Pattern;							 //模式串
	string Target;							 //目标串
};

void Sys::getNext(int *next) {
	next[0] = -1;									   //初始值
	int j = 0, k = -1, len = Pattern.length() - 1;	   //对应next[j] = k
	while (j < len) {								   //循环length-2次
		if (k == -1 || Pattern[k] == Pattern[j]) {	   //对应位置相等或者全不匹配
			next[++j] = ++k;
		} else 
			k = next[k];							   //递推下去
	}
}

int Sys::KMP(int pos, int *next) {
	int lenT = Target.length(), lenP = Pattern.length();
	int i = pos, j = 0;
	while (i < lenT&&j < lenP) {
		if (j == -1 || Pattern[j] == Target[i]) {      //对应位置匹配或者全不匹配
			++i;
			++j;
		} else                                         //对应位置不匹配，回溯
			j = next[j];
	}
	return j < lenP ? -1 : i - j;                      //返回匹配成功的起始位置或者-1
}

int Sys::search() {
	int *next = new int[Pattern.length()];
	getNext(next);
	int pos = 0, count = 0;
	while ((pos = KMP(pos, next)) != -1) {
		++pos;
		++count;
	}
	delete[]next;
	return count;
}

void Sys::readFile(string &fileName) {
	string content;
	cin >> fileName;
	ofstream fout(fileName);
	if (!fout) {
		cerr << "Error!";
		exit(-1);
	}
	cout << "\n请输入一段英文:";
	while (getline(cin, content)) {
		Target += content;
		fout << content << endl;
	}
	fout.close();
	cout << "本文本已保存在文本文件\"" << fileName << "\"中" << endl;
}

void Sys::showFile(string &fileName) {
	string content;
	ifstream fin(fileName);
	cout << "显示源文件\"" << fileName << "\":" << endl;
	if (!fin) {
		cerr << "Error!";
		exit(-1);
	}
	while (getline(fin, content)) {
		cout << content << endl;
	}
	fin.close();
}

void Sys::Start() {
	string fileName;
	cout << "关键字检索系统" << endl << "请输入文件名:";

	readFile(fileName);

	cout << "请输入要检索的关键字:";
	cin.clear();
	cin >> Pattern;

	showFile(fileName);

	cout << "在源文件中共检索到:" << search() << "个关键字\"" << Pattern << "\"" << endl;

}