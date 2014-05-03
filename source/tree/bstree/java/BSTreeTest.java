
/**
 * Java 语言: 二叉查找树
 *
 * @author skywang
 * @date 2013/11/07
 */
public class BSTreeTest {

	private static final int arr[] = {1,5,4,3,2,6};

	public static void main(String[] args) {
		int i, ilen;
		BSTree<Integer> tree=new BSTree<Integer>();

		System.out.print("== 依次添加: ");
		ilen = arr.length;
		for(i=0; i<ilen; i++) {
			System.out.print(arr[i]+" ");
			tree.insert(arr[i]);
		}

		System.out.print("\n== 前序遍历: ");
		tree.preOrder();

		System.out.print("\n== 中序遍历: ");
		tree.inOrder();

		System.out.print("\n== 后序遍历: ");
		tree.postOrder();
		System.out.println();

		System.out.println("== 最小值: "+ tree.minimum());
		System.out.println("== 最大值: "+ tree.maximum());
		System.out.println("== 树的详细信息: ");
		tree.print();

		System.out.print("\n== 删除根节点: "+ arr[3]);
		tree.remove(arr[3]);

		System.out.print("\n== 中序遍历: ");
		tree.inOrder();
		System.out.println();

		// 销毁二叉树
		tree.clear();
	}
}
