#include <iostream>
#include "ArrayQueue.h"
using namespace std;

/**
 * C++ : 数组实现“队列”，能存储任意数据。
 *
 * @author skywang
 * @date 2013/11/07
 */
int main() 
{
	int tmp=0;
	ArrayQueue<int> *astack = new ArrayQueue<int>();

    // 将10, 20, 30 依次推入队列中
    astack->add(10);
    astack->add(20);
    astack->add(30);

    // 将“队列开头元素”赋值给tmp，并删除“该元素”
    tmp = astack->pop();
	cout<<"tmp="<<tmp<<endl;

	// 只将“队列开头的元素”赋值给tmp，不删除该元素.
	tmp = astack->front();
	cout<<"tmp="<<tmp<<endl;

    astack->add(40);

	cout<<"is_empty()="<<astack->is_empty()<<endl;
	cout<<"size()="<<astack->size()<<endl;
	while (!astack->is_empty())
	{
		tmp = astack->pop();
		cout<<tmp<<endl;
	}

	return 0;
}
