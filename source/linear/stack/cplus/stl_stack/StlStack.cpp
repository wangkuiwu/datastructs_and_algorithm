#include <iostream>
#include <stack>
using namespace std;

/**
 * C++ 语言: STL 自带的“栈”(stack)的示例。
 *
 * @author skywang
 * @date 2013/11/07
 */
int main ()
{
	int tmp=0;
	stack<int> istack;

    // 将10, 20, 30 依次推入栈中
    istack.push(10);
    istack.push(20);
    istack.push(30);

    // 将“栈顶元素”赋值给tmp，并删除“栈顶元素”
    istack.pop();

    // 只将“栈顶”赋值给tmp，不删除该元素.
    tmp = istack.top();

    istack.push(40);

	while (!istack.empty())
	{
		tmp = istack.top();
		istack.pop();
		cout<<tmp<<endl;
	}

	return 0;
}
