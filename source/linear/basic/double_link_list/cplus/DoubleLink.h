
#ifndef DOUBLE_LINK_HXX
#define DOUBLE_LINK_HXX

#include <iostream>
using namespace std;

template<class T> 
struct DNode 
{
	public:
		T value;
		DNode *prev;
		DNode *next;
	public:
		DNode() { }
		DNode(T t, DNode *prev, DNode *next) {
			this->value = t;
			this->prev  = prev;
			this->next  = next;
	   	}
};

template<class T> 
class DoubleLink 
{
	public:
		DoubleLink();
		~DoubleLink();

		int size();
		int is_empty();

		T get(int index);
		T get_first();
		T get_last();

		int insert(int index, T t);
		int insert_first(T t);
		int append_last(T t);

		int del(int index);
		int delete_first();
		int delete_last();

	private:
		int count;
		DNode<T> *phead;
	private:
		DNode<T> *get_node(int index);
};

template<class T>
DoubleLink<T>::DoubleLink() : count(0)
{
	// 创建“表头”。注意：表头没有存储数据！
	phead = new DNode<T>();
	phead->prev = phead->next = phead;
	// 设置链表计数为0
	//count = 0;
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



#endif
