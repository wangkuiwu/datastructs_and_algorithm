
#include <stdio.h>
#include <malloc.h>

/**
 * C 语言: 单向链表实现的栈，只能存储int数据。
 *
 * @author skywang
 * @date 2013/11/07
 */

// 单向链表的“节点”
struct node {
	int val;
	struct node* next;
};

// 单向链表的“表头”
static struct node *phead=NULL;

// 创建节点，val为节点值
static struct node* create_node(int val) 
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

	while (phead != NULL) {
		pnode = phead;
		phead = phead->next;
		free(pnode);
	}
	return 0;
}

// 将val插入到链表的表头位置
static struct node* push(int val) 
{
	struct node *pnode = NULL;
	
	pnode = create_node(val);
	pnode->next = phead;
	phead = pnode;
	
	return phead;
}

// 删除链表的表头
static int pop() 
{
	if (!phead)
	{
		printf("remove failed! link is empty!");
		return -1;
	}
	
	int ret;
	struct node *pnode;
	ret = phead->val;
	pnode = phead;
	phead = phead->next;
	free(pnode);

	return ret;
}

// 返回链表的表头节点的值
static int peek() 
{
	if (!phead)
	{
		printf("peek failed! link is empty!");
		return -1;
	}

	return phead->val;
}

// 返回链表中节点的个数
static int size() 
{
	int count=0;
	struct node *pnode=phead;

	while (pnode != NULL) {
		pnode = pnode->next;
		count++;
	}
	return count;
}

// 链表是否为空
static int is_empty() 
{
	return phead==NULL;
}

// 打印“栈”
static void print_single_link()
{
	if (is_empty()) 
	{
		printf("stack is Empty\n");
		return 0;
	}

	printf("stack size()=%d\n", size());

	struct node *pnode=NULL;

	while (phead != NULL) {
		printf("%d\n", phead->val);
		pnode = phead;
		phead = phead->next;
		free(pnode);
	}
}

void main() 
{
	int tmp=0;

	// 将10, 20, 30 依次推入栈中
	push(10);
	push(20);
	push(30);

	//print_single_link();	// 打印栈

	// 将“栈顶元素”赋值给tmp，并删除“栈顶元素”
	tmp = pop();
	printf("tmp=%d\n", tmp);
	//print_single_link();	// 打印栈

	// 只将“栈顶”赋值给tmp，不删除该元素.
	tmp = peek();
	printf("tmp=%d\n", tmp);
	//print_single_link();	// 打印栈

	push(40);
	print_single_link();	// 打印栈

	// 销毁栈
	destroy_single_link();
}
