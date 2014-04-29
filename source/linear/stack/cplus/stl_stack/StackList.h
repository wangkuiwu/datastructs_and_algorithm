
#ifndef STACK_LIST_HXX
#define STACK_LIST_HXX

#include <stack>

template<class T> class StackList{
    public:
		StackList();

		void add(T t);
		T front();
		T pop();
		int size();
		int is_empty();

	private:
		// 向队列添加数据时：(01) 将“已有的全部数据”都移到sin中。 (02) 将“新添加的数据”添加到sin中。
		stack<T> sin;
		// 从队列获取元素时：(01) 将“已有的全部数据”都移到sout中。(02) 返回并删除sout栈顶元素。
		stack<T> sout;
		int count;
};

#endif
