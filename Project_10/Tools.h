#include <ctime>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "SortMachine.h"

#define MAXN 1000000
#define BlankSize 26

using namespace std;

//Debug
template<typename ElemType>
void Print(ElemType Array[], int n) {
	for (int i = 1; i < n; ++i) {
		/*cout << Array[i] << ' ';
		if (i % 10 == 0)cout << endl;*/
		if (Array[i]>Array[i + 1]) {
			cout << "FALSE" << endl;
			return;
		}
	}
	cout << "TRUE";
	cout << endl;
}

//��ʱ����
class Timer {
public:
	Timer() {}
	~Timer() {}
	void Reset() { startTime = clock(); }
	int ElapsedTime() {                       //�����ʱ
		endTime = clock();
		return endTime - startTime;
	}
private:
	clock_t startTime, endTime;
};


//������
class Test {
public:
	Test();
	~Test();
	void show();                                     //��ӡ����
	void getArray(int n);							 //��ʼ����������
	void Run();										 //������
private:
	int *Array;
	SortMachine<int> Sort;
};

Test::Test() {
	Array = new int[MAXN + 1];
	if (Array == NULL) {
		cerr << "�ڴ�������!" << endl;
		exit(-1);
	}
}

Test::~Test() {
	delete[]Array;
}

void Test::show() {
	cout << "**             �����㷨�Ƚ�                 **\n"
		<< "==============================================\n"
		<< "**             1 --- ð������               **\n"
		<< "**             2 --- ѡ������               **\n"
		<< "**             3 --- ֱ�Ӳ�������           **\n"
		<< "**             4 --- ϣ������               **\n"
		<< "**             5 --- ��������               **\n"
		<< "**             6 --- ������                 **\n"
		<< "**             7 --- �鲢����               **\n"
		<< "**             8 --- ��������               **\n"
		<< "**             9 --- �˳�����               **\n"
		<< "==============================================\n"
		<< endl;

}

void Test::getArray(int n) {
	srand((unsigned)time(NULL));
	for (int i = 1; i <= n; ++i)
		Array[i] = rand();
}

void Test::Run() {
	int num, n, expense;
	show();
	cout << "������Ҫ������������ĸ���:";
	cin >> num;
	Timer timer;
	while (true) {
		cout << left << setw(BlankSize) << "\n��ѡ�������㷨:";
		cin >> n;
		Sort.swapTimes = 0;
		getArray(num);
		switch (n) {
		case 1:
			timer.Reset();
			Sort.BubbleSort(Array, num);
			expense = timer.ElapsedTime();
			cout << left << setw(BlankSize) << "ð����������ʱ��:" << expense
				<< "ms\n" << setw(BlankSize) << "ð�����򽻻�����:" << Sort.swapTimes
				<< endl;
			break;
		case 2:
			timer.Reset();
			Sort.SelectSort(Array, num);
			expense = timer.ElapsedTime();
			cout << left << setw(BlankSize) << "ѡ����������ʱ��:" << expense
				<< "ms\n" << setw(BlankSize) << "ѡ�����򽻻�����:" << Sort.swapTimes
				<< endl;
			break;
		case 3:
			timer.Reset();
			Sort.InsertSort(Array, num);
			expense = timer.ElapsedTime();
			cout << left << setw(BlankSize) << "ֱ�Ӳ�����������ʱ��:" << expense
				<< "ms\n" << setw(BlankSize) << "ֱ�Ӳ������򽻻�����:" << Sort.swapTimes
				<< endl;
			break;
		case 4:
			timer.Reset();
			Sort.ShellSort(Array, num);
			expense = timer.ElapsedTime();
			cout << left << setw(BlankSize) << "ϣ����������ʱ��:" << expense
				<< "ms\n" << setw(BlankSize) << "ϣ�����򽻻�����:" << Sort.swapTimes
				<< endl;
			break;
		case 5:
			timer.Reset();
			Sort.QuickSort(Array, num);
			expense = timer.ElapsedTime();
			cout << left << setw(BlankSize) << "������������ʱ��:" << expense
				<< "ms\n" << setw(BlankSize) << "�������򽻻�����:" << Sort.swapTimes
				<< endl;
			break;
		case 6:
			timer.Reset();
			Sort.HeapSort(Array, num);
			expense = timer.ElapsedTime();
			cout << left << setw(BlankSize) << "����������ʱ��:" << expense
				<< "ms\n" << setw(BlankSize) << "�����򽻻�����:" << Sort.swapTimes
				<< endl;
			break;
		case 7:
			timer.Reset();
			Sort.MergeSort(Array, num);
			expense = timer.ElapsedTime();
			cout << left << setw(BlankSize) << "�鲢��������ʱ��:" << expense
				<< "ms\n" << setw(BlankSize) << "�鲢���򽻻�����:" << Sort.swapTimes
				<< endl;
			break;
		case 8:
			timer.Reset();
			Sort.RadixSort(Array, num);
			expense = timer.ElapsedTime();
			cout << left << setw(BlankSize) << "������������ʱ��:" << expense
				<< "ms\n" << setw(BlankSize) << "�������򽻻�����:" << Sort.swapTimes
				<< endl;
			break;
		case 9:
			break;
		default:
			cout << "û�����ѡ�" << endl;
			break;
		}
		//Print(Array, num);
		cout << endl;
		if (n == 9)break;
	}
}
