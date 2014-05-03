
/**
 * Java 语言: 伸展树
 *
 * @author skywang
 * @date 2014/02/03
 */
public class SplayTreeTest {

	private static final int arr[] = {10,50,40,30,20,60};

	public static void main(String[] args) {
		int i, ilen;
		SplayTree<Integer> tree=new SplayTree<Integer>();

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

		i = 30;
		System.out.printf("\n== 旋转节点(%d)为根节点\n", i);
		tree.splay(i);
		System.out.printf("== 树的详细信息: \n");
		tree.print();

		// 销毁二叉树
		tree.clear();
	}
}
