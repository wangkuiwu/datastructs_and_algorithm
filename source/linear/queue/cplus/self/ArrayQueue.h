
#ifndef ARRAY_QUEUE_HXX
#define ARRAY_QUEUE_HXX

#include <iostream>
using namespace std;

template<class T> class ArrayQueue{
    public:
		ArrayQueue();
		~ArrayQueue();

		void add(T t);
		T front();
		T pop();
		int size();
		int is_empty();

	private:
		T *arr;
		int count;
};

// 创建“队列”，默认大小是12
template<class T>
ArrayQueue<T>::ArrayQueue() 
{
	arr = new T[12];
	if (!arr) 
	{
		cout<<"arr malloc error!"<<endl;
	}
}

// 销毁“队列”
template<class T>
ArrayQueue<T>::~ArrayQueue() 
{
	if (arr) 
	{
		delete[] arr;
		arr = NULL;
	}
}

// 将val添加到队列的末尾
template<class T>
void ArrayQueue<T>::add(T t) 
{
	arr[count++] = t;
}


// 返回“队列开头元素”
template<class T>
T ArrayQueue<T>::front() 
{
	return arr[0];
}

// 返回并删除“队列末尾的元素”
template<class T>
T ArrayQueue<T>::pop() 
{
	int i = 0;;
	T ret = arr[0];

	count--;
	while (i++<count)
		arr[i-1] = arr[i];

	return ret;
}

// 返回“队列”的大小
template<class T>
int ArrayQueue<T>::size() 
{
	return count;
}

// 返回“队列”是否为空
template<class T>
int ArrayQueue<T>::is_empty()
{
	return count==0;
}


#endif
