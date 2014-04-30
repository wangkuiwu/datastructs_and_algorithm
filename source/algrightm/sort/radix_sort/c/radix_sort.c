/**
 * 基数排序：C 语言
 *
 * @author skywang
 * @date 2014/03/15
 */

#include <stdio.h>

// 数组长度
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )

/*
 * 获取数组a中最大值
 *
 * 参数说明：
 *     a -- 数组
 *     n -- 数组长度
 */
int get_max(int a[], int n)
{
	int i, max;

	max = a[0];
    for (i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];
    return max;
}

/*
 * 对数组按照"某个位数"进行排序(桶排序)
 *
 * 参数说明：
 *     a -- 数组
 *     n -- 数组长度
 *     exp -- 指数。对数组a按照该指数进行排序。
 *
 * 例如，对于数组a={50, 3, 542, 745, 2014, 154, 63, 616}；
 *    (01) 当exp=1表示按照"个位"对数组a进行排序
 *    (02) 当exp=10表示按照"十位"对数组a进行排序
 *    (03) 当exp=100表示按照"百位"对数组a进行排序
 *    ...
 */
void count_sort(int a[], int n, int exp)
{
    int output[n]; 			// 存储"被排序数据"的临时数组
    int i, buckets[10] = {0};

	// 将数据出现的次数存储在buckets[]中
    for (i = 0; i < n; i++)
        buckets[ (a[i]/exp)%10 ]++;

	// 更改buckets[i]。目的是让更改后的buckets[i]的值，是该数据在output[]中的位置。
    for (i = 1; i < 10; i++)
        buckets[i] += buckets[i - 1];

    // 将数据存储到临时数组output[]中
    for (i = n - 1; i >= 0; i--)
    {
        output[buckets[ (a[i]/exp)%10 ] - 1] = a[i];
        buckets[ (a[i]/exp)%10 ]--;
    }

	// 将排序好的数据赋值给a[]
    for (i = 0; i < n; i++)
        a[i] = output[i];
}

/*
 * 基数排序
 *
 * 参数说明：
 *     a -- 数组
 *     n -- 数组长度
 */
void radix_sort(int a[], int n)
{
    int exp;	// 指数。当对数组按各位进行排序时，exp=1；按十位进行排序时，exp=10；...
    int max = get_max(a, n);	// 数组a中的最大值

	// 从个位开始，对数组a按"指数"进行排序
    for (exp = 1; max/exp > 0; exp *= 10)
        count_sort(a, n, exp);
}

void main()
{
	int i;
	int a[] = {53, 3, 542, 748, 14, 214, 154, 63, 616};
	int ilen = LENGTH(a);

	printf("before sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");

	radix_sort(a, ilen);

	printf("after  sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");
}
