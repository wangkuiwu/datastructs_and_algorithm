#include <iostream>
#include "double_link.h"
using namespace std;

/**
 * C++ 实现双向链表
 *
 * @author skywang
 * @date   2013/11/07
 */
// 构造函数
template<class T>
DoubleLink<T>::DoubleLink() 
{
	// 创建“表头”。注意：表头没有存储数据！
	phead = new DNode<T>();
	phead->prev = phead->next = phead;
	// 设置链表计数为0
	count = 0;
}

// 析构函数
template<class T>
DoubleLink<T>::~DoubleLink() 
{
	// 删除所有的节点
	DNode<T>* ptmp;
	DNode<T>* pnode = phead->next;
	while (pnode != phead)
	{
		ptmp = pnode;
		pnode=pnode->next;
		delete ptmp;
	}

	// 删除"表头"
	delete phead;
	phead = NULL;
}

// 返回节点数目
template<class T>
int DoubleLink<T>::size() 
{
	return count;
}

// 返回链表是否为空
template<class T>
int DoubleLink<T>::is_empty() 
{
	return count==0;
}

// 获取第index位置的节点
template<class T>
DNode<T>* DoubleLink<T>::get_node(int index) 
{
	// 判断参数有效性
	if (index<0 || index>=count)
	{
		cout << "get node failed! the index in out of bound!" << endl;
		return NULL;
	}

	// 正向查找
	if (index <= count/2)
	{
		int i=0;
		DNode<T>* pindex = phead->next;
		while (i++ < index) {
			pindex = pindex->next;
		}

		return pindex;
	}

	// 反向查找
	int j=0;
	int rindex = count - index -1;
	DNode<T>* prindex = phead->prev;
	while (j++ < rindex) {
		prindex = prindex->prev;
	}

	return prindex;
}

// 获取第index位置的节点的值
template<class T>
T DoubleLink<T>::get(int index) 
{
	return get_node(index)->value;
}

// 获取第1个节点的值
template<class T>
T DoubleLink<T>::get_first() 
{
	return get_node(0)->value;
}

// 获取最后一个节点的值
template<class T>
T DoubleLink<T>::get_last() 
{
	return get_node(count-1)->value;
}

// 将节点插入到第index位置之前
template<class T>
int DoubleLink<T>::insert(int index, T t) 
{
	if (index == 0)
		return insert_first(t);

	DNode<T>* pindex = get_node(index);
	DNode<T>* pnode  = new DNode<T>(t, pindex->prev, pindex);
	pindex->prev->next = pnode;
	pindex->prev = pnode;
	count++;

	return 0;
}

// 将节点插入第一个节点处。
template<class T>
int DoubleLink<T>::insert_first(T t) 
{
	DNode<T>* pnode  = new DNode<T>(t, phead, phead->next);
	phead->next->prev = pnode;
	phead->next = pnode;
	count++;

	return 0;
}

// 将节点追加到链表的末尾
template<class T>
int DoubleLink<T>::append_last(T t) 
{
	DNode<T>* pnode = new DNode<T>(t, phead->prev, phead);
	phead->prev->next = pnode;
	phead->prev = pnode;
	count++;

	return 0;
}

// 删除index位置的节点
template<class T>
int DoubleLink<T>::del(int index) 
{
	DNode<T>* pindex = get_node(index);
	pindex->next->prev = pindex->prev;
	pindex->prev->next = pindex->next;
	delete pindex;
	count--;

	return 0;
}

// 删除第一个节点
template<class T>
int DoubleLink<T>::delete_first() 
{
	return del(0);
}

// 删除最后一个节点
template<class T>
int DoubleLink<T>::delete_last() 
{
	return del(count-1);
}

int main()
{
	DoubleLink<int>* pdlink = new DoubleLink<int>();

	// 将10, 20, 30, 40, 50 添加到双向链表中。
	pdlink->insert(0, 20);		// 将 20 插入到第一个位置
	pdlink->append_last(30);	// 将 30 追加到链表末尾
	pdlink->insert_first(10);	// 将 10 插入到第一个位置
	pdlink->append_last(40);	// 将 40 追加到链表末尾
	pdlink->append_last(50);	// 将 50 追加到链表末尾
	pdlink->append_last(60);	// 将 60 追加到链表末尾

	pdlink->del(2);				// 删除位置2的节点，即删除“30”
	pdlink->delete_first();		// 删除第一个节点，即删除“10”
	pdlink->delete_last();		// 删除最后一个节点，即删除“60”

	cout << "is_empty()=" << pdlink->is_empty() <<endl;
	cout << "size()=" << pdlink->size() <<endl;

	int first = pdlink->get_first();	// 获取第一个节点的值，即“20”
	int mid = pdlink->get(1);			// 获取位置1的节点的值，即“40”
	int last = pdlink->get_last();		// 获取最后一个节点的值，即“50”
	cout << "first=" << first <<endl;
	cout << "mid=" << mid <<endl;
	cout << "last=" << last <<endl;

	// 打印出全部的节点
	for (int i=0; i<pdlink->size(); i++)
		cout << "pdlink("<<i<<")=" << pdlink->get(i) <<endl;

	return 0;
}
