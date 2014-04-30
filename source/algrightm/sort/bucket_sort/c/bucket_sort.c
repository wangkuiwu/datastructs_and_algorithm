/**
 * 桶排序：C 语言
 *
 * @author skywang
 * @date 2014/03/13
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 数组长度
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )

/*
 * 桶排序
 *
 * 参数说明：
 *     a -- 待排序数组
 *     n -- 数组a的长度
 *     max -- 数组a中最大值的范围
 */
void bucket_sort(int a[], int n, int max)
{
	int i, j;
    int *buckets;

    if (a==NULL || n<1 || max<1)
        return ;

    // 创建一个容量为max的数组buckets，并且将buckets中的所有数据都初始化为0。
    if ((buckets=(int *)malloc(max*sizeof(int)))==NULL)
        return ;
    memset(buckets, 0, max*sizeof(int));

	// 1. 计数
    for(i = 0; i < n; i++) 
        buckets[a[i]]++; 

	// 2. 排序
	for (i = 0, j = 0; i < max; i++) 
		while( (buckets[i]--) >0 )
			a[j++] = i;

	free(buckets);
}

void main()
{
	int i;
	int a[] = {8,2,3,4,3,6,6,3,9};
	int ilen = LENGTH(a);

	printf("before sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");

	bucket_sort(a, ilen, 10); // 桶排序

	printf("after  sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");
}
