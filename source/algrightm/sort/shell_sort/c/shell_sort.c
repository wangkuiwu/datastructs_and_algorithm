/**
 * 希尔排序：C 语言
 *
 * @author skywang
 * @date 2014/03/11
 */

#include <stdio.h>

// 数组长度
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )

/*
 * 希尔排序
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     n -- 数组的长度
 */
void shell_sort1(int a[], int n)
{
	int i,j,gap;

    // gap为步长，每次减为原来的一半。
    for (gap = n / 2; gap > 0; gap /= 2)
    {
		// 共gap个组，对每一组都执行直接插入排序
        for (i = 0 ;i < gap; i++)
		{
			for (j = i + gap; j < n; j += gap) 
			{
				// 如果a[j] < a[j-gap]，则寻找a[j]位置，并将后面数据的位置都后移。
				if (a[j] < a[j - gap])
				{
					int tmp = a[j];
					int k = j - gap;
					while (k >= 0 && a[k] > tmp)
					{
						a[k + gap] = a[k];
						k -= gap;
					}
					a[k + gap] = tmp;
				}
			}
		}

    }
}

/*
 * 对希尔排序中的单个组进行排序
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     n -- 数组总的长度
 *     i -- 组的起始位置
 *     gap -- 组的步长
 *
 *  组是"从i开始，将相隔gap长度的数都取出"所组成的！
 */
void group_sort(int a[], int n, int i,int gap)
{
	int j;

	for (j = i + gap; j < n; j += gap) 
	{
		// 如果a[j] < a[j-gap]，则寻找a[j]位置，并将后面数据的位置都后移。
		if (a[j] < a[j - gap])
		{
			int tmp = a[j];
			int k = j - gap;
			while (k >= 0 && a[k] > tmp)
			{
				a[k + gap] = a[k];
				k -= gap;
			}
			a[k + gap] = tmp;
		}
	}
}

/*
 * 希尔排序
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     n -- 数组的长度
 */
void shell_sort2(int a[], int n)
{
	int i,gap;

    // gap为步长，每次减为原来的一半。
    for (gap = n / 2; gap > 0; gap /= 2)
    {
		// 共gap个组，对每一组都执行直接插入排序
        for (i = 0 ;i < gap; i++)
            group_sort(a, n, i, gap);
    }
}

void main()
{
	int i;
	int a[] = {80,30,60,40,20,10,50,70};
	int ilen = LENGTH(a);

	printf("before sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");

	shell_sort1(a, ilen);
	//shell_sort2(a, ilen);

	printf("after  sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");
}
