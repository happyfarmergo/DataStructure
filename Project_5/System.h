#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Sys {
public:
	Sys() {}
	~Sys() {}
	int search();							 //����ģʽ�����ִ���
	void Start();							 //������
	void readFile(string &fileName);		 //��ȡĿ�괮
	void showFile(string &fileName);		 //��ӡĿ�괮
private:
	int KMP(int pos, int *next);			 //KMPƥ��
	void getNext(int *next);				 //����next����
private:
	string Pattern;							 //ģʽ��
	string Target;							 //Ŀ�괮
};

void Sys::getNext(int *next) {
	next[0] = -1;									   //��ʼֵ
	int j = 0, k = -1, len = Pattern.length() - 1;	   //��Ӧnext[j] = k
	while (j < len) {								   //ѭ��length-2��
		if (k == -1 || Pattern[k] == Pattern[j]) {	   //��Ӧλ����Ȼ���ȫ��ƥ��
			next[++j] = ++k;
		} else 
			k = next[k];							   //������ȥ
	}
}

int Sys::KMP(int pos, int *next) {
	int lenT = Target.length(), lenP = Pattern.length();
	int i = pos, j = 0;
	while (i < lenT&&j < lenP) {
		if (j == -1 || Pattern[j] == Target[i]) {      //��Ӧλ��ƥ�����ȫ��ƥ��
			++i;
			++j;
		} else                                         //��Ӧλ�ò�ƥ�䣬����
			j = next[j];
	}
	return j < lenP ? -1 : i - j;                      //����ƥ��ɹ�����ʼλ�û���-1
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
	cout << "\n������һ��Ӣ��:";
	while (getline(cin, content)) {
		Target += content;
		fout << content << endl;
	}
	fout.close();
	cout << "���ı��ѱ������ı��ļ�\"" << fileName << "\"��" << endl;
}

void Sys::showFile(string &fileName) {
	string content;
	ifstream fin(fileName);
	cout << "��ʾԴ�ļ�\"" << fileName << "\":" << endl;
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
	cout << "�ؼ��ּ���ϵͳ" << endl << "�������ļ���:";

	readFile(fileName);

	cout << "������Ҫ�����Ĺؼ���:";
	cin.clear();
	cin >> Pattern;

	showFile(fileName);

	cout << "��Դ�ļ��й�������:" << search() << "���ؼ���\"" << Pattern << "\"" << endl;

}