/**
 * C 语言: Huffman树
 *
 * @author skywang
 * @date 2014/03/25
 */
#include <stdio.h>
#include "huffman.h"

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

void main()
{
	int a[]= {5,6,8,7,15};
	int i,ilen=LENGTH(a);
	HuffmanTree root=NULL;

	printf("== 添加数组: ");
	for(i=0; i<ilen; i++)
		printf("%d ", a[i]);

	// 创建数组a对应的Huffman树
	root = create_huffman(a, ilen);

	printf("\n== 前序遍历: ");
	preorder_huffman(root);

	printf("\n== 中序遍历: ");
	inorder_huffman(root);

	printf("\n== 后序遍历: ");
	postorder_huffman(root);
	printf("\n");

	printf("== 树的详细信息: \n");
	print_huffman(root);

	// 销毁二叉树
	destroy_huffman(root);
}
