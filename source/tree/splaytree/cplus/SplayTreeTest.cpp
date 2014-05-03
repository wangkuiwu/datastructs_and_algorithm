/**
 * C++ 语言: 伸展树
 *
 * @author skywang
 * @date 2014/02/03
 */

#include <iostream>
#include "SplayTree.h"
using namespace std;

static int arr[]= {10,50,40,30,20,60};
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

int main()
{
	int i,ilen;
	SplayTree<int>* tree=new SplayTree<int>();

	cout << "== 依次添加: ";
	ilen = TBL_SIZE(arr);
	for(i=0; i<ilen; i++)
	{
		cout << arr[i] <<" ";
		tree->insert(arr[i]);
	}

	cout << "\n== 前序遍历: ";
	tree->preOrder();

	cout << "\n== 中序遍历: ";
	tree->inOrder();

	cout << "\n== 后序遍历: ";
	tree->postOrder();
	cout << endl;

	cout << "== 最小值: " << tree->minimum() << endl;
	cout << "== 最大值: " << tree->maximum() << endl;
	cout << "== 树的详细信息: " << endl;
	tree->print();

	i = 30;
	cout << "\n== 旋转节点(" << i << ")为根节点";
	tree->splay(i);
	cout << "\n== 树的详细信息: " << endl;
	tree->print();

	// 销毁二叉树
	tree->destroy();

	return 0;
}
