/**
 * 最小堆：为Huffman树服务的。
 *
 * @author skywang
 * @date 2014/03/25
 */

#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

static HuffmanNode *m_heap;	// 最小堆的数组
static int m_capacity;		// 总的容量
static int m_size;			// 当前有效数据的数量
 
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
    HuffmanNode tmp = m_heap[c];	// 当前(current)节点

    while(l <= end)
    {
		// "l"是左孩子，"l+1"是右孩子
        if(l < end && m_heap[l].key > m_heap[l+1].key)
            l++;		// 左右两孩子中选择较小者，即m_heap[l+1]
        if(tmp.key <= m_heap[l].key)
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
    HuffmanNode tmp = m_heap[c];		// 当前节点(current)

    while(c > 0)
    {
        if(m_heap[p].key <= tmp.key)
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
 * 将node插入到二叉堆中
 *
 * 返回值：
 *     0，表示成功
 *    -1，表示失败
 */
int dump_to_minheap(HuffmanNode *node)
{
    // 如果"堆"已满，则返回
    if(m_size == m_capacity)
        return -1;
 
    m_heap[m_size] = *node;     // 将"node的数据"全部复制到"数组末尾"
    filter_up(m_size);			// 向上调整堆
    m_size++;					// 堆的实际容量+1

    return 0;
}

/*
 * 交换两个HuffmanNode节点的全部数据
 */
static void swap_node(int i, int j)
{
	HuffmanNode tmp = m_heap[i];
	m_heap[i] = m_heap[j];
	m_heap[j] = tmp;
}

/* 
 * 新建一个节点，并将最小堆中最小节点的数据复制给该节点。
 * 然后除最小节点之外的数据重新构造成最小堆。
 *
 * 返回值：
 *     失败返回NULL。
 */
HuffmanNode* dump_from_minheap()
{
    // 如果"堆"已空，则返回
    if(m_size == 0)
		return NULL;

	HuffmanNode *node;
    if((node = (HuffmanNode *)malloc(sizeof(HuffmanNode))) == NULL)
		return NULL;

	// 将"最小节点的全部数据"复制给node
	*node = m_heap[0];

	swap_node(0, m_size-1);				// 交换"最小节点"和"最后一个节点"
    minheap_filterdown(0, m_size-2);	// 将m_heap[0...m_size-2]构造成一个最小堆
	m_size--;						

	return node;
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
		printf("%d ", m_heap[i].key);
}

/* 
 * 创建最小堆
 *
 * 参数说明：
 *     a -- 数据所在的数组
 *     size -- 数组大小
 */
void create_minheap(Type a[], int size)
{
	int i;

	// 创建最小堆所对应的数组
	m_size = size;
	m_capacity = size;
	m_heap = (HuffmanNode *)malloc(sizeof(HuffmanNode)*size);
	
	// 初始化数组
    for(i=0; i<size; i++)
	{
		m_heap[i].key = a[i];
		m_heap[i].parent = m_heap[i].left = m_heap[i].right = NULL;
	}

    // 从(size/2-1) --> 0逐次遍历。遍历之后，得到的数组实际上是一个最小堆。
    for (i = size / 2 - 1; i >= 0; i--)
		minheap_filterdown(i, size-1);
}

// 销毁最小堆
void destroy_minheap()
{
	m_size = 0;
	m_capacity = 0;
	free(m_heap);
}
