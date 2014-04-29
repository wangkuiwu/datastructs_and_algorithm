#include <iostream>
#include <queue>
using namespace std;

/**
 * C++ : STL中的队列(queue)的演示程序。
 *
 * @author skywang
 * @date 2013/11/07
 */
int main ()
{
	int tmp=0;
	queue<int> iqueue;

    // 将10, 20, 30 依次加入队列的末尾
    iqueue.push(10);
    iqueue.push(20);
    iqueue.push(30);

    // 删除队列开头的元素
    iqueue.pop();

	// 将“队列开头的元素”赋值给tmp，不删除该元素.
	tmp = iqueue.front();
	cout<<"tmp="<<tmp<<endl;

    // 将40加入到队列的末尾
    iqueue.push(40);

	cout << "empty()=" << iqueue.empty() <<endl;
	cout << "size()=" << iqueue.size() <<endl;
	while (!iqueue.empty()) 
	{
		tmp = iqueue.front();
		cout<<tmp<<endl;
        iqueue.pop();  
	}

	return 0;
}
