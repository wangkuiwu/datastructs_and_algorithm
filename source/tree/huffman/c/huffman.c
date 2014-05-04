/**
 * Huffman树(C语言): C语言实现的Huffman树。
 *
 * 构造Huffman树时，使用到了最小堆。
 *
 * @author skywang
 * @date 2014/03/25
 */

#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

// 创建最小堆
extern void create_minheap(Type a[], int size);
// 新建一个节点，并将最小堆中最小节点的数据复制给该节点。
extern HuffmanNode* dump_from_minheap();
// 将data插入到二叉堆中。0表示成功，-1表示失败。
extern int dump_to_minheap(HuffmanNode *node);
// 销毁最小堆
extern void destroy_minheap();

/*
 * 前序遍历"Huffman树"
 */
void preorder_huffman(HuffmanTree tree)
{
    if(tree != NULL)
    {
        printf("%d ", tree->key);
        preorder_huffman(tree->left);
        preorder_huffman(tree->right);
    }
}


/*
 * 中序遍历"Huffman树"
 */
void inorder_huffman(HuffmanTree tree)
{
    if(tree != NULL)
    {
        inorder_huffman(tree->left);
        printf("%d ", tree->key);
        inorder_huffman(tree->right);
    }
}

/*
 * 后序遍历"Huffman树"
 */
void postorder_huffman(HuffmanTree tree)
{
    if(tree != NULL)
    {
        postorder_huffman(tree->left);
        postorder_huffman(tree->right);
        printf("%d ", tree->key);
    }
}

/*
 * 创建Huffman树结点。
 *
 * 参数说明：
 *     key 是键值。
 *     left 是左孩子。
 *     right 是右孩子。
 *     parent 是父节点
 */
HuffmanNode* huffman_create_node(Type key, HuffmanNode *left, HuffmanNode* right, HuffmanNode* parent)
{
    HuffmanNode* p;

    if ((p = (HuffmanNode *)malloc(sizeof(HuffmanNode))) == NULL)
        return NULL;
    p->key = key;
    p->left = left;
    p->right = right;
    p->parent = parent;

    return p;
}

/*
 * 创建Huffman树
 *
 * 参数说明：
 *     a 权值数组
 *     size 数组大小
 *
 * 返回值：
 *     Huffman树的根
 */
HuffmanNode* create_huffman(Type a[], int size)
{
    int i;
    HuffmanNode *left, *right, *parent;

	// 建立数组a对应的最小堆
    create_minheap(a, size);
 
    for(i=0; i<size-1; i++)
    {   
        left = dump_from_minheap();  // 最小节点是左孩子
        right = dump_from_minheap(); // 其次才是右孩子
 
		// 新建parent节点，左右孩子分别是left/right；
		// parent的大小是左右孩子之和
        parent = huffman_create_node(left->key+right->key, left, right, NULL);
        left->parent = parent;
		right->parent = parent;
 

		// 将parent节点数据拷贝到"最小堆"中
		if (dump_to_minheap(parent)!=0)
		{
			printf("插入失败!\n结束程序\n");
			destroy_huffman(parent);
			parent = NULL;
			break;
		}
    }   

	// 销毁最小堆
	destroy_minheap();

	return parent;
}

/* 
 * 销毁Huffman树
 */
void destroy_huffman(HuffmanTree tree)
{
    if (tree==NULL)
        return ;

    if (tree->left != NULL)
        destroy_huffman(tree->left);
    if (tree->right != NULL)
        destroy_huffman(tree->right);

    free(tree);
}

/*
 * 打印"Huffman树"
 *
 * tree       -- Huffman树的节点
 * key        -- 节点的键值 
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
void huffman_print(HuffmanTree tree, Type key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    // tree是根节点
            printf("%2d is root\n", tree->key, key);
        else                // tree是分支节点
            printf("%2d is %2d's %6s child\n", tree->key, key, direction==1?"right" : "left");

        huffman_print(tree->left, tree->key, -1);
        huffman_print(tree->right,tree->key,  1);
    }
}

void print_huffman(HuffmanTree tree)
{
	if (tree!=NULL)
		huffman_print(tree, tree->key, 0);
}
