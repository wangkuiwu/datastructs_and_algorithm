
#include <stdio.h>
#include "list.h"
#include "double_link.h"

typedef struct tag_stu
{
	int id;
	char name[20];
}stu;

static stu arr_stu[] = 
{
	{10, "sky"},
	{20, "jody"},
	{30, "vic"},
	{40, "dan"},
};
#define ARR_STU_SIZE ( (sizeof(arr_stu)) / (sizeof(arr_stu[0])) )


/**
 * C 语言: 双向链表实现栈，只能存储int数据。
 *
 * @author skywang
 * @date 2013/11/07
 */
// 创建栈
int create_dlink_stack() 
{
	return create_dlink();
}

// 销毁栈
int destroy_dlink_stack() 
{
	return destroy_dlink();
}

// 将val添加到栈中
int push(int val) 
{
	return dlink_insert_first(val);
}

// 返回“栈顶元素值”
int peek() 
{
	return dlink_get_first();
}

// 返回“栈顶元素值”，并删除“栈顶元素”
int pop() 
{
	int ret = peek();
	dlink_delete_first();
	return ret;
}

// 返回“栈”的大小
int size() 
{
	return dlink_size();
}

// 返回“栈”是否为空
int is_empty()
{
	return dlink_is_empty();
}

// 打印“栈”
void print_dlink_stack()
{
	return print_dlink();
}

void main()
{
	stu *pval=NULL;
	INIT_LIST_HEAD();
	// 创建“栈”
	create_dlink_stack();

	// 将10, 20, 30 依次推入栈中
	push(10);
	push(20);
	push(30);

	//print_dlink_stack();	// 打印栈

	// 将“栈顶元素”赋值给tmp，并删除“栈顶元素”
	tmp = pop();
	printf("tmp=%d\n", tmp);
	//print_dlink_stack();	// 打印栈

	// 只将“栈顶”赋值给tmp，不删除该元素.
	tmp = peek();
	printf("tmp=%d\n", tmp);
	//print_dlink_stack();	// 打印栈

	push(40);
	print_dlink_stack();	// 打印栈

	// 销毁栈
	destroy_dlink_stack();
}
