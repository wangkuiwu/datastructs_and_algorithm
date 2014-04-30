/**
 * 归并排序：C 语言
 *
 * @author skywang
 * @date 2014/03/12
 */

#include <stdio.h>
#include <stdlib.h>

// 数组长度
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )

/*
 * 将一个数组中的两个相邻有序区间合并成一个
 *
 * 参数说明：
 *     a -- 包含两个有序区间的数组
 *     start -- 第1个有序区间的起始地址。
 *     mid   -- 第1个有序区间的结束地址。也是第2个有序区间的起始地址。
 *     end   -- 第2个有序区间的结束地址。
 */
void merge(int a[], int start, int mid, int end)
{
    int *tmp = (int *)malloc((end-start+1)*sizeof(int));	// tmp是汇总2个有序区的临时区域
    int i = start;			// 第1个有序区的索引
    int j = mid + 1;		// 第2个有序区的索引
    int k = 0;				// 临时区域的索引

    while(i <= mid && j <= end)
    {
		if (a[i] <= a[j])
			tmp[k++] = a[i++];
		else
			tmp[k++] = a[j++];
    }

    while(i <= mid)
        tmp[k++] = a[i++];

    while(j <= end)
        tmp[k++] = a[j++];

	// 将排序后的元素，全部都整合到数组a中。
	for (i = 0; i < k; i++)
		a[start + i] = tmp[i];

    free(tmp);
}

/*
 * 归并排序(从上往下)
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     start -- 数组的起始地址
 *     endi -- 数组的结束地址
 */
void merge_sort_up2down(int a[], int start, int end)
{
    if(a==NULL || start >= end)
        return ;

    int mid = (end + start)/2;
    merge_sort_up2down(a, start, mid); // 递归排序a[start...mid]
    merge_sort_up2down(a, mid+1, end); // 递归排序a[mid+1...end]

	// a[start...mid] 和 a[mid...end]是两个有序空间，
	// 将它们排序成一个有序空间a[start...end]
    merge(a, start, mid, end);
}


/*
 * 对数组a做若干次合并：数组a的总长度为len，将它分为若干个长度为gap的子数组；
 *             将"每2个相邻的子数组" 进行合并排序。
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     len -- 数组的长度
 *     gap -- 子数组的长度
 */
void merge_groups(int a[], int len, int gap)
{
    int i;
    int twolen = 2 * gap;	// 两个相邻的子数组的长度

    // 将"每2个相邻的子数组" 进行合并排序。
    for(i = 0; i+2*gap-1 < len; i+=(2*gap))
	{
        merge(a, i, i+gap-1, i+2*gap-1);
    }

    // 若 i+gap-1 < len-1，则剩余一个子数组没有配对。
	// 将该子数组合并到已排序的数组中。
    if ( i+gap-1 < len-1)
	{
        merge(a, i, i + gap - 1, len - 1);
    }
}

/*
 * 归并排序(从下往上)
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     len -- 数组的长度
 */
void merge_sort_down2up(int a[], int len)
{
    int n;

	if (a==NULL || len<=0)
		return ;

    for(n = 1; n < len; n*=2)
        merge_groups(a, len, n);
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

	merge_sort_up2down(a, 0, ilen-1);		// 归并排序(从上往下)
	//merge_sort_down2up(a, ilen);			// 归并排序(从下往上)

	printf("after  sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");
}
