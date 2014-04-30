/**
 * 二叉堆(最小堆)
 *
 * @author skywang
 * @date 2014/03/07
 */

#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

static int m_heap[30];
static int m_capacity=30;	// 总的容量
static int m_size=0;		// 实际容量(初始化为0)
 
/* 
 * 返回data在二叉堆中的索引
 *
 * 返回值：
 *     存在 -- 返回data在数组中的索引
 *     不存在 -- -1
 */
int get_index(int data)
{
	int i=0;

	for(i=0; i<m_size; i++)
		if (data==m_heap[i])
			return i;

	return -1;
}

/* 
 * 最小堆的向下调整算法
 *
 * 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
 *
 * 参数说明：
 *     start -- 被下调节点的起始位置(一般为0，表示从第1个开始)
 *     end   -- 截至范围(一般为数组中最后一个元素的索引)
 */
static void minheap_filterdown(int start, int end)
{
    int c = start; 	 	// 当前(current)节点的位置
    int l = 2*c + 1; 	// 左(left)孩子的位置
    int tmp = m_heap[c];	// 当前(current)节点的大小

    while(l <= end)
    {
		// "l"是左孩子，"l+1"是右孩子
        if(l < end && m_heap[l] > m_heap[l+1])
            l++;		// 左右两孩子中选择较小者，即m_heap[l+1]
        if(tmp <= m_heap[l])
            break;		//调整结束
        else
        {
            m_heap[c] = m_heap[l];
            c = l;
            l = 2*l + 1;   
        }       
    }   
    m_heap[c] = tmp;
}
 
/*
 * 删除最小堆中的data
 *
 * 返回值：
 *      0，成功
 *     -1，失败
 */
int minheap_remove(int data)
{
	int index;
    // 如果"堆"已空，则返回-1
    if(m_size == 0)
        return -1;

	// 获取data在数组中的索引
	index = get_index(data); 
	if (index==-1)
		return -1;

    m_heap[index] = m_heap[--m_size];		// 用最后元素填补
    minheap_filterdown(index, m_size-1);	// 从index号位置开始自上向下调整为最小堆

    return 0;
}

/*
 * 最小堆的向上调整算法(从start开始向上直到0，调整堆)
 *
 * 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
 *
 * 参数说明：
 *     start -- 被上调节点的起始位置(一般为数组中最后一个元素的索引)
 */
static void filter_up(int start)
{
    int c = start;			// 当前节点(current)的位置
    int p = (c-1)/2;		// 父(parent)结点的位置 
    int tmp = m_heap[c];		// 当前节点(current)的大小

    while(c > 0)
    {
        if(m_heap[p] <= tmp)
            break;
        else
        {
            m_heap[c] = m_heap[p];
            c = p;
            p = (p-1)/2;   
        }       
    }
    m_heap[c] = tmp;
}
  
/* 
 * 将data插入到二叉堆中
 *
 * 返回值：
 *     0，表示成功
 *    -1，表示失败
 */
int minheap_insert(int data)
{
    // 如果"堆"已满，则返回
    if(m_size == m_capacity)
        return -1;
 
    m_heap[m_size] = data;		// 将"数组"插在表尾
    filter_up(m_size);			// 向上调整堆
    m_size++;					// 堆的实际容量+1

    return 0;
}
  
/* 
 * 打印二叉堆
 *
 * 返回值：
 *     0，表示成功
 *    -1，表示失败
 */
void minheap_print()
{
	int i;
	for (i=0; i<m_size; i++)
		printf("%d ", m_heap[i]);
}

void main()
{
    int a[] = {80, 40, 30, 60, 90, 70, 10, 50, 20};
	int i, len=LENGTH(a);

	printf("== 依次添加: ");
    for(i=0; i<len; i++)
	{
		printf("%d ", a[i]);
        minheap_insert(a[i]);
	}

	printf("\n== 最 小 堆: ");
	minheap_print();

	i=15;
    minheap_insert(i);
	printf("\n== 添加元素: %d", i);
	printf("\n== 最 小 堆: ");
	minheap_print();

	i=10;
	minheap_remove(i);
	printf("\n== 删除元素: %d", i);
	printf("\n== 最 小 堆: ");
	minheap_print();
	printf("\n");
}
