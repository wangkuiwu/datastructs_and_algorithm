/**
 * C++: 左倾堆
 *
 * @author skywang
 * @date 2014/03/31
 */

#ifndef _LEFTIST_TREE_HPP_
#define _LEFTIST_TREE_HPP_

#include <iomanip>
#include <iostream>
using namespace std;

template <class T>
class LeftistNode{
	public:
		T key;				// 关键字(键值)
    	int npl;			// 零路经长度(Null Path Length)
		LeftistNode *left;	// 左孩子
		LeftistNode *right;	// 右孩子

		LeftistNode(T value, LeftistNode *l, LeftistNode *r):
			key(value), npl(0), left(l),right(r) {}
};

template <class T>
class LeftistHeap {
	private:
		LeftistNode<T> *mRoot;	// 根结点

    public:
		LeftistHeap();
		~LeftistHeap();

		// 前序遍历"左倾堆"
		void preOrder();
		// 中序遍历"左倾堆"
		void inOrder();
		// 后序遍历"左倾堆"
		void postOrder();

 		// 将other的左倾堆合并到this中。
		void merge(LeftistHeap<T>* other);
		// 将结点(key为节点键值)插入到左倾堆中
		void insert(T key);
		// 删除结点(key为节点键值)
		void remove();

		// 销毁左倾堆
		void destroy();

		// 打印左倾堆
		void print();
	private:

		// 前序遍历"左倾堆"
		void preOrder(LeftistNode<T>* heap) const;
		// 中序遍历"左倾堆"
		void inOrder(LeftistNode<T>* heap) const;
		// 后序遍历"左倾堆"
		void postOrder(LeftistNode<T>* heap) const;

		// 交换节点x和节点y
		void swapNode(LeftistNode<T> *&x, LeftistNode<T> *&y);
        // 合并"左倾堆x"和"左倾堆y"
		LeftistNode<T>* merge(LeftistNode<T>* &x, LeftistNode<T>* &y);
		// 将结点(z)插入到左倾堆(heap)中
		LeftistNode<T>* insert(LeftistNode<T>* &heap, T key);
		// 删除左倾堆(heap)中的结点(z)，并返回被删除的结点
		LeftistNode<T>* remove(LeftistNode<T>* &heap);

		// 销毁左倾堆
		void destroy(LeftistNode<T>* &heap);

		// 打印左倾堆
		void print(LeftistNode<T>* heap, T key, int direction);
};

/* 
 * 构造函数
 */
template <class T>
LeftistHeap<T>::LeftistHeap():mRoot(NULL)
{
}

/* 
 * 析构函数
 */
template <class T>
LeftistHeap<T>::~LeftistHeap() 
{
	destroy(mRoot);
}

/*
 * 前序遍历"左倾堆"
 */
template <class T>
void LeftistHeap<T>::preOrder(LeftistNode<T>* heap) const
{
	if(heap != NULL)
	{
		cout<< heap->key << " " ;
		preOrder(heap->left);
		preOrder(heap->right);
	}
}

template <class T>
void LeftistHeap<T>::preOrder() 
{
	preOrder(mRoot);
}

/*
 * 中序遍历"左倾堆"
 */
template <class T>
void LeftistHeap<T>::inOrder(LeftistNode<T>* heap) const
{
	if(heap != NULL)
	{
		inOrder(heap->left);
		cout<< heap->key << " " ;
		inOrder(heap->right);
	}
}

template <class T>
void LeftistHeap<T>::inOrder() 
{
	inOrder(mRoot);
}

/*
 * 后序遍历"左倾堆"
 */
template <class T>
void LeftistHeap<T>::postOrder(LeftistNode<T>* heap) const
{
	if(heap != NULL)
	{
		postOrder(heap->left);
		postOrder(heap->right);
		cout<< heap->key << " " ;
	}
}

template <class T>
void LeftistHeap<T>::postOrder() 
{
	postOrder(mRoot);
}

/*
 * 交换两个节点的内容
 */
template <class T>
void LeftistHeap<T>::swapNode(LeftistNode<T> *&x, LeftistNode<T> *&y)
{
	LeftistNode<T> *tmp = x;
	x = y;
	y = tmp;
}


/*
 * 合并"左倾堆x"和"左倾堆y"
 */
template <class T>
LeftistNode<T>* LeftistHeap<T>::merge(LeftistNode<T>* &x, LeftistNode<T>* &y)
{
	if(x == NULL)
		return y;
	if(y == NULL)
		return x;

	// 合并x和y时，将x作为合并后的树的根；
	// 这里的操作是保证: x的key < y的key
	if(x->key > y->key)
		swapNode(x, y);

	// 将x的右孩子和y合并，"合并后的树的根"是x的右孩子。
	x->right = merge(x->right, y);

	// 如果"x的左孩子为空" 或者 "x的左孩子的npl<右孩子的npl"
	// 则，交换x和y
	if(x->left == NULL || x->left->npl < x->right->npl)
	{
		LeftistNode<T> *tmp = x->left;
		x->left = x->right;
		x->right = tmp;
	}
	// 设置合并后的新树(x)的npl
	if (x->right == NULL || x->left == NULL)
		x->npl = 0;
	else
		x->npl = (x->left->npl > x->right->npl) ? (x->right->npl + 1) : (x->left->npl + 1);

	return x;
}

/*
 * 将other的左倾堆合并到this中。
 */
template <class T>
void LeftistHeap<T>::merge(LeftistHeap<T>* other)
{
	mRoot = merge(mRoot, other->mRoot);
}

/* 
 * 将结点插入到左倾堆中，并返回根节点
 *
 * 参数说明：
 *     heap 左倾堆的根结点
 *     key 插入的结点的键值
 * 返回值：
 *     根节点
 */
template <class T>
LeftistNode<T>* LeftistHeap<T>::insert(LeftistNode<T>* &heap, T key)
{
	LeftistNode<T> *node;	// 新建结点

	// 新建节点
	node = new LeftistNode<T>(key, NULL, NULL);
	if (node==NULL)
	{
		cout << "ERROR: create node failed!" << endl;
		return heap;
	}

	return merge(mRoot, node);
}

template <class T>
void LeftistHeap<T>::insert(T key)
{
	mRoot = insert(mRoot, key);
}

/* 
 * 删除结点，返回根节点
 *
 * 参数说明：
 *     heap 左倾堆的根结点
 * 返回值：
 *     根节点
 */
template <class T>
LeftistNode<T>* LeftistHeap<T>::remove(LeftistNode<T>* &heap)
{
    if (heap == NULL)
        return NULL;

    LeftistNode<T> *l = heap->left;
    LeftistNode<T> *r = heap->right;

	// 删除根节点
	delete heap;

    return merge(l, r); // 返回左右子树合并后的新树
}

template <class T>
void LeftistHeap<T>::remove()
{
	mRoot = remove(mRoot);
}

/* 
 * 销毁左倾堆
 */
template <class T>
void LeftistHeap<T>::destroy(LeftistNode<T>* &heap)
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
void LeftistHeap<T>::destroy()
{
	destroy(mRoot);
}

/*
 * 打印"二叉查找树"
 *
 * key        -- 节点的键值 
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
template <class T>
void LeftistHeap<T>::print(LeftistNode<T>* heap, T key, int direction)
{
	if(heap != NULL)
	{
		if(direction==0)	// heap是根节点
			cout << setw(2) << heap->key << "(" << heap->npl << ") is root" << endl;
		else				// heap是分支节点
			cout << setw(2) << heap->key << "(" << heap->npl << ") is " << setw(2) << key << "'s "  << setw(12) << (direction==1?"right child" : "left child") << endl;

		print(heap->left, heap->key, -1);
		print(heap->right,heap->key,  1);
	}
}

template <class T>
void LeftistHeap<T>::print()
{
	if (mRoot != NULL)
		print(mRoot, mRoot->key, 0);
}
#endif
