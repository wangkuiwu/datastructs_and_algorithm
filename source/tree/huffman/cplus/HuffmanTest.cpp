/**
 * Huffman树测试程序
 *
 * @author skywang
 * @date 2014/03/25
 */

#include <iostream>
#include "Huffman.h"
using namespace std;


int main()
{
	int a[]= {5,6,8,7,15};
	int i, ilen = sizeof(a) / (sizeof(a[0])) ;
	Huffman<int>* tree=new Huffman<int>();

	cout << "== 添加数组: ";
	for(i=0; i<ilen; i++) 
		cout << a[i] <<" ";

	tree->create(a, ilen);

	cout << "\n== 前序遍历: ";
	tree->preOrder();

	cout << "\n== 中序遍历: ";
	tree->inOrder();

	cout << "\n== 后序遍历: ";
	tree->postOrder();
	cout << endl;

	cout << "== 树的详细信息: " << endl;
	tree->print();

	// 销毁二叉树
	tree->destroy();

	return 0;
}
