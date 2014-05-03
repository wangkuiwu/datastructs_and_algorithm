/**
 * Java 语言: 伸展树
 *
 * @author skywang
 * @date 2014/02/03
 */

public class SplayTree<T extends Comparable<T>> {

	private SplayTreeNode<T> mRoot;	// 根结点

	public class SplayTreeNode<T extends Comparable<T>> {
		T key;				// 关键字(键值)
		SplayTreeNode<T> left;	// 左孩子
		SplayTreeNode<T> right;	// 右孩子

		public SplayTreeNode() {
			this.left = null;
			this.right = null;
		}

		public SplayTreeNode(T key, SplayTreeNode<T> left, SplayTreeNode<T> right) {
			this.key = key;
			this.left = left;
			this.right = right;
		}
	}

	public SplayTree() {
		mRoot=null;
	}

	/*
	 * 前序遍历"伸展树"
	 */
	private void preOrder(SplayTreeNode<T> tree) {
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
	 * 中序遍历"伸展树"
	 */
	private void inOrder(SplayTreeNode<T> tree) {
		if(tree != null) {
			inOrder(tree.left);
			System.out.print(tree.key+" ");
			inOrder(tree.right);
		}
	}

	public void inOrder() {
		inOrder(mRoot);
	}


	/*
	 * 后序遍历"伸展树"
	 */
	private void postOrder(SplayTreeNode<T> tree) {
		if(tree != null)
		{
			postOrder(tree.left);
			postOrder(tree.right);
			System.out.print(tree.key+" ");
		}
	}

	public void postOrder() {
		postOrder(mRoot);
	}


	/*
	 * (递归实现)查找"伸展树x"中键值为key的节点
	 */
	private SplayTreeNode<T> search(SplayTreeNode<T> x, T key) {
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

	public SplayTreeNode<T> search(T key) {
		return search(mRoot, key);
	}

	/*
	 * (非递归实现)查找"伸展树x"中键值为key的节点
	 */
	private SplayTreeNode<T> iterativeSearch(SplayTreeNode<T> x, T key) {
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

	public SplayTreeNode<T> iterativeSearch(T key) {
		return iterativeSearch(mRoot, key);
	}

	/* 
	 * 查找最小结点：返回tree为根结点的伸展树的最小结点。
	 */
	private SplayTreeNode<T> minimum(SplayTreeNode<T> tree) {
		if (tree == null)
			return null;

		while(tree.left != null)
			tree = tree.left;
		return tree;
	}

	public T minimum() {
		SplayTreeNode<T> p = minimum(mRoot);
		if (p != null)
			return p.key;

		return null;
	}
	 
	/* 
	 * 查找最大结点：返回tree为根结点的伸展树的最大结点。
	 */
	private SplayTreeNode<T> maximum(SplayTreeNode<T> tree) {
		if (tree == null)
			return null;

		while(tree.right != null)
			tree = tree.right;
		return tree;
	}

	public T maximum() {
		SplayTreeNode<T> p = maximum(mRoot);
		if (p != null)
			return p.key;

		return null;
	}

	/* 
	 * 旋转key对应的节点为根节点，并返回根节点。
	 *
	 * 注意：
	 *   (a)：伸展树中存在"键值为key的节点"。
	 *          将"键值为key的节点"旋转为根节点。
	 *   (b)：伸展树中不存在"键值为key的节点"，并且key < tree.key。
	 *      b-1 "键值为key的节点"的前驱节点存在的话，将"键值为key的节点"的前驱节点旋转为根节点。
	 *      b-2 "键值为key的节点"的前驱节点存在的话，则意味着，key比树中任何键值都小，那么此时，将最小节点旋转为根节点。
	 *   (c)：伸展树中不存在"键值为key的节点"，并且key > tree.key。
	 *      c-1 "键值为key的节点"的后继节点存在的话，将"键值为key的节点"的后继节点旋转为根节点。
	 *      c-2 "键值为key的节点"的后继节点不存在的话，则意味着，key比树中任何键值都大，那么此时，将最大节点旋转为根节点。
	 */
	private SplayTreeNode<T> splay(SplayTreeNode<T> tree, T key) {
		if (tree == null) 
			return tree;

		SplayTreeNode<T> N = new SplayTreeNode<T>();
		SplayTreeNode<T> l = N;
		SplayTreeNode<T> r = N;
		SplayTreeNode<T> c;

		for (;;) {

			int cmp = key.compareTo(tree.key);
			if (cmp < 0) {

				if (tree.left == null)
					break;

				if (key.compareTo(tree.left.key) < 0) {
					c = tree.left;                           /* rotate right */
					tree.left = c.right;
					c.right = tree;
					tree = c;
					if (tree.left == null) 
						break;
				}
				r.left = tree;                               /* link right */
				r = tree;
				tree = tree.left;
			} else if (cmp > 0) {

				if (tree.right == null) 
					break;

				if (key.compareTo(tree.right.key) > 0) {
					c = tree.right;                          /* rotate left */
					tree.right = c.left;
					c.left = tree;
					tree = c;
					if (tree.right == null) 
						break;
				}

				l.right = tree;                              /* link left */
				l = tree;
				tree = tree.right;
			} else {
				break;
			}
		}

		l.right = tree.left;                                /* assemble */
		r.left = tree.right;
		tree.left = N.right;
		tree.right = N.left;

		return tree;
	}

	public void splay(T key) {
		mRoot = splay(mRoot, key);
	}

	/* 
     * 将结点插入到伸展树中，并返回根节点
	 *
	 * 参数说明：
	 *     tree 伸展树的
	 *     z 插入的结点
	 */
	private SplayTreeNode<T> insert(SplayTreeNode<T> tree, SplayTreeNode<T> z) {
		int cmp;
		SplayTreeNode<T> y = null;
		SplayTreeNode<T> x = tree;

		// 查找z的插入位置
		while (x != null) {
			y = x;
			cmp = z.key.compareTo(x.key);
			if (cmp < 0)
				x = x.left;
			else if (cmp > 0)
				x = x.right;
			else {
				System.out.printf("不允许插入相同节点(%d)!\n", z.key);
				z=null;
				return tree;
			}
		}

		if (y==null)
			tree = z;
		else {
			cmp = z.key.compareTo(y.key);
			if (cmp < 0)
				y.left = z;
			else
				y.right = z;
		}

		return tree;
	}

	public void insert(T key) {
		SplayTreeNode<T> z=new SplayTreeNode<T>(key,null,null);

		// 如果新建结点失败，则返回。
		if ((z=new SplayTreeNode<T>(key,null,null)) == null)
			return ;

		// 插入节点
		mRoot = insert(mRoot, z);
		// 将节点(key)旋转为根节点
		mRoot = splay(mRoot, key);
	}

	/* 
	 * 删除结点(z)，并返回被删除的结点
	 *
	 * 参数说明：
	 *     bst 伸展树
	 *     z 删除的结点
	 */
	private SplayTreeNode<T> remove(SplayTreeNode<T> tree, T key) {
		SplayTreeNode<T> x;

		if (tree == null) 
			return null;

		// 查找键值为key的节点，找不到的话直接返回。
		if (search(tree, key) == null)
			return tree;

		// 将key对应的节点旋转为根节点。
		tree = splay(tree, key);

		if (tree.left != null) {
			// 将"tree的前驱节点"旋转为根节点
			x = splay(tree.left, key);
			// 移除tree节点
			x.right = tree.right;
		}
		else
			x = tree.right;

		tree = null;

		return x;
	}

	public void remove(T key) {
		mRoot = remove(mRoot, key);
	}

	/*
	 * 销毁伸展树
	 */
	private void destroy(SplayTreeNode<T> tree) {
		if (tree==null)
			return ;

		if (tree.left != null)
			destroy(tree.left);
		if (tree.right != null)
			destroy(tree.right);

		tree=null;
	}

	public void clear() {
		destroy(mRoot);
		mRoot = null;
	}

	/*
	 * 打印"伸展树"
	 *
	 * key        -- 节点的键值 
	 * direction  --  0，表示该节点是根节点;
	 *               -1，表示该节点是它的父结点的左孩子;
	 *                1，表示该节点是它的父结点的右孩子。
	 */
	private void print(SplayTreeNode<T> tree, T key, int direction) {

		if(tree != null) {

			if(direction==0)	// tree是根节点
				System.out.printf("%2d is root\n", tree.key);
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
