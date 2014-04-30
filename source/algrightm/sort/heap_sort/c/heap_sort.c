/**
 * 堆排序：C 语言
 *
 * @author skywang
 * @date 2014/03/12
 */

#include <stdio.h>

// 数组长度
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )
#define swap(a,b) (a^=b,b^=a,a^=b)

/* 
 * (最大)堆的向下调整算法
 *
 * 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
 *     其中，N为数组下标索引值，如数组中第1个数对应的N为0。
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     start -- 被下调节点的起始位置(一般为0，表示从第1个开始)
 *     end   -- 截至范围(一般为数组中最后一个元素的索引)
 */
void maxheap_down(int a[], int start, int end)
{
    int c = start;			// 当前(current)节点的位置
    int l = 2*c + 1;		// 左(left)孩子的位置
    int tmp = a[c];			// 当前(current)节点的大小
    for (; l <= end; c=l,l=2*l+1)
    {
		// "l"是左孩子，"l+1"是右孩子
        if ( l < end && a[l] < a[l+1])
            l++;		// 左右两孩子中选择较大者，即m_heap[l+1]
        if (tmp >= a[l])
            break;		// 调整结束
		else			// 交换值
        {
            a[c] = a[l];
            a[l]= tmp;
        }
    }
}

/*
 * 堆排序(从小到大)
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     n -- 数组的长度
 */
void heap_sort_asc(int a[], int n)
{
    int i;

    // 从(n/2-1) --> 0逐次遍历。遍历之后，得到的数组实际上是一个(最大)二叉堆。
    for (i = n / 2 - 1; i >= 0; i--)
        maxheap_down(a, i, n-1);

    // 从最后一个元素开始对序列进行调整，不断的缩小调整的范围直到第一个元素
    for (i = n - 1; i > 0; i--)
    {
        // 交换a[0]和a[i]。交换后，a[i]是a[0...i]中最大的。
		swap(a[0], a[i]);
		// 调整a[0...i-1]，使得a[0...i-1]仍然是一个最大堆。
		// 即，保证a[i-1]是a[0...i-1]中的最大值。
        maxheap_down(a, 0, i-1);
    }
}

/* 
 * (最小)堆的向下调整算法
 *
 * 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
 *     其中，N为数组下标索引值，如数组中第1个数对应的N为0。
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     start -- 被下调节点的起始位置(一般为0，表示从第1个开始)
 *     end   -- 截至范围(一般为数组中最后一个元素的索引)
 */
void minheap_down(int a[], int start, int end)
{
    int c = start;			// 当前(current)节点的位置
    int l = 2*c + 1;		// 左(left)孩子的位置
    int tmp = a[c];			// 当前(current)节点的大小
    for (; l <= end; c=l,l=2*l+1)
    {
		// "l"是左孩子，"l+1"是右孩子
        if ( l < end && a[l] > a[l+1])
            l++;		// 左右两孩子中选择较小者
        if (tmp <= a[l])
            break;		// 调整结束
		else			// 交换值
        {
            a[c] = a[l];
            a[l]= tmp;
        }
    }
}

/*
 * 堆排序(从大到小)
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     n -- 数组的长度
 */
void heap_sort_desc(int a[], int n)
{
    int i;

    // 从(n/2-1) --> 0逐次遍历每。遍历之后，得到的数组实际上是一个最小堆。
    for (i = n / 2 - 1; i >= 0; i--)
        minheap_down(a, i, n-1);

    // 从最后一个元素开始对序列进行调整，不断的缩小调整的范围直到第一个元素
    for (i = n - 1; i > 0; i--)
    {
        // 交换a[0]和a[i]。交换后，a[i]是a[0...i]中最小的。
		swap(a[0], a[i]);
		// 调整a[0...i-1]，使得a[0...i-1]仍然是一个最小堆。
		// 即，保证a[i-1]是a[0...i-1]中的最小值。
        minheap_down(a, 0, i-1);
    }
}

void main()
{
	int i;
	int a[] = {20,30,90,40,70,110,60,10,100,50,80};
	int ilen = LENGTH(a);

	printf("before sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");

	heap_sort_asc(a, ilen);			// 升序排列
	//heap_sort_desc(a, ilen);		// 降序排列

	printf("after  sort:");
	for (i=0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");
}
