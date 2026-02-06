#include <iostream>
#include <time.h>
#include <queue>
using namespace std;

const int N = 1000010;//允许的最大数据量
int a[N];

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
}

void init(int a[], int len, int seed) {// 初始化数组
	srand(seed);
	for (int i = 0; i < len; i++) {
		a[i] = rand();
	}
}
void print(int a[], int len) {
	cout << "最大的十个数：";
	for (int i = len - 1; i > len - 11; i--) {
		cout << a[i] << ' ';
	}
	cout << endl;
}

int main() {
	int len = 1000000;

	init(a, len, 1);

	//快速排序方法
	cout << "快速排序方法：" << endl;
	int t0 = clock();
	QuickSort(a, len);
	int t1 = clock();
	print(a, len);
	cout << "耗时：" << t1 - t0 << endl;

	init(a, len, 1);

	//堆排序方法
	cout << endl << "堆排序方法：" << endl;
	priority_queue <int, vector<int>, less<int> > q;
	t0 = clock();
	int num = 0;
	for (int i = 0; i < len - 1; i++) {
		if (num < 10) {
			q.push(a[i]);
			continue;
		}
		if (a[i] > q.top()) {
			q.pop();
			q.push(a[i]);
		}
	}
	t1 = clock();
	cout << "最大的十个数：";
	for (int i = 0; i < 10; i++) {
		cout << q.top() << ' ';
		q.pop();
	}
	cout << endl;
	cout << "耗时：" << t1 - t0 << endl;
}
