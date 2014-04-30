/**
 * 直接插入排序：C 语言
 *
 * @author skywang
 * @date 2014/03/11
 */

#include <stdio.h>

// 数组长度
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )

/*
 * 直接插入排序
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     n -- 数组的长度
 */
void insert_sort(int a[], int n)
{
	int i, j, k;

	for (i = 1; i < n; i++)
	{
		//为a[i]在前面的a[0...i-1]有序区间中找一个合适的位置
		for (j = i - 1; j >= 0; j--)
			if (a[j] < a[i])
				break;

		//如找到了一个合适的位置
		if (j != i - 1)
		{
			//将比a[i]大的数据向后移
			int temp = a[i];
			for (k = i - 1; k > j; k--)
				a[k + 1] = a[k];
			//将a[i]放到正确位置上
			a[k + 1] = temp;
		}
	}
}

void main()
{
	int i;
	int a[] = {20,40,30,10,60,50};
	int ilen = LENGTH(a);

	printf("before sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");

	insert_sort(a, ilen);

	printf("after  sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");
}
