
#include <stdio.h>
#include <malloc.h>

/**
 * C 语言: 单链表实现“队列”，只能存储int数据。
 *
 * @author skywang
 * @date 2013/11/07
 */

// 单链表节点
struct node {
	int val;
	struct node* next;
};

// 表头
static struct node *phead=NULL;

// 创建节点，val为节点值
static struct node* create_node(val) 
{
	struct node *pnode=NULL;
	pnode = (struct node*)malloc(sizeof(struct node));
	if (!pnode)
		return NULL;
	pnode->val = val;
	pnode->next = NULL;
	
	return pnode;
}

// 销毁单向链表
static int destroy_single_link() 
{
	struct node *pnode=NULL;

	while (phead != NULL) 
	{
		pnode = phead;
		phead = phead->next;
		free(pnode);
	}
	return 0;
}

// 将val添加到队列的末尾
static void add(int val) 
{
	if (!phead)
	{
		phead = create_node(val);
		return ;
	}

	struct node *pnode = create_node(val);
	struct node *pend = phead;
	while (pend->next)
		pend = pend->next;

	pend->next = pnode;
}

// 返回“队列开头元素”
int front() 
{
	return phead->val;
}

// 返回并删除“队列开头元素”
static int pop() 
{
	int ret = phead->val;
	struct node *pnode = phead;

	phead = phead->next;
	free(pnode);

	return ret;
}

// 返回链表中节点的个数
static int size() 
{
	int count=0;
	struct node *pend = phead;

	while (pend) 
	{
		pend = pend->next;
		count++;
	}

	return count;
}

// 链表是否为空
static int is_empty() 
{
	return size()==0;
}

void main() 
{
	int tmp=0;

	// 将10, 20, 30 依次加入到队列中
	add(10);
	add(20);
	add(30);

	// 将“队列开头元素”赋值给tmp，并删除“该元素”
	tmp = pop();
	printf("tmp=%d\n", tmp);

	// 只将“队列开头的元素”赋值给tmp，不删除该元素.
	tmp = front();
	printf("tmp=%d\n", tmp);

	add(40);

	printf("is_empty()=%d\n", is_empty());
	printf("size()=%d\n", size());
	while (!is_empty())
	{
		printf("%d\n", pop());
	}

	// 销毁队列
	destroy_single_link();
}
