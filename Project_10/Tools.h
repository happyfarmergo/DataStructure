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

//计时器类
class Timer {
public:
	Timer() {}
	~Timer() {}
	void Reset() { startTime = clock(); }
	int ElapsedTime() {                       //计算耗时
		endTime = clock();
		return endTime - startTime;
	}
private:
	clock_t startTime, endTime;
};


//测试类
class Test {
public:
	Test();
	~Test();
	void show();                                     //打印标题
	void getArray(int n);							 //初始化数组数据
	void Run();										 //主程序
private:
	int *Array;
	SortMachine<int> Sort;
};

Test::Test() {
	Array = new int[MAXN + 1];
	if (Array == NULL) {
		cerr << "内存分配错误!" << endl;
		exit(-1);
	}
}

Test::~Test() {
	delete[]Array;
}

void Test::show() {
	cout << "**             排序算法比较                 **\n"
		<< "==============================================\n"
		<< "**             1 --- 冒泡排序               **\n"
		<< "**             2 --- 选择排序               **\n"
		<< "**             3 --- 直接插入排序           **\n"
		<< "**             4 --- 希尔排序               **\n"
		<< "**             5 --- 快速排序               **\n"
		<< "**             6 --- 堆排序                 **\n"
		<< "**             7 --- 归并排序               **\n"
		<< "**             8 --- 基数排序               **\n"
		<< "**             9 --- 退出程序               **\n"
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
	cout << "请输入要产生的随机数的个数:";
	cin >> num;
	Timer timer;
	while (true) {
		cout << left << setw(BlankSize) << "\n请选择排序算法:";
		cin >> n;
		Sort.swapTimes = 0;
		getArray(num);
		switch (n) {
		case 1:
			timer.Reset();
			Sort.BubbleSort(Array, num);
			expense = timer.ElapsedTime();
			cout << left << setw(BlankSize) << "冒泡排序所用时间:" << expense
				<< "ms\n" << setw(BlankSize) << "冒泡排序交换次数:" << Sort.swapTimes
				<< endl;
			break;
		case 2:
			timer.Reset();
			Sort.SelectSort(Array, num);
			expense = timer.ElapsedTime();
			cout << left << setw(BlankSize) << "选择排序所用时间:" << expense
				<< "ms\n" << setw(BlankSize) << "选择排序交换次数:" << Sort.swapTimes
				<< endl;
			break;
		case 3:
			timer.Reset();
			Sort.InsertSort(Array, num);
			expense = timer.ElapsedTime();
			cout << left << setw(BlankSize) << "直接插入排序所用时间:" << expense
				<< "ms\n" << setw(BlankSize) << "直接插入排序交换次数:" << Sort.swapTimes
				<< endl;
			break;
		case 4:
			timer.Reset();
			Sort.ShellSort(Array, num);
			expense = timer.ElapsedTime();
			cout << left << setw(BlankSize) << "希尔排序所用时间:" << expense
				<< "ms\n" << setw(BlankSize) << "希尔排序交换次数:" << Sort.swapTimes
				<< endl;
			break;
		case 5:
			timer.Reset();
			Sort.QuickSort(Array, num);
			expense = timer.ElapsedTime();
			cout << left << setw(BlankSize) << "快速排序所用时间:" << expense
				<< "ms\n" << setw(BlankSize) << "快速排序交换次数:" << Sort.swapTimes
				<< endl;
			break;
		case 6:
			timer.Reset();
			Sort.HeapSort(Array, num);
			expense = timer.ElapsedTime();
			cout << left << setw(BlankSize) << "堆排序所用时间:" << expense
				<< "ms\n" << setw(BlankSize) << "堆排序交换次数:" << Sort.swapTimes
				<< endl;
			break;
		case 7:
			timer.Reset();
			Sort.MergeSort(Array, num);
			expense = timer.ElapsedTime();
			cout << left << setw(BlankSize) << "归并排序所用时间:" << expense
				<< "ms\n" << setw(BlankSize) << "归并排序交换次数:" << Sort.swapTimes
				<< endl;
			break;
		case 8:
			timer.Reset();
			Sort.RadixSort(Array, num);
			expense = timer.ElapsedTime();
			cout << left << setw(BlankSize) << "基数排序所用时间:" << expense
				<< "ms\n" << setw(BlankSize) << "基数排序交换次数:" << Sort.swapTimes
				<< endl;
			break;
		case 9:
			break;
		default:
			cout << "没有这个选项！" << endl;
			break;
		}
		//Print(Array, num);
		cout << endl;
		if (n == 9)break;
	}
}
