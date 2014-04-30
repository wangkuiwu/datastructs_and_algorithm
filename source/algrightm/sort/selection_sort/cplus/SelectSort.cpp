/**
 * 选择排序：C++
 *
 * @author skywang
 * @date 2014/03/11
 */

#include <iostream>
using namespace std;

/*
 * 选择排序
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     n -- 数组的长度
 */
void selectSort(int* a, int n)
{
	int i;		// 有序区的末尾位置
	int j;		// 无序区的起始位置
	int min;	// 无序区中最小元素位置

	for(i=0; i<n; i++)
	{
		min=i;

		// 找出"a[i+1] ... a[n]"之间的最小元素，并赋值给min。
		for(j=i+1; j<n; j++)
		{
			if(a[j] < a[min])
				min=j;
		}

		// 若min!=i，则交换 a[i] 和 a[min]。
		// 交换之后，保证了a[0] ... a[i] 之间的元素是有序的。
		if(min != i)
		{
			int tmp = a[i];
			a[i] = a[min];
			a[min] = tmp;
		}
	}
}

int main()
{
	int i;
	int a[] = {20,40,30,10,60,50};
	int ilen = (sizeof(a)) / (sizeof(a[0]));

	cout << "before sort:";
	for (i=0; i<ilen; i++)
		cout << a[i] << " ";
	cout << endl;

	selectSort(a, ilen);

	cout << "after  sort:";
	for (i=0; i<ilen; i++)
		cout << a[i] << " ";
	cout << endl;

	return 0;
}
