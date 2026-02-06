#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

const int N = 500010;//允许的最大数据量
int a[N], tmp[N];

void check(int a[], int len) {// 遍历一次数组，用于检查排序是否正确完成
	for (int i = 1; i < len; i++) {
		if (a[i] < a[i - 1]) {
			cout << "error" << endl;
			return;
		}
	}
	cout << "complete" << endl;
}

void SelectSort(int a[], int len) {// 选择排序

	// a[0]~a[i-1]已经完成（到达最终状态），循环负责找出后续数组中最小的数，放到a[i]处
	for (int i = 0; i < len - 1; i++) {
		int min = i;// 记录最小值编号
		for (int j = i + 1; j < len; j++) {
			if (a[j] < a[min]) min = j;// 更新最小值
		}
		swap(a[i], a[min]);// 将最小值放入a[i]
	}
	cout << "\nSelectSort" << ' ';
	check(a, len);
}

void BubbleSort(int a[], int len) {// 冒泡排序
	for (int i = 0; i < len; i++)
		for (int j = 1; j < len - i; j++)
			if (a[j] < a[j - 1]) swap(a[j], a[j - 1]);// 逆序，则交换		
	cout << "\nBubbleSort" << ' ';
	check(a, len);
}

void InsertSort(int a[], int len) {// 插入排序

	// a[0]~a[i-1]保持递增有序，循环目的是找到a[i]应当插入的位置，并插入
	for (int i = 1; i < len; i++) {
		int end = a[i];
		for (int j = 0; j < i; j++) {
			if (end < a[j]) {// 找到了a[i]应当插入的位置，开始插入
				for (int k = i; k > j; k--) {
					a[k] = a[k - 1];// 先腾出位置
				}
				a[j] = end;// 插入
			}
		}
	}
	cout << "\nInsertSort" << ' ';
	check(a, len);
}

void QuickSort(int a[], int begin, int end) {// 快速排序
	if (begin >= end)return;
	int key = a[begin];// 选取第一个数作为key
	int p1 = begin, p2 = end;

	// 循环：最终目的是使p1==p2，a[p1]==key，p1左边的数全部小于key，右边的数全部大于等于key
	while (p2 > p1) {
		while (a[p2] >= key && p1 < p2) {
			p2--;
		}
		swap(a[p1], a[p2]);
		while (a[p1] < key && p1 < p2) {
			p1++;
		}
		swap(a[p1], a[p2]);
	}
	QuickSort(a, begin, p1 - 1);
	QuickSort(a, p1 + 1, end);
}

void QuickSort(int a[], int len) {// 快速排序（调用接口）
	QuickSort(a, 0, len - 1);
	cout << "\nQuickSort" << ' ';
	check(a, len);
}

void MergeSort(int a[], int begin, int end) {// 归并排序
	if (begin >= end) return;

	// 划分数组，递归调用
	int mid = (begin + end) / 2;
	MergeSort(a, begin, mid);
	MergeSort(a, mid + 1, end);

	// 进行归并（先将归并后的数据存到临时数组，再转到a）
	int k = 0, i = begin, j = mid + 1;
	while (i <= mid && j <= end)
		if (a[i] <= a[j]) tmp[k++] = a[i++];
		else tmp[k++] = a[j++];
	while (i <= mid) tmp[k++] = a[i++];
	while (j <= end) tmp[k++] = a[j++];
	for (i = begin, j = 0; i <= end; i++, j++) a[i] = tmp[j];
}

void MergeSort(int a[], int len) {// 归并排序（调用接口）
	MergeSort(a, 0, len - 1);
	cout << "\nMergeSort" << ' ';
	check(a, len);
}

void init(int a[], int len, int seed) {// 初始化数组
	srand(seed);
	for (int i = 0; i < len; i++) {
		a[i] = rand();
	}
}

int main() {
	int max_len = 500000;// 最大数组长度，要求小于N
	int sample_quantity = 20;// 对于每一个数据长度，进行sample_quantity次重复实验

	for (int len = max_len / 5; len <= max_len; len += max_len / 5) {
		double Select_t = 0, Bubble_t = 0, Insert_t = 0, Quick_t = 0, Merge_t = 0;
		for (int seed = 0; seed <= sample_quantity; seed++) {
			cout << "Sample size:" << len << "  Sample number:" << seed << endl;

			double t0, t1;// 用于计时

			// 选择排序
			init(a, len, seed);
			t0 = clock();
			SelectSort(a, len);
			t1 = clock();
			cout << "Using time:" << t1 - t0 << endl;
			Select_t += (t1 - t0) / sample_quantity;

			// 冒泡排序
			init(a, len, seed);
			t0 = clock();
			BubbleSort(a, len);
			t1 = clock();
			cout << "Using time:" << t1 - t0 << endl;
			Bubble_t += (t1 - t0) / sample_quantity;

			// 插入排序
			init(a, len, seed);
			t0 = clock();
			InsertSort(a, len);
			t1 = clock();
			cout << "Using time:" << t1 - t0 << endl;
			Insert_t += (t1 - t0) / sample_quantity;

			// 快速排序
			init(a, len, seed);
			t0 = clock();
			QuickSort(a, len);
			t1 = clock();
			cout << "Using time:" << t1 - t0 << endl;
			Quick_t += (t1 - t0) / sample_quantity;

			// 归并排序
			init(a, len, seed);
			t0 = clock();
			MergeSort(a, len);
			t1 = clock();
			cout << "Using time:" << t1 - t0 << endl;
			Merge_t += (t1 - t0) / sample_quantity;

			cout << endl << endl;
		}
		cout << "Sample size:" << len << endl;
		cout << "average select sort time: " << Select_t << endl;
		cout << "average bubble sort time: " << Bubble_t << endl;
		cout << "average insert sort time: " << Insert_t << endl;
		cout << "average quick sort time: " << Quick_t << endl;
		cout << "average merge sort time: " << Merge_t << endl;
		cout << endl << endl << endl;
	}
}