
#include <iostream>
using namespace std;

#include "StackList.h"

/**
 * c++语言： 用2个“栈”实现队列
 *
 * @author skywang
 * @date 2013/11/07
 */

template<class T>
StackList<T>::StackList() 
{
	count=0;
}

// 将t添加到队列中
template<class T>
void StackList<T>::add(T t)
{
	// 将“已有的全部数据”都移到sin中
	while (!sout.empty())
	{
		sin.push(sout.top());
		sout.pop();
	}

	// 将“新添加的数据”添加到sin中。
	sin.push(t);
	// 统计数+1
	count++;
}

// 返回队列开头的元素
template<class T>
T StackList<T>::front()
{
	// 将“已有的全部数据”都移到sout中
	while (!sin.empty())
	{
		sout.push(sin.top());
		sin.pop();
	}

	// 返回sout栈顶元素
	return sout.top();
}


// 删除并返回队列开头的元素
template<class T>
T StackList<T>::pop()
{
	// 将“已有的全部数据”都移到sout中
	while (!sin.empty())
	{
		sout.push(sin.top());
		sin.pop();
	}

	// 返回并删除sout栈顶元素
	T t = sout.top();
	sout.pop();
	// 统计数-1
	count--;

	return t;
}

template<class T>
int StackList<T>::size()
{
	return count;
}

template<class T>
int StackList<T>::is_empty()
{
	return count==0;
}


int main()
{
	int tmp;

	// 创建“队列”
	StackList<int>* plist = new StackList<int>();

	// 将10, 20, 30 依次推入队列中
	plist->add(10);
	plist->add(20);
	plist->add(30);

	// 将“队列开头的元素”赋值给tmp，并删除“该元素”
	tmp = plist->pop();
	cout << "tmp=" << tmp <<endl;

	// 只将“队列开头的元素”赋值给tmp，不删除该元素.
	tmp = plist->front();
	cout << "tmp=" << tmp <<endl;

	plist->add(40);

	// 打印队列
	cout << "is_empty()=" << plist->is_empty() <<endl;
	cout << "size()=" << plist->size() <<endl;
	while (!plist->is_empty())
	{
		cout << "tmp=" << plist->pop() <<endl;
	}
	return 0;
}
