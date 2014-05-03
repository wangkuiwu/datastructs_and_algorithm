
/**
 * Java 语言: 二叉查找树
 *
 * @author skywang
 * @date 2013/11/07
 */
public class RBTreeTest {

	private static final int a[] = {10, 40, 30, 60, 90, 70, 20, 50, 80};
	private static final boolean mDebugInsert = false;	// "插入"动作的检测开关(false，关闭；true，打开)
	private static final boolean mDebugDelete = false;	// "删除"动作的检测开关(false，关闭；true，打开)

	public static void main(String[] args) {
		int i, ilen = a.length;
		RBTree<Integer> tree=new RBTree<Integer>();

		System.out.printf("== 原始数据: ");
		for(i=0; i<ilen; i++)
			System.out.printf("%d ", a[i]);
		System.out.printf("\n");

		for(i=0; i<ilen; i++) {
			tree.insert(a[i]);
			// 设置mDebugInsert=true,测试"添加函数"
			if (mDebugInsert) {
				System.out.printf("== 添加节点: %d\n", a[i]);
				System.out.printf("== 树的详细信息: \n");
				tree.print();
				System.out.printf("\n");
			}
		}

		System.out.printf("== 前序遍历: ");
		tree.preOrder();

		System.out.printf("\n== 中序遍历: ");
		tree.inOrder();

		System.out.printf("\n== 后序遍历: ");
		tree.postOrder();
		System.out.printf("\n");

		System.out.printf("== 最小值: %s\n", tree.minimum());
		System.out.printf("== 最大值: %s\n", tree.maximum());
		System.out.printf("== 树的详细信息: \n");
		tree.print();
		System.out.printf("\n");

		// 设置mDebugDelete=true,测试"删除函数"
		if (mDebugDelete) {
			for(i=0; i<ilen; i++)
			{
				tree.remove(a[i]);

				System.out.printf("== 删除节点: %d\n", a[i]);
				System.out.printf("== 树的详细信息: \n");
				tree.print();
				System.out.printf("\n");
			}
		}

		// 销毁二叉树
		tree.clear();
	}
}
