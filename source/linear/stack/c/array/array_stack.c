#include <stdio.h>
#include <malloc.h>

/**
 * C 语言: 数组实现的栈，只能存储int数据。
 *
 * @author skywang
 * @date 2013/11/07
 */

// 保存数据的数组
static int *arr=NULL;
// 栈的实际大小
static int count;

// 创建“栈”，默认大小是12
int create_array_stack(int sz) 
{
	arr = (int *)malloc(sz*sizeof(int));
	if (!arr) 
	{
		printf("arr malloc error!");
		return -1;
	}

	return 0;
}

// 销毁“栈”
int destroy_array_stack() 
{
	if (arr) 
	{
		free(arr);
		arr = NULL;
	}

	return 0;
}

// 将val添加到栈中
void push(int val) 
{
	arr[count++] = val;
}

// 返回“栈顶元素值”
int peek() 
{
	return arr[count-1];
}

// 返回“栈顶元素值”，并删除“栈顶元素”
int pop() 
{
	int ret = arr[count-1];
	count--;
	return ret;
}

// 返回“栈”的大小
int size() 
{
	return count;
}

// 返回“栈”是否为空
int is_empty()
{
	return size()==0;
}

// 打印“栈”
void print_array_stack()
{
	if (is_empty()) 
	{
		printf("stack is Empty\n");
		return ;
	}

	printf("stack size()=%d\n", size());

	int i=size()-1;
	while (i>=0)
	{
		printf("%d\n", arr[i]);
		i--;
	}
}


void main() 
{
	int tmp=0;

	// 创建“栈”
	create_array_stack(12);

	// 将10, 20, 30 依次推入栈中
	push(10);
	push(20);
	push(30);

	//print_array_stack();	// 打印栈

	// 将“栈顶元素”赋值给tmp，并删除“栈顶元素”
	tmp = pop();
	printf("tmp=%d\n", tmp);
	//print_array_stack();	// 打印栈

	// 只将“栈顶”赋值给tmp，不删除该元素.
	tmp = peek();
	printf("tmp=%d\n", tmp);
	//print_array_stack();	// 打印栈

	push(40);
	print_array_stack();	// 打印栈

	// 销毁栈
	destroy_array_stack();
}

