/**
 * C 语言: AVL树
 *
 * @author skywang
 * @date 2013/11/07
 */

#include <iostream>
#include "AVLTree.h"
using namespace std;

static int arr[]= {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

int main()
{
	int i,ilen;
	AVLTree<int>* tree=new AVLTree<int>();

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

	cout << "== 高度: " << tree->height() << endl;
	cout << "== 最小值: " << tree->minimum() << endl;
	cout << "== 最大值: " << tree->maximum() << endl;
	cout << "== 树的详细信息: " << endl;
	tree->print();

	i = 8;
	cout << "\n== 删除根节点: " << i;
	tree->remove(i);

	cout << "\n== 高度: " << tree->height() ;
	cout << "\n== 中序遍历: " ;
	tree->inOrder();
	cout << "\n== 树的详细信息: " << endl;
	tree->print();

	// 销毁二叉树
	tree->destroy();

	return 0;
}
