#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

typedef int Type;

typedef struct _HuffmanNode{
	Type key;					// 权值
	struct _HuffmanNode *left;	// 左孩子
	struct _HuffmanNode *right;	// 右孩子
	struct _HuffmanNode *parent;	// 父节点
}HuffmanNode, *HuffmanTree;

// 前序遍历"Huffman树"
void preorder_huffman(HuffmanTree tree);
// 中序遍历"Huffman树"
void inorder_huffman(HuffmanTree tree);
// 后序遍历"Huffman树"
void postorder_huffman(HuffmanTree tree);

// 创建Huffman树
HuffmanNode* create_huffman(Type arr[], int size);

// 销毁Huffman树
void destroy_huffman(HuffmanTree tree);

// 打印Huffman树
void print_huffman(HuffmanTree tree);

#endif
