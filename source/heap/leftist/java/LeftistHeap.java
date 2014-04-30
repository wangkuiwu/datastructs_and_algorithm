/**
 * Java 语言: 左倾堆
 *
 * @author skywang
 * @date 2014/03/31
 */


public class LeftistHeap<T extends Comparable<T>> {

	private LeftistNode<T> mRoot;	// 根结点

	private class LeftistNode<T extends Comparable<T>> {
		T key;				    // 关键字(键值)
    	int npl;			    // 零路经长度(Null Path Length)
		LeftistNode<T> left;	// 左孩子
		LeftistNode<T> right;	// 右孩子

		public LeftistNode(T key, LeftistNode<T> left, LeftistNode<T> right) {
			this.key = key;
			this.npl = 0;
			this.left = left;
			this.right = right;
		}

		public String toString() {
			return "key:"+key;
		}
	}

	public LeftistHeap() {
		mRoot = null;
	}

	/*
	 * 前序遍历"左倾堆"
	 */
	private void preOrder(LeftistNode<T> heap) {
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
	 * 中序遍历"左倾堆"
	 */
	private void inOrder(LeftistNode<T> heap) {
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
	 * 后序遍历"左倾堆"
	 */
	private void postOrder(LeftistNode<T> heap) {
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
     * 合并"左倾堆x"和"左倾堆y"
     */
    private LeftistNode<T> merge(LeftistNode<T> x, LeftistNode<T> y) {
        if(x == null) return y;
        if(y == null) return x;

        // 合并x和y时，将x作为合并后的树的根；
        // 这里的操作是保证: x的key < y的key
        if(x.key.compareTo(y.key) > 0) {
            LeftistNode<T> tmp = x;
            x = y;
            y = tmp;
        }

        // 将x的右孩子和y合并，"合并后的树的根"是x的右孩子。
        x.right = merge(x.right, y);

		// 如果"x的左孩子为空" 或者 "x的左孩子的npl<右孩子的npl"
		// 则，交换x和y
        if (x.left == null || x.left.npl < x.right.npl) {
            LeftistNode<T> tmp = x.left;
            x.left = x.right;
            x.right = tmp;
        }
        if (x.right == null || x.left == null)
            x.npl = 0;
        else
            x.npl = (x.left.npl > x.right.npl) ? (x.right.npl + 1) : (x.left.npl + 1);

        return x;
    }

    public void merge(LeftistHeap<T> other) {
        this.mRoot = merge(this.mRoot, other.mRoot);
    }

	/* 
	 * 新建结点(key)，并将其插入到左倾堆中
	 *
	 * 参数说明：
	 *     key 插入结点的键值
	 */
	public void insert(T key) {
		LeftistNode<T> node = new LeftistNode<T>(key,null,null);

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
        LeftistNode<T> l = this.mRoot.left;
        LeftistNode<T> r = this.mRoot.right;

        this.mRoot = null;          // 删除根节点
        this.mRoot = merge(l, r);   // 合并左右子树

        return key;
	}

	/*
	 * 销毁左倾堆
	 */
	private void destroy(LeftistNode<T> heap) {
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
	 * 打印"左倾堆"
	 *
	 * key        -- 节点的键值 
	 * direction  --  0，表示该节点是根节点;
	 *               -1，表示该节点是它的父结点的左孩子;
	 *                1，表示该节点是它的父结点的右孩子。
	 */
	private void print(LeftistNode<T> heap, T key, int direction) {

		if(heap != null) {

			if(direction==0)	// heap是根节点
				System.out.printf("%2d(%d) is root\n", heap.key, heap.npl);
			else				// heap是分支节点
				System.out.printf("%2d(%d) is %2d's %6s child\n", heap.key, heap.npl, key, direction==1?"right" : "left");

			print(heap.left, heap.key, -1);
			print(heap.right,heap.key,  1);
		}
	}

	public void print() {
		if (mRoot != null)
			print(mRoot, mRoot.key, 0);
	}
}

