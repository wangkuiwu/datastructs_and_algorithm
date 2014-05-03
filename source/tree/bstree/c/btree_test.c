/**
 * C 语言: 二叉查找树
 *
 * @author skywang
 * @date 2013/11/07
 */

#include <stdio.h>
#include "bstree.h"

static int arr[]= {1,5,4,3,2,6};
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

void main()
{
	int i, ilen;
	BSTree root=NULL;

	printf("== 依次添加: ");
	ilen = TBL_SIZE(arr);
	for(i=0; i<ilen; i++)
	{
		printf("%d ", arr[i]);
		root = insert_bstree(root, arr[i]);
	}

	printf("\n== 前序遍历: ");
	preorder_bstree(root);

	printf("\n== 中序遍历: ");
	inorder_bstree(root);

	printf("\n== 后序遍历: ");
	postorder_bstree(root);
	printf("\n");

	printf("== 最小值: %d\n", bstree_minimum(root)->key);
	printf("== 最大值: %d\n", bstree_maximum(root)->key);
	printf("== 树的详细信息: \n");
	print_bstree(root, root->key, 0);

	printf("\n== 删除根节点: %d", arr[3]);
	root = delete_bstree(root, arr[3]);

	printf("\n== 中序遍历: ");
	inorder_bstree(root);
	printf("\n");

	// 销毁二叉树
	destroy_bstree(root);
}
