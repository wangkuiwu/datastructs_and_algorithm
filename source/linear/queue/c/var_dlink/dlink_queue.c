
#include <stdio.h>
#include "double_link.h"

/**
 * C 语言: 双向链表实现“队列”，能存储任意数据。
 *
 * @author skywang
 * @date 2013/11/07
 */

// 创建队列
int create_dlink_queue() 
{
	return create_dlink();
}

// 销毁队列
int destroy_dlink_queue() 
{
	return destroy_dlink();
}

// 将p添加到队列的末尾
int add(void *p) 
{
	return dlink_append_last(p);
}

// 返回“队列开头元素”
void* front() 
{
	return dlink_get_first();
}

// 返回“队列开头的元素”，并删除“该元素”
void* pop() 
{
	void *p = dlink_get_first();
	dlink_delete_first();
	return p;
}

// 返回“队列”的大小
int size() 
{
	return dlink_size();
}

// 返回“队列”是否为空
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

	// 创建“队列”
	create_dlink_queue();

	// 将10, 20, 30 依次推入队列中
	int i=0;
	for (i=0; i<ARR_STU_SIZE-1; i++)
	{
		add(&arr_stu[i]);
	}

	// 将“队列开头的元素”赋值给tmp，并删除“该元素”
	pval = (stu*)pop();
	print_stu(pval) ;

	// 只将“队列开头的元素”赋值给tmp，不删除该元素.
	pval = front();
	print_stu(pval) ;

	add(&arr_stu[ARR_STU_SIZE-1]);

	printf("is_empty()=%d\n", is_empty());
	printf("size()=%d\n", size());
	// 打印队列中的所有元素
	while (!is_empty())
	{
		pval = pop();
		print_stu(pval) ;
	}

	// 销毁队列
	destroy_dlink_queue();
}
