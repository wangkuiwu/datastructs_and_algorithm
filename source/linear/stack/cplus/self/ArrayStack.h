
#ifndef ARRAY_STACK_HXX
#define ARRAY_STACK_HXX

#include <iostream>
#include "ArrayStack.h"
using namespace std;

template<class T> class ArrayStack{
    public:
		ArrayStack();
		~ArrayStack();

		void push(T t);
		T peek();
		T pop();
		int size();
		int isEmpty();
	private:
		T *arr;
		int count;
};

// 创建“栈”，默认大小是12
template<class T>
ArrayStack<T>::ArrayStack() 
{
	arr = new T[12];
	if (!arr) 
	{
		cout<<"arr malloc error!"<<endl;
	}
}

// 销毁“栈”
template<class T>
ArrayStack<T>::~ArrayStack() 
{
	if (arr) 
	{
		delete[] arr;
		arr = NULL;
	}
}

// 将val添加到栈中
template<class T>
void ArrayStack<T>::push(T t) 
{
	//arr[count++] = val;
	arr[count++] = t;
}

// 返回“栈顶元素值”
template<class T>
T ArrayStack<T>::peek() 
{
	return arr[count-1];
}

// 返回“栈顶元素值”，并删除“栈顶元素”
template<class T>
T ArrayStack<T>::pop() 
{
	int ret = arr[count-1];
	count--;
	return ret;
}

// 返回“栈”的大小
template<class T>
int ArrayStack<T>::size() 
{
	return count;
}

// 返回“栈”是否为空
template<class T>
int ArrayStack<T>::isEmpty()
{
	return size()==0;
}

#endif
