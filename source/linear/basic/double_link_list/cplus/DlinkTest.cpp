
#include <iostream>
#include "DoubleLink.h"
using namespace std;

// 双向链表操作int数据
void int_test()
{
	int iarr[4] = {10, 20, 30, 40};

	cout << "\n----int_test----" << endl;
	// 创建双向链表
	DoubleLink<int>* pdlink = new DoubleLink<int>();

	pdlink->insert(0, 20);		// 将 20 插入到第一个位置
	pdlink->append_last(10);	// 将 10 追加到链表末尾
	pdlink->insert_first(30);	// 将 30 插入到第一个位置

	// 双向链表是否为空
	cout << "is_empty()=" << pdlink->is_empty() <<endl;
	// 双向链表的大小
	cout << "size()=" << pdlink->size() <<endl;

	// 打印双向链表中的全部数据
	int sz = pdlink->size();
	for (int i=0; i<sz; i++)
		cout << "pdlink("<<i<<")=" << pdlink->get(i) <<endl;
}

void string_test()
{
	string sarr[4] = {"ten", "twenty", "thirty", "forty"};

	cout << "\n----string_test----" << endl;
	// 创建双向链表
	DoubleLink<string>* pdlink = new DoubleLink<string>();

	pdlink->insert(0, sarr[1]);		// 将 sarr中第2个元素 插入到第一个位置
	pdlink->append_last(sarr[0]);	// 将 sarr中第1个元素  追加到链表末尾
	pdlink->insert_first(sarr[2]);	// 将 sarr中第3个元素  插入到第一个位置

	// 双向链表是否为空
	cout << "is_empty()=" << pdlink->is_empty() <<endl;
	// 双向链表的大小
	cout << "size()=" << pdlink->size() <<endl;

	// 打印双向链表中的全部数据
	int sz = pdlink->size();
	for (int i=0; i<sz; i++)
		cout << "pdlink("<<i<<")=" << pdlink->get(i) <<endl;
}

struct stu
{
	int id;
	char name[20];
};

static stu arr_stu[] = 
{
	{10, "sky"},
	{20, "jody"},
	{30, "vic"},
	{40, "dan"},
};
#define ARR_STU_SIZE ( (sizeof(arr_stu)) / (sizeof(arr_stu[0])) )

void object_test()
{
	cout << "\n----object_test----" << endl;
	// 创建双向链表
	DoubleLink<stu>* pdlink = new DoubleLink<stu>();

	pdlink->insert(0, arr_stu[1]);		// 将 arr_stu中第2个元素 插入到第一个位置
	pdlink->append_last(arr_stu[0]);	// 将 arr_stu中第1个元素  追加到链表末尾
	pdlink->insert_first(arr_stu[2]);	// 将 arr_stu中第3个元素  插入到第一个位置

	// 双向链表是否为空
	cout << "is_empty()=" << pdlink->is_empty() <<endl;
	// 双向链表的大小
	cout << "size()=" << pdlink->size() <<endl;

	// 打印双向链表中的全部数据
	int sz = pdlink->size();
	struct stu p;
	for (int i=0; i<sz; i++) 
	{
		p = pdlink->get(i);
		cout << "pdlink("<<i<<")=[" << p.id << ", " << p.name <<"]" <<endl;
	}
}


int main()
{
	int_test();		// 演示向双向链表操作“int数据”。
	string_test();	// 演示向双向链表操作“字符串数据”。
	object_test();	// 演示向双向链表操作“对象”。

	return 0;
}
