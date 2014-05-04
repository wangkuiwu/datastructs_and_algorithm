/**
 * C++实现的Huffman树。
 *
 * 构造Huffman树时，使用到了最小堆。
 *
 * @author skywang
 * @date 2014/03/25
 */

#ifndef _HUFFMAN_TREE_HPP_
#define _HUFFMAN_TREE_HPP_

#include <iomanip>
#include <iostream>
#include "HuffmanNode.h"
#include "MinHeap.h"
using namespace std;

template <class T>
class Huffman {
	private:
		HuffmanNode<T> *mRoot;	// 根结点

    public:
		Huffman();
		~Huffman();

		// 前序遍历"Huffman树"
		void preOrder();
		// 中序遍历"Huffman树"
		void inOrder();
		// 后序遍历"Huffman树"
		void postOrder();

		// 创建Huffman树
		void create(T a[], int size);
		// 销毁Huffman树
		void destroy();

		// 打印Huffman树
		void print();
	private:
		// 前序遍历"Huffman树"
		void preOrder(HuffmanNode<T>* tree) const;
		// 中序遍历"Huffman树"
		void inOrder(HuffmanNode<T>* tree) const;
		// 后序遍历"Huffman树"
		void postOrder(HuffmanNode<T>* tree) const;

		// 销毁Huffman树
		void destroy(HuffmanNode<T>* &tree);

		// 打印Huffman树
		void print(HuffmanNode<T>* tree, T key, int direction);
};

/* 
 * 构造函数
 */
template <class T>
Huffman<T>::Huffman():mRoot(NULL)
{
}

/* 
 * 析构函数
 */
template <class T>
Huffman<T>::~Huffman() 
{
	destroy();
}

/*
 * 前序遍历"Huffman树"
 */
template <class T>
void Huffman<T>::preOrder(HuffmanNode<T>* tree) const
{
	if(tree != NULL)
	{
		cout<< tree->key << " " ;
		preOrder(tree->left);
		preOrder(tree->right);
	}
}

template <class T>
void Huffman<T>::preOrder() 
{
	preOrder(mRoot);
}

/*
 * 中序遍历"Huffman树"
 */
template <class T>
void Huffman<T>::inOrder(HuffmanNode<T>* tree) const
{
	if(tree != NULL)
	{
		inOrder(tree->left);
		cout<< tree->key << " " ;
		inOrder(tree->right);
	}
}

template <class T>
void Huffman<T>::inOrder() 
{
	inOrder(mRoot);
}

/*
 * 后序遍历"Huffman树"
 */
template <class T>
void Huffman<T>::postOrder(HuffmanNode<T>* tree) const
{
	if(tree != NULL)
	{
		postOrder(tree->left);
		postOrder(tree->right);
		cout<< tree->key << " " ;
	}
}

template <class T>
void Huffman<T>::postOrder() 
{
	postOrder(mRoot);
}

/* 
 * 创建Huffman树
 *
 * 参数说明：
 *     a 权值数组
 *     size 数组大小
 *
 * 返回值：
 *     Huffman树的根节点
 */
template <class T>
void Huffman<T>::create(T a[], int size)
{
    int i;
    HuffmanNode<T> *left, *right, *parent;
	MinHeap<T> *heap = new MinHeap<T>();

	// 建立数组a对应的最小堆
    heap->create(a, size);
 
    for(i=0; i<size-1; i++)
    {   
        left = heap->dumpFromMinimum();  // 最小节点是左孩子
        right = heap->dumpFromMinimum(); // 其次才是右孩子
 
		// 新建parent节点，左右孩子分别是left/right；
		// parent的大小是左右孩子之和
        parent = new HuffmanNode<T>(left->key+right->key, left, right, NULL);
        left->parent = parent;
		right->parent = parent;
 

		// 将parent节点数据拷贝到"最小堆"中
		if (heap->copyOf(parent)!=0)
		{
			cout << "插入失败!" << endl << "结束程序" << endl;
			destroy(parent);
			parent = NULL;
			break;
		}
    }

	mRoot = parent;

	// 销毁最小堆
	heap->destroy();
	delete heap;
}

/*
 * 销毁Huffman树
 */
template <class T>
void Huffman<T>::destroy(HuffmanNode<T>* &tree)
{
	if (tree==NULL)
		return ;

	if (tree->left != NULL)
		return destroy(tree->left);
	if (tree->right != NULL)
		return destroy(tree->right);

	delete tree;
	tree=NULL;
}

template <class T>
void Huffman<T>::destroy()
{
	destroy(mRoot);
}

/*
 * 打印"Huffman树"
 *
 * key        -- 节点的键值 
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
template <class T>
void Huffman<T>::print(HuffmanNode<T>* tree, T key, int direction)
{
	if(tree != NULL)
	{
		if(direction==0)	// tree是根节点
			cout << setw(2) << tree->key << " is root" << endl;
		else				// tree是分支节点
			cout << setw(2) << tree->key << " is " << setw(2) << key << "'s "  << setw(12) << (direction==1?"right child" : "left child") << endl;

		print(tree->left, tree->key, -1);
		print(tree->right,tree->key,  1);
	}
}

template <class T>
void Huffman<T>::print()
{
	if (mRoot != NULL)
		print(mRoot, mRoot->key, 0);
}

#endif
