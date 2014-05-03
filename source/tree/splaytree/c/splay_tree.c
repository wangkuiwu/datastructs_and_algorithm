/**
 * SplayTree伸展树(C语言): C语言实现的伸展树。
 *
 * @author skywang
 * @date 2014/02/03
 */

#include <stdio.h>
#include <stdlib.h>
#include "splay_tree.h"

/*
 * 前序遍历"伸展树"
 */
void preorder_splaytree(SplayTree tree)
{
	if(tree != NULL)
	{
		printf("%d ", tree->key);
		preorder_splaytree(tree->left);
		preorder_splaytree(tree->right);
	}
}

/*
 * 中序遍历"伸展树"
 */
void inorder_splaytree(SplayTree tree)
{
	if(tree != NULL)
	{
		inorder_splaytree(tree->left);
		printf("%d ", tree->key);
		inorder_splaytree(tree->right);
	}
}

/*
 * 后序遍历"伸展树"
 */
void postorder_splaytree(SplayTree tree)
{
	if(tree != NULL)
	{
		postorder_splaytree(tree->left);
		postorder_splaytree(tree->right);
		printf("%d ", tree->key);
	}
}

/*
 * (递归实现)查找"伸展树x"中键值为key的节点
 */
Node* splaytree_search(SplayTree x, Type key)
{
	if (x==NULL || x->key==key)
		return x;

	if (key < x->key)
		return splaytree_search(x->left, key);
	else
		return splaytree_search(x->right, key);
}

/*
 * (非递归实现)查找"伸展树x"中键值为key的节点
 */
Node* iterative_splaytree_search(SplayTree x, Type key)
{
	while ((x!=NULL) && (x->key!=key))
	{
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	return x;
}

/* 
 * 查找最小结点：返回tree为根结点的伸展树的最小结点。
 */
Node* splaytree_minimum(SplayTree tree)
{
	if (tree == NULL)
		return NULL;

	while(tree->left != NULL)
		tree = tree->left;
	return tree;
}
 
/* 
 * 查找最大结点：返回tree为根结点的伸展树的最大结点。
 */
Node* splaytree_maximum(SplayTree tree)
{
	if (tree == NULL)
		return NULL;

	while(tree->right != NULL)
		tree = tree->right;
	return tree;
}

/* 
 * 旋转key对应的节点为根节点，并返回根节点。
 *
 * 注意：
 *   (a)：伸展树中存在"键值为key的节点"。
 *          将"键值为key的节点"旋转为根节点。
 *   (b)：伸展树中不存在"键值为key的节点"，并且key < tree->key。
 *      b-1 "键值为key的节点"的前驱节点存在的话，将"键值为key的节点"的前驱节点旋转为根节点。
 *      b-2 "键值为key的节点"的前驱节点存在的话，则意味着，key比树中任何键值都小，那么此时，将最小节点旋转为根节点。
 *   (c)：伸展树中不存在"键值为key的节点"，并且key > tree->key。
 *      c-1 "键值为key的节点"的后继节点存在的话，将"键值为key的节点"的后继节点旋转为根节点。
 *      c-2 "键值为key的节点"的后继节点不存在的话，则意味着，key比树中任何键值都大，那么此时，将最大节点旋转为根节点。
 */
Node* splaytree_splay(SplayTree tree, Type key)
{
    Node N, *l, *r, *c;

    if (tree == NULL) 
        return tree;

    N.left = N.right = NULL;
    l = r = &N;

    for (;;)
    {
        if (key < tree->key)
        {
            if (tree->left == NULL)
                break;
            if (key < tree->left->key)
            {
                c = tree->left;                           /* 01, rotate right */
                tree->left = c->right;
                c->right = tree;
                tree = c;
                if (tree->left == NULL) 
                    break;
            }
            r->left = tree;                               /* 02, link right */
            r = tree;
            tree = tree->left;
        }
		else if (key > tree->key)
        {
            if (tree->right == NULL) 
                break;
            if (key > tree->right->key) 
            {
                c = tree->right;                          /* 03, rotate left */
                tree->right = c->left;
                c->left = tree;
                tree = c;
                if (tree->right == NULL) 
                    break;
            }
            l->right = tree;                              /* 04, link left */
            l = tree;
            tree = tree->right;
        }
		else
		{
            break;
        }
    }

    l->right = tree->left;                                /* 05, assemble */
    r->left = tree->right;
    tree->left = N.right;
    tree->right = N.left;

    return tree;
}

/* 
 * 将结点插入到伸展树中(不旋转)
 *
 * 参数说明：
 *     tree 伸展树的根结点
 *     z 插入的结点
 * 返回值：
 *     根节点
 */
static Node* splaytree_insert(SplayTree tree, Node *z)
{
	Node *y = NULL;
	Node *x = tree;

	// 查找z的插入位置
	while (x != NULL)
	{
		y = x;
		if (z->key < x->key)
			x = x->left;
		else if (z->key > x->key)
			x = x->right;
		else
		{
			printf("不允许插入相同节点(%d)!\n", z->key);
			// 释放申请的节点，并返回tree。
			free(z);
			return tree;
		}
	}

	if (y==NULL)
		tree = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;

	return tree;
}

/*
 * 创建并返回伸展树结点。
 *
 * 参数说明：
 *     key 是键值。
 *     parent 是父结点。
 *     left 是左孩子。
 *     right 是右孩子。
 */
static Node* create_splaytree_node(Type key, Node *left, Node* right)
{
	Node* p;

	if ((p = (Node *)malloc(sizeof(Node))) == NULL)
		return NULL;
	p->key = key;
	p->left = left;
	p->right = right;

	return p;
}

/* 
 * 新建结点(key)，然后将其插入到伸展树中，并将插入节点旋转为根节点
 *
 * 参数说明：
 *     tree 伸展树的根结点
 *     key 插入结点的键值
 * 返回值：
 *     根节点
 */
Node* insert_splaytree(SplayTree tree, Type key)
{
	Node *z;	// 新建结点

	// 如果新建结点失败，则返回。
	if ((z=create_splaytree_node(key, NULL, NULL)) == NULL)
		return tree;

	// 插入节点
	tree = splaytree_insert(tree, z);
	// 将节点(key)旋转为根节点
	tree = splaytree_splay(tree, key);
}

/* 
 * 删除结点(key为节点的键值)，并返回根节点。
 *
 * 参数说明：
 *     tree 伸展树的根结点
 *     z 删除的结点
 * 返回值：
 *     根节点(根节点是被删除节点的前驱节点)
 *
 */
Node* delete_splaytree(SplayTree tree, Type key)
{
    Node *x;

    if (tree == NULL) 
        return NULL;

	// 查找键值为key的节点，找不到的话直接返回。
	if (splaytree_search(tree, key) == NULL)
		return tree;

	// 将key对应的节点旋转为根节点。
    tree = splaytree_splay(tree, key);

	if (tree->left != NULL)
	{
		// 将"tree的前驱节点"旋转为根节点
		x = splaytree_splay(tree->left, key);
		// 移除tree节点
		x->right = tree->right;
	}
	else
		x = tree->right;

	free(tree);

	return x;
}

/*
 * 销毁伸展树
 */
void destroy_splaytree(SplayTree tree)
{
	if (tree==NULL)
		return ;

	if (tree->left != NULL)
		destroy_splaytree(tree->left);
	if (tree->right != NULL)
		destroy_splaytree(tree->right);

	free(tree);
}

/*
 * 打印"伸展树"
 *
 * tree       -- 伸展树的节点
 * key        -- 节点的键值 
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
void print_splaytree(SplayTree tree, Type key, int direction)
{
	if(tree != NULL)
	{
		if(direction==0)	// tree是根节点
			printf("%2d is root\n", tree->key);
		else				// tree是分支节点
			printf("%2d is %2d's %6s child\n", tree->key, key, direction==1?"right" : "left");

		print_splaytree(tree->left, tree->key, -1);
		print_splaytree(tree->right,tree->key,  1);
	}
}
