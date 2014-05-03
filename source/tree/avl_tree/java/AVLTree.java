/**
 * Java 语言: AVL树
 *
 * @author skywang
 * @date 2013/11/07
 */

public class AVLTree<T extends Comparable<T>> {
	private AVLTreeNode<T> mRoot;	// 根结点

	// AVL树的节点(内部类)
	class AVLTreeNode<T extends Comparable<T>> {
		T key;				// 关键字(键值)
		int height;     	// 高度
		AVLTreeNode<T> left;	// 左孩子
		AVLTreeNode<T> right;	// 右孩子

		public AVLTreeNode(T key, AVLTreeNode<T> left, AVLTreeNode<T> right) {
			this.key = key;
			this.left = left;
			this.right = right;
			this.height = 0;
		}
	}

	// 构造函数
	public AVLTree() {
		mRoot = null;
	}

	/*
	 * 获取树的高度
	 */
	private int height(AVLTreeNode<T> tree) {
		if (tree != null)
			return tree.height;

		return 0;
	}

	public int height() {
		return height(mRoot);
	}

	/*
	 * 比较两个值的大小
	 */
	private int max(int a, int b) {
		return a>b ? a : b;
	}

	/*
	 * 前序遍历"AVL树"
	 */
	private void preOrder(AVLTreeNode<T> tree) {
		if(tree != null) {
			System.out.print(tree.key+" ");
			preOrder(tree.left);
			preOrder(tree.right);
		}
	}

	public void preOrder() {
		preOrder(mRoot);
	}

	/*
	 * 中序遍历"AVL树"
	 */
	private void inOrder(AVLTreeNode<T> tree) {
		if(tree != null)
		{
			inOrder(tree.left);
			System.out.print(tree.key+" ");
			inOrder(tree.right);
		}
	}

	public void inOrder() {
		inOrder(mRoot);
	}

	/*
	 * 后序遍历"AVL树"
	 */
	private void postOrder(AVLTreeNode<T> tree) {
		if(tree != null) {
			postOrder(tree.left);
			postOrder(tree.right);
			System.out.print(tree.key+" ");
		}
	}

	public void postOrder() {
		postOrder(mRoot);
	}

	/*
	 * (递归实现)查找"AVL树x"中键值为key的节点
	 */
	private AVLTreeNode<T> search(AVLTreeNode<T> x, T key) {
		if (x==null)
			return x;

		int cmp = key.compareTo(x.key);
		if (cmp < 0)
			return search(x.left, key);
		else if (cmp > 0)
			return search(x.right, key);
		else
			return x;
	}

	public AVLTreeNode<T> search(T key) {
		return search(mRoot, key);
	}

	/*
	 * (非递归实现)查找"AVL树x"中键值为key的节点
	 */
	private AVLTreeNode<T> iterativeSearch(AVLTreeNode<T> x, T key) {
		while (x!=null) {
			int cmp = key.compareTo(x.key);

			if (cmp < 0)
				x = x.left;
			else if (cmp > 0)
				x = x.right;
			else
				return x;
		}

		return x;
	}

	public AVLTreeNode<T> iterativeSearch(T key) {
		return iterativeSearch(mRoot, key);
	}

	/* 
	 * 查找最小结点：返回tree为根结点的AVL树的最小结点。
	 */
	private AVLTreeNode<T> minimum(AVLTreeNode<T> tree) {
		if (tree == null)
			return null;

		while(tree.left != null)
			tree = tree.left;
		return tree;
	}

	public T minimum() {
		AVLTreeNode<T> p = minimum(mRoot);
		if (p != null)
			return p.key;

		return null;
	}
	 
	/* 
	 * 查找最大结点：返回tree为根结点的AVL树的最大结点。
	 */
	private AVLTreeNode<T> maximum(AVLTreeNode<T> tree) {
		if (tree == null)
			return null;

		while(tree.right != null)
			tree = tree.right;
		return tree;
	}

	public T maximum() {
		AVLTreeNode<T> p = maximum(mRoot);
		if (p != null)
			return p.key;

		return null;
	}

	/*
	 * LL：左左对应的情况(左单旋转)。
	 *
	 * 返回值：旋转后的根节点
	 */
	private AVLTreeNode<T> leftLeftRotation(AVLTreeNode<T> k2) {
		AVLTreeNode<T> k1;

		k1 = k2.left;
		k2.left = k1.right;
		k1.right = k2;

		k2.height = max( height(k2.left), height(k2.right)) + 1;
		k1.height = max( height(k1.left), k2.height) + 1;

		return k1;
	}

	/*
	 * RR：右右对应的情况(右单旋转)。
	 *
	 * 返回值：旋转后的根节点
	 */
	private AVLTreeNode<T> rightRightRotation(AVLTreeNode<T> k1) {
		AVLTreeNode<T> k2;

		k2 = k1.right;
		k1.right = k2.left;
		k2.left = k1;

		k1.height = max( height(k1.left), height(k1.right)) + 1;
		k2.height = max( height(k2.right), k1.height) + 1;

		return k2;
	}

	/*
	 * LR：左右对应的情况(左双旋转)。
	 *
	 * 返回值：旋转后的根节点
	 */
	private AVLTreeNode<T> leftRightRotation(AVLTreeNode<T> k3) {
		k3.left = rightRightRotation(k3.left);

		return leftLeftRotation(k3);
	}

	/*
	 * RL：右左对应的情况(右双旋转)。
	 *
	 * 返回值：旋转后的根节点
	 */
	private AVLTreeNode<T> rightLeftRotation(AVLTreeNode<T> k1) {
		k1.right = leftLeftRotation(k1.right);

		return rightRightRotation(k1);
	}

	/* 
	 * 将结点插入到AVL树中，并返回根节点
	 *
	 * 参数说明：
	 *     tree AVL树的根结点
	 *     key 插入的结点的键值
	 * 返回值：
	 *     根节点
	 */
	private AVLTreeNode<T> insert(AVLTreeNode<T> tree, T key) {
		if (tree == null) {
			// 新建节点
			tree = new AVLTreeNode<T>(key, null, null);
			if (tree==null) {
				System.out.println("ERROR: create avltree node failed!");
				return null;
			}
		} else {
			int cmp = key.compareTo(tree.key);

		   	if (cmp < 0) {	// 应该将key插入到"tree的左子树"的情况
				tree.left = insert(tree.left, key);
				// 插入节点后，若AVL树失去平衡，则进行相应的调节。
				if (height(tree.left) - height(tree.right) == 2) {
					if (key.compareTo(tree.left.key) < 0)
						tree = leftLeftRotation(tree);
					else
						tree = leftRightRotation(tree);
				}
			} else if (cmp > 0) {	// 应该将key插入到"tree的右子树"的情况
				tree.right = insert(tree.right, key);
				// 插入节点后，若AVL树失去平衡，则进行相应的调节。
				if (height(tree.right) - height(tree.left) == 2) {
					if (key.compareTo(tree.right.key) > 0)
						tree = rightRightRotation(tree);
					else
						tree = rightLeftRotation(tree);
				}
			} else {	// cmp==0
				System.out.println("添加失败：不允许添加相同的节点！");
			}
		}

		tree.height = max( height(tree.left), height(tree.right)) + 1;

		return tree;
	}

	public void insert(T key) {
		mRoot = insert(mRoot, key);
	}

	/* 
	 * 删除结点(z)，返回根节点
	 *
	 * 参数说明：
	 *     tree AVL树的根结点
	 *     z 待删除的结点
	 * 返回值：
	 *     根节点
	 */
	private AVLTreeNode<T> remove(AVLTreeNode<T> tree, AVLTreeNode<T> z) {
		// 根为空 或者 没有要删除的节点，直接返回null。
		if (tree==null || z==null)
			return null;

		int cmp = z.key.compareTo(tree.key);
		if (cmp < 0) {		// 待删除的节点在"tree的左子树"中
			tree.left = remove(tree.left, z);
			// 删除节点后，若AVL树失去平衡，则进行相应的调节。
			if (height(tree.right) - height(tree.left) == 2) {
				AVLTreeNode<T> r =  tree.right;
				if (height(r.left) > height(r.right))
					tree = rightLeftRotation(tree);
				else
					tree = rightRightRotation(tree);
			}
		} else if (cmp > 0) {	// 待删除的节点在"tree的右子树"中
			tree.right = remove(tree.right, z);
			// 删除节点后，若AVL树失去平衡，则进行相应的调节。
			if (height(tree.left) - height(tree.right) == 2) {
				AVLTreeNode<T> l =  tree.left;
				if (height(l.right) > height(l.left))
					tree = leftRightRotation(tree);
				else
					tree = leftLeftRotation(tree);
			}
		} else {	// tree是对应要删除的节点。
			// tree的左右孩子都非空
			if ((tree.left!=null) && (tree.right!=null)) {
				if (height(tree.left) > height(tree.right)) {
					// 如果tree的左子树比右子树高；
					// 则(01)找出tree的左子树中的最大节点
					//   (02)将该最大节点的值赋值给tree。
					//   (03)删除该最大节点。
					// 这类似于用"tree的左子树中最大节点"做"tree"的替身；
					// 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
					AVLTreeNode<T> max = maximum(tree.left);
					tree.key = max.key;
					tree.left = remove(tree.left, max);
				} else {
					// 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
					// 则(01)找出tree的右子树中的最小节点
					//   (02)将该最小节点的值赋值给tree。
					//   (03)删除该最小节点。
					// 这类似于用"tree的右子树中最小节点"做"tree"的替身；
					// 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
					AVLTreeNode<T> min = maximum(tree.right);
					tree.key = min.key;
					tree.right = remove(tree.right, min);
				}
			} else {
				AVLTreeNode<T> tmp = tree;
				tree = (tree.left!=null) ? tree.left : tree.right;
				tmp = null;
			}
		}

		return tree;
	}

	public void remove(T key) {
		AVLTreeNode<T> z; 

		if ((z = search(mRoot, key)) != null)
			mRoot = remove(mRoot, z);
	}

	/* 
	 * 销毁AVL树
	 */
	private void destroy(AVLTreeNode<T> tree) {
		if (tree==null)
			return ;

		if (tree.left != null)
			destroy(tree.left);
		if (tree.right != null)
			destroy(tree.right);

		tree = null;
	}

	public void destroy() {
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
	private void print(AVLTreeNode<T> tree, T key, int direction) {
		if(tree != null) {
			if(direction==0)	// tree是根节点
				System.out.printf("%2d is root\n", tree.key, key);
			else				// tree是分支节点
				System.out.printf("%2d is %2d's %6s child\n", tree.key, key, direction==1?"right" : "left");

			print(tree.left, tree.key, -1);
			print(tree.right,tree.key,  1);
		}
	}

	public void print() {
		if (mRoot != null)
			print(mRoot, mRoot.key, 0);
	}
}
