#ifndef _SORT_MACHINE_H_
#define _SORT_MACHINE_H_

#include "LinkList.h"

#define CUTOFF 30


//排序算法类
template<typename ElemType>
class SortMachine {
public:
	void InsertSort(ElemType Array[], int n);                          //直接插入排序
	void BubbleSort(ElemType Array[], int n);						   //冒泡排序
	void ShellSort(ElemType Array[], int n);						   //希尔排序
	void SelectSort(ElemType Array[], int n);						   //选择排序
	void QuickSort(ElemType Array[], int n);						   //快速排序
	void HeapSort(ElemType Array[], int n);							   //堆排序
	void MergeSort(ElemType Array[], int n);						   //归并排序
	void RadixSort(ElemType Array[], int n);                           //基数排序
	int swapTimes;
private:
	void Swap(ElemType &x, ElemType &y);
	void Insert(ElemType *Array, int length);                          //数据规模较小时用插入排序
	ElemType Medium3(ElemType Array[], int left, int right);           //三数取中函数
	void Partition(ElemType Array[], int left, int right);			   //快速排序的辅助函数
	void SiftAdjust(ElemType Array[], int i, int n);				   //堆排序的辅助函数
	void Merge(ElemType Array[], int Temp[], int left, int right);	   //归并排序的辅助函数
	void Distribute(ElemType Array[], int n, int r, int i, LinkList<ElemType> *list);//基数排序的辅助函数
	void Collect(ElemType Array[], int n, int r, LinkList<ElemType> *list);//基数排序的辅助函数
};

template<typename ElemType>
inline void SortMachine<ElemType>::Swap(ElemType &x, ElemType &y) {
	ElemType temp = x; x = y; y = temp;
}

//插入排序
template<typename ElemType>
void SortMachine<ElemType>::InsertSort(ElemType Array[], int n) {
	int i, j;
	for (i = 2; i <= n; ++i) {
		Array[0] = Array[i];
		for (j = i - 1; Array[0] < Array[j]; --j) {
			Array[j + 1] = Array[j];
			++swapTimes;
		}
		Array[j + 1] = Array[0];
		++swapTimes;
	}
}

//冒泡排序
template<typename ElemType>
void SortMachine<ElemType>::BubbleSort(ElemType Array[], int n) {
	int i, j;
	for (i = 1; i < n; ++i) {
		for (j = 1; j <= n - i; ++j) {
			if (Array[j] > Array[j + 1]) {
				Swap(Array[j], Array[j + 1]);
				++swapTimes;
			}
		}
	}
}

//希尔排序
template<typename ElemType>
void SortMachine<ElemType>::ShellSort(ElemType Array[], int n) {
	int Sedgewick[] = { 146305, 64769, 36289, 16001, 8929, 3905, 
		2161, 929, 505, 209, 109, 41, 19, 5, 1, 0 };
	int Si, i, j, k;
	for (Si = 0; Sedgewick[Si] >= n; ++Si)
		;
	for (k = Sedgewick[Si]; k > 0; k = Sedgewick[++Si]) {
		for (i = k + 1; i <= n; ++i) {
			Array[0] = Array[i];
			for (j = i - k; j >= 0 && Array[0] < Array[j]; j -= k) {
				Array[j + k] = Array[j];
				++swapTimes;
			}
			Array[j + k] = Array[0];
			++swapTimes;
		}
	}
}

//选择排序
template<typename ElemType>
void SortMachine<ElemType>::SelectSort(ElemType Array[], int n) {
	int i, j, k;
	for (i = 1; i < n; ++i) {
		k = i;
		for (j = i + 1; j <= n; ++j) {
			if (Array[j] < Array[k]) {
				k = j;
				++swapTimes;
			}
		}
		Swap(Array[i], Array[k]);
		++swapTimes;
	}
}


//快速排序
template<typename ElemType>
void SortMachine<ElemType>::QuickSort(ElemType Array[], int n) {
	Partition(Array, 1, n);
}

template<typename ElemType>
void SortMachine<ElemType>::Partition(ElemType Array[], int left, int right) {
	if (right - left <= CUTOFF) {
		Insert(Array + left, right - left + 1);
		return;
	}
	int low = left, high = right - 1;
	ElemType pivot = Medium3(Array, left, right);
	while (low < high) {
		while (Array[++low] < pivot)
			;
		while (Array[--high] > pivot)
			;
		if (low < high) {
			Swap(Array[low], Array[high]);
			++swapTimes;
		}
	}
	Swap(Array[low], Array[right - 1]);
	++swapTimes;
	if (low - 1 > left)
		Partition(Array, left, low - 1);
	if (low + 1 < right)
		Partition(Array, low + 1, right);
}

//在left，mid，right三者中取中间值作为主元
template<typename ElemType>
inline ElemType SortMachine<ElemType>::Medium3(ElemType Array[], int left, int right) {
	int mid = (left + right) >> 1;
	if (Array[left] > Array[mid])
		Swap(Array[left], Array[mid]);
	if (Array[left] > Array[right])
		Swap(Array[left], Array[right]);
	if (Array[mid] > Array[right])
		Swap(Array[mid], Array[right]);
	Swap(Array[mid], Array[right - 1]);
	return Array[right - 1];
}

//递归到数据规模小于CUTOFF时调用插入
template<typename ElemType>
void SortMachine<ElemType>::Insert(ElemType *Array, int length) {
	int i, j;
	ElemType temp;
	for (i = 1; i < length; ++i) {
		temp = Array[i];
		for (j = i - 1; j >= 0 && temp < Array[j]; --j) {
			Array[j + 1] = Array[j];
			++swapTimes;
		}
		Array[j + 1] = temp;
		++swapTimes;
	}
}

//堆排序
template<typename ElemType>
void SortMachine<ElemType>::HeapSort(ElemType Array[], int n) {
	int i;
	for (i = n / 2; i > 0; --i)
		SiftAdjust(Array, i, n);
	for (i = n; i >= 2; --i) {
		Swap(Array[i], Array[1]);
		++swapTimes;
		SiftAdjust(Array, 1, i - 1);
	}
}

template<typename ElemType>
void SortMachine<ElemType>::SiftAdjust(ElemType Array[], int i, int n) {
	for (int parent = i, child = parent << 1; child <= n; child = child << 1) {
		if (child < n&&Array[child] < Array[child + 1])
			++child;
		if (Array[parent] >= Array[child])break;
		Swap(Array[parent], Array[child]);
		++swapTimes;
		parent = child;
	}
}


//归并排序
template<typename ElemType>
void SortMachine<ElemType>::MergeSort(ElemType Array[], int n) {
	int *Temp = new int[n + 1];
	Merge(Array, Temp, 1, n);
	delete[]Temp;
}

template<typename ElemType>
void SortMachine<ElemType>::Merge(ElemType Array[], int Temp[], int left, int right) {
	if (left < right) {
		int mid = (left + right) >> 1;
		Merge(Array, Temp, left, mid);
		Merge(Array, Temp, mid + 1, right);
		int i, j, k;
		for (i = left, j = mid + 1, k = left; i <= mid&&j <= right;) {
			if (Array[i] < Array[j])
				Temp[k++] = Array[i++];
			else
				Temp[k++] = Array[j++];
			++swapTimes;
		}
		swapTimes += mid + 1 - i + right + 1 - j;
		while (i <= mid)
			Temp[k++] = Array[i++];
		while (j <= right)
			Temp[k++] = Array[j++];
		for (i = left; i <= right; ++i)
			Array[i] = Temp[i];
	}
}

//基数排序
template<typename ElemType>
void SortMachine<ElemType>::RadixSort(ElemType Array[], int n) {
	const int radix = 10, digit = 5;
	LinkList<ElemType> *list = new LinkList<ElemType>[radix];
	for (int i = 1; i <= digit; ++i) {
		Distribute(Array, n, radix, i, list);
		Collect(Array, n, radix, list);
	}
	delete []list;
}

//第i趟分配
template<typename ElemType>
void SortMachine<ElemType>::Distribute(ElemType Array[], int n, int r, int i, LinkList<ElemType> *list) {
	int index;
	for (int power = pow((double)r, i - 1), j = 1; j <= n; ++j) {
		index = (Array[j] / power) % r;
		list[index].InsertLast(Array[j]);
	}
}

//第i趟收集
template<typename ElemType>
void SortMachine<ElemType>::Collect(ElemType Array[], int n, int r, LinkList<ElemType> *list) {
	for (int k = 1, j = 0; j < r; ++j) {
		ElemType elem;
		while (!list[j].Empty()) {
			list[j].DeleteFirst(elem);
			Array[k++] = elem;
		}
	}
}

#endif