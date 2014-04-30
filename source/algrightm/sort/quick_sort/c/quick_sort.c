/**
 * 快速排序：C 语言
 *
 * @author skywang
 * @date 2014/03/11
 */

#include <stdio.h>

// 数组长度
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )

/*
 * 快速排序
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     l -- 数组的左边界(例如，从起始位置开始排序，则l=0)
 *     r -- 数组的右边界(例如，排序截至到数组末尾，则r=a.length-1)
 */
void quick_sort(int a[], int l, int r)
{
    if (l < r)
    {
		int i,j,x;

        i = l;
        j = r;
        x = a[i];
        while (i < j)
        {
            while(i < j && a[j] > x)
				j--; // 从右向左找第一个小于x的数
            if(i < j)
				a[i++] = a[j];
            while(i < j && a[i] < x)
				i++; // 从左向右找第一个大于x的数
            if(i < j)
				a[j--] = a[i];
        }
        a[i] = x;
        quick_sort(a, l, i-1); /* 递归调用 */
        quick_sort(a, i+1, r); /* 递归调用 */
    }
}

void main()
{
	int i;
	//int a[] = {30,40,60,10,20,50};
	int a[] = {10,20,30,40,50,60};
	int ilen = LENGTH(a);

	printf("before sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");

	quick_sort(a, 0, ilen-1);

	printf("after  sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");
}
