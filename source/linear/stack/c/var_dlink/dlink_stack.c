
#include <stdio.h>
#include "double_link.h"

/**
 * C 语言: 双向链表实现栈，能存储任意数据。
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
int push(void *p) 
{
	return dlink_insert_first(p);
}

// 返回“栈顶元素值”
void* peek() 
{
	return dlink_get_first();
}

// 返回“栈顶元素值”，并删除“栈顶元素”
void* pop() 
{
	void *p = peek();
	dlink_delete_first();
	return p;
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

static void print_stu(stu *p) 
{
	if (!p)
		return ;

	printf("id=%d, name=%s\n", p->id, p->name);
}

void main()
{
	stu *pval=NULL;

	// 创建“栈”
	create_dlink_stack();

	// 将10, 20, 30 依次推入栈中
	int i=0;
	for (i=0; i<ARR_STU_SIZE-1; i++)
	{
		push(&arr_stu[i]);
	}

	// 将“栈顶元素”赋值给pval，并删除“栈顶元素”
	pval = (stu*)pop();
	//print_stu(pval) ;

	// 只将“栈顶”赋值给pval，不删除该元素.
	pval = peek();
	//print_stu(pval) ;

	push(&arr_stu[ARR_STU_SIZE-1]);


	// 打印栈中的所有元素
	while (!is_empty())
	{
		pval = pop();
		print_stu(pval) ;
	}

	// 销毁栈
	destroy_dlink_stack();
}
