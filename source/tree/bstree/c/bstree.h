
#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

typedef int Type;

typedef struct BSTreeNode{
	Type   key;					// 关键字(键值)
	struct BSTreeNode *left;	// 左孩子
	struct BSTreeNode *right;	// 右孩子
	struct BSTreeNode *parent;	// 父结点
}Node, *BSTree;

// 前序遍历"二叉树"
void preorder_bstree(BSTree tree);
// 中序遍历"二叉树"
void inorder_bstree(BSTree tree);
// 后序遍历"二叉树"
void postorder_bstree(BSTree tree);

// (递归实现)查找"二叉树x"中键值为key的节点
Node* bstree_search(BSTree x, Type key);
// (非递归实现)查找"二叉树x"中键值为key的节点
Node* iterative_bstree_search(BSTree x, Type key);

// 查找最小结点：返回tree为根结点的二叉树的最小结点。
Node* bstree_minimum(BSTree tree);
// 查找最大结点：返回tree为根结点的二叉树的最大结点。
Node* bstree_maximum(BSTree tree);

// 找结点(x)的后继结点。即，查找"二叉树中数据值大于该结点"的"最小结点"。
Node* bstree_successor(Node *x);
// 找结点(x)的前驱结点。即，查找"二叉树中数据值小于该结点"的"最大结点"。
Node* bstree_predecessor(Node *x);

// 将结点插入到二叉树中，并返回根节点
Node* insert_bstree(BSTree tree, Type key);

// 删除结点(key为节点的值)，并返回根节点
Node* delete_bstree(BSTree tree, Type key);

// 销毁二叉树
void destroy_bstree(BSTree tree);

// 打印二叉树
void print_bstree(BSTree tree, Type key, int direction);

#endif
