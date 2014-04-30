/**
 * C++: 斜堆
 *
 * @author skywang
 * @date 2014/03/31
 */

#ifndef _SKEW_HEAP_HPP_
#define _SKEW_HEAP_HPP_

#include <iomanip>
#include <iostream>
using namespace std;

template <class T>
class SkewNode{
	public:
		T key;				// 关键字(键值)
		SkewNode *left;		// 左孩子
		SkewNode *right;	// 右孩子

		SkewNode(T value, SkewNode *l, SkewNode *r):
			key(value), left(l),right(r) {}
};

template <class T>
class SkewHeap {
	private:
		SkewNode<T> *mRoot;	// 根结点

    public:
		SkewHeap();
		~SkewHeap();

		// 前序遍历"斜堆"
		void preOrder();
		// 中序遍历"斜堆"
		void inOrder();
		// 后序遍历"斜堆"
		void postOrder();

 		// 将other的斜堆合并到this中。
		void merge(SkewHeap<T>* other);
		// 将结点(key为节点键值)插入到斜堆中
		void insert(T key);
		// 删除结点(key为节点键值)
		void remove();

		// 销毁斜堆
		void destroy();

		// 打印斜堆
		void print();
	private:

		// 前序遍历"斜堆"
		void preOrder(SkewNode<T>* heap) const;
		// 中序遍历"斜堆"
		void inOrder(SkewNode<T>* heap) const;
		// 后序遍历"斜堆"
		void postOrder(SkewNode<T>* heap) const;

		// 交换节点x和节点y
		void swapNode(SkewNode<T> *&x, SkewNode<T> *&y);
        // 合并"斜堆x"和"斜堆y"
		SkewNode<T>* merge(SkewNode<T>* &x, SkewNode<T>* &y);

		// 销毁斜堆
		void destroy(SkewNode<T>* &heap);

		// 打印斜堆
		void print(SkewNode<T>* heap, T key, int direction);
};

/* 
 * 构造函数
 */
template <class T>
SkewHeap<T>::SkewHeap():mRoot(NULL)
{
}

/* 
 * 析构函数
 */
template <class T>
SkewHeap<T>::~SkewHeap() 
{
	destroy(mRoot);
}

/*
 * 前序遍历"斜堆"
 */
template <class T>
void SkewHeap<T>::preOrder(SkewNode<T>* heap) const
{
	if(heap != NULL)
	{
		cout<< heap->key << " " ;
		preOrder(heap->left);
		preOrder(heap->right);
	}
}

template <class T>
void SkewHeap<T>::preOrder() 
{
	preOrder(mRoot);
}

/*
 * 中序遍历"斜堆"
 */
template <class T>
void SkewHeap<T>::inOrder(SkewNode<T>* heap) const
{
	if(heap != NULL)
	{
		inOrder(heap->left);
		cout<< heap->key << " " ;
		inOrder(heap->right);
	}
}

template <class T>
void SkewHeap<T>::inOrder() 
{
	inOrder(mRoot);
}

/*
 * 后序遍历"斜堆"
 */
template <class T>
void SkewHeap<T>::postOrder(SkewNode<T>* heap) const
{
	if(heap != NULL)
	{
		postOrder(heap->left);
		postOrder(heap->right);
		cout<< heap->key << " " ;
	}
}

template <class T>
void SkewHeap<T>::postOrder() 
{
	postOrder(mRoot);
}

/*
 * 交换两个节点的内容
 */
template <class T>
void SkewHeap<T>::swapNode(SkewNode<T> *&x, SkewNode<T> *&y)
{
	SkewNode<T> *tmp = x;
	x = y;
	y = tmp;
}


/*
 * 合并"斜堆x"和"斜堆y"
 */
template <class T>
SkewNode<T>* SkewHeap<T>::merge(SkewNode<T>* &x, SkewNode<T>* &y)
{
	if(x == NULL)
		return y;
	if(y == NULL)
		return x;

	// 合并x和y时，将x作为合并后的树的根；
	// 这里的操作是保证: x的key < y的key
	if(x->key > y->key)
		swapNode(x, y);

	// 将x的右孩子和y合并，
	// 合并后直接交换x的左右孩子，而不需要像左倾堆一样考虑它们的npl。
	SkewNode<T> *tmp = merge(x->right, y);
	x->right = x->left;
	x->left  = tmp;

	return x;
}

/*
 * 将other的斜堆合并到this中。
 */
template <class T>
void SkewHeap<T>::merge(SkewHeap<T>* other)
{
	mRoot = merge(mRoot, other->mRoot);
}

/* 
 * 新建键值为key的结点并将其插入到斜堆中
 *
 * 参数说明：
 *     heap 斜堆的根结点
 *     key 插入的结点的键值
 * 返回值：
 *     根节点
 */
template <class T>
void SkewHeap<T>::insert(T key)
{
	SkewNode<T> *node;	// 新建结点

	// 新建节点
	node = new SkewNode<T>(key, NULL, NULL);
	if (node==NULL)
	{
		cout << "ERROR: create node failed!" << endl;
		return ;
	}

	mRoot = merge(mRoot, node);
}

/* 
 * 删除结点
 */
template <class T>
void SkewHeap<T>::remove()
{
    if (mRoot == NULL)
        return NULL;

    SkewNode<T> *l = mRoot->left;
    SkewNode<T> *r = mRoot->right;

	// 删除根节点
	delete mRoot;
	// 左右子树合并后的新树
    mRoot = merge(l, r); 
}

/* 
 * 销毁斜堆
 */
template <class T>
void SkewHeap<T>::destroy(SkewNode<T>* &heap)
{
	if (heap==NULL)
		return ;

	if (heap->left != NULL)
		destroy(heap->left);
	if (heap->right != NULL)
		destroy(heap->right);

	delete heap;
}

template <class T>
void SkewHeap<T>::destroy()
{
	destroy(mRoot);
}

/*
 * 打印"斜堆"
 *
 * key        -- 节点的键值 
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
template <class T>
void SkewHeap<T>::print(SkewNode<T>* heap, T key, int direction)
{
	if(heap != NULL)
	{
		if(direction==0)	// heap是根节点
			cout << setw(2) << heap->key << " is root" << endl;
		else				// heap是分支节点
			cout << setw(2) << heap->key << " is " << setw(2) << key << "'s "  << setw(12) << (direction==1?"right child" : "left child") << endl;

		print(heap->left, heap->key, -1);
		print(heap->right,heap->key,  1);
	}
}

template <class T>
void SkewHeap<T>::print()
{
	if (mRoot != NULL)
		print(mRoot, mRoot->key, 0);
}
#endif
