/**
 * Java 语言: 斜堆
 *
 * @author skywang
 * @date 2014/03/31
 */

public class SkewHeap<T extends Comparable<T>> {

	private SkewNode<T> mRoot;	// 根结点

	private class SkewNode<T extends Comparable<T>> {
		T key;			    // 关键字(键值)
		SkewNode<T> left;	// 左孩子
		SkewNode<T> right;	// 右孩子

		public SkewNode(T key, SkewNode<T> left, SkewNode<T> right) {
			this.key = key;
			this.left = left;
			this.right = right;
		}

		public String toString() {
			return "key:"+key;
		}
	}

	public SkewHeap() {
		mRoot = null;
	}

	/*
	 * 前序遍历"斜堆"
	 */
	private void preOrder(SkewNode<T> heap) {
		if(heap != null) {
			System.out.print(heap.key+" ");
			preOrder(heap.left);
			preOrder(heap.right);
		}
	}

	public void preOrder() {
		preOrder(mRoot);
	}

	/*
	 * 中序遍历"斜堆"
	 */
	private void inOrder(SkewNode<T> heap) {
		if(heap != null) {
			inOrder(heap.left);
			System.out.print(heap.key+" ");
			inOrder(heap.right);
		}
	}

	public void inOrder() {
		inOrder(mRoot);
	}

	/*
	 * 后序遍历"斜堆"
	 */
	private void postOrder(SkewNode<T> heap) {
		if(heap != null)
		{
			postOrder(heap.left);
			postOrder(heap.right);
			System.out.print(heap.key+" ");
		}
	}

	public void postOrder() {
		postOrder(mRoot);
	}

    /*
     * 合并"斜堆x"和"斜堆y"
     */
    private SkewNode<T> merge(SkewNode<T> x, SkewNode<T> y) {
        if(x == null) return y;
        if(y == null) return x;

        // 合并x和y时，将x作为合并后的树的根；
        // 这里的操作是保证: x的key < y的key
        if(x.key.compareTo(y.key) > 0) {
            SkewNode<T> tmp = x;
            x = y;
            y = tmp;
        }

		// 将x的右孩子和y合并，
		// 合并后直接交换x的左右孩子，而不需要像左倾堆一样考虑它们的npl。
        SkewNode<T> tmp = merge(x.right, y);
        x.right = x.left;
        x.left = tmp;

        return x;
    }

    public void merge(SkewHeap<T> other) {
        this.mRoot = merge(this.mRoot, other.mRoot);
    }

	/* 
	 * 新建结点(key)，并将其插入到斜堆中
	 *
	 * 参数说明：
	 *     key 插入结点的键值
	 */
	public void insert(T key) {
		SkewNode<T> node = new SkewNode<T>(key,null,null);

		// 如果新建结点失败，则返回。
		if (node != null)
            this.mRoot = merge(this.mRoot, node);
	}

	/* 
	 * 删除根结点
	 * 
     * 返回值：
     *     返回被删除的节点的键值
	 */
	public T remove() {
        if (this.mRoot == null)
            return null;

		T key = this.mRoot.key;
        SkewNode<T> l = this.mRoot.left;
        SkewNode<T> r = this.mRoot.right;

        this.mRoot = null;          // 删除根节点
        this.mRoot = merge(l, r);   // 合并左右子树

        return key;
	}

	/*
	 * 销毁斜堆
	 */
	private void destroy(SkewNode<T> heap) {
		if (heap==null)
			return ;

		if (heap.left != null)
			destroy(heap.left);
		if (heap.right != null)
			destroy(heap.right);

		heap=null;
	}

	public void clear() {
		destroy(mRoot);
		mRoot = null;
	}

	/*
	 * 打印"斜堆"
	 *
	 * key        -- 节点的键值 
	 * direction  --  0，表示该节点是根节点;
	 *               -1，表示该节点是它的父结点的左孩子;
	 *                1，表示该节点是它的父结点的右孩子。
	 */
	private void print(SkewNode<T> heap, T key, int direction) {

		if(heap != null) {

			if(direction==0)	// heap是根节点
				System.out.printf("%2d is root\n", heap.key);
			else				// heap是分支节点
				System.out.printf("%2d is %2d's %6s child\n", heap.key, key, direction==1?"right" : "left");

			print(heap.left, heap.key, -1);
			print(heap.right,heap.key,  1);
		}
	}

	public void print() {
		if (mRoot != null)
			print(mRoot, mRoot.key, 0);
	}
}

