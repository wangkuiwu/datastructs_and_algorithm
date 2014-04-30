/**
 * Java 语言: 斐波那契堆
 *
 * @author skywang
 * @date 2014/04/07
 */

public class FibHeap {

	private int keyNum;         // 堆中节点的总数
	private FibNode min;	    // 最小节点(某个最小堆的根节点)

	private class FibNode {
		int key;			// 关键字(键值)
    	int degree;			// 度数
		FibNode left;		// 左兄弟
		FibNode right;		// 右兄弟
		FibNode child;		// 第一个孩子节点
		FibNode parent;		// 父节点
        boolean marked;     // 是否被删除第一个孩子

		public FibNode(int key) {
			this.key    = key;
			this.degree = 0;
			this.marked = false;
			this.left   = this;
			this.right  = this;
			this.parent = null;
			this.child  = null;
		}
	}

	public FibHeap() {
		this.keyNum = 0;
		this.min = null;
	}

	/* 
	 * 将node从双链表移除
	 */
	private void removeNode(FibNode node) {
		node.left.right = node.right;
		node.right.left = node.left;
	}
	 
	/*
	 * 将node堆结点加入root结点之前(循环链表中)
	 *   a …… root
	 *   a …… node …… root
	*/
	private void addNode(FibNode node, FibNode root) {
		node.left        = root.left;
		root.left.right  = node;
		node.right       = root;
		root.left        = node;
	}
	 
	/*
	 * 将节点node插入到斐波那契堆中
	 */
	private void insert(FibNode node) {
		if (keyNum == 0)
			min = node;
		else {
			addNode(node, min);
			if (node.key < min.key)
				min = node;
		}

		keyNum++;
	}
	 
	/* 
	 * 新建键值为key的节点，并将其插入到斐波那契堆中
	 */
	public void insert(int key) {
		FibNode node;

		node = new FibNode(key);
		if (node == null)
			return ;

		insert(node);
	}
	 
    /*
     * 将双向链表b链接到双向链表a的后面
     */
    private void catList(FibNode a, FibNode b) {
        FibNode tmp;

        tmp           = a.right;
        a.right       = b.right;
        b.right.left  = a;
        b.right       = tmp;
        tmp.left      = b;
    }

	/*
	 * 将other合并到当前堆中
	 */
	public void union(FibHeap other) {
		if (other==null)
			return ;

		if((this.min) == null) {                // this无"最小节点"
			this.min = other.min;
			this.keyNum = other.keyNum;
			other = null;
		} else if((other.min) == null) {        // this有"最小节点" && other无"最小节点"
			other = null;
		} else {                                // this有"最小节点" && other有"最小节点"
			// 将"other中根链表"添加到"this"中
            catList(this.min, other.min) ;

			if (this.min.key > other.min.key)
				this.min = other.min;
			this.keyNum += other.keyNum;
			other = null;;
		}
	}

	/*
	 * 将"堆的最小结点"从根链表中移除，
	 * 这意味着"将最小节点所属的树"从堆中移除!
	 */
	private FibNode extractMin() {
		FibNode p = min;

		if (p == p.right)
			min = null;
		else {
			removeNode(p);
			min = p.right;
		}
		p.left = p.right = p;

		return p;
	}
	 
	/*
	 * 将node链接到root根结点
	 */
	private void link(FibNode node, FibNode root) {
		// 将node从双链表中移除
		removeNode(node);
		// 将node设为root的孩子
		if (root.child == null)
			root.child = node;
		else
			addNode(node, root.child);

		node.parent = root;
		root.degree++;
		node.marked = false;
	}
	 
	/* 
	 * 合并斐波那契堆的根链表中左右相同度数的树
	 */
	private void consolidate() {
        // 计算log2(keyNum)，floor意味着向上取整！
        // ex. log2(13) = 3，向上取整为4。
		int maxDegree = (int) Math.floor(Math.log(keyNum) / Math.log(2.0));
		int D = maxDegree + 1;
		FibNode[] cons = new FibNode[D+1];

		for (int i = 0; i < D; i++)
			cons[i] = null;
	 
		// 合并相同度的根节点，使每个度数的树唯一
		while (min != null) {
			FibNode x = extractMin();			// 取出堆中的最小树(最小节点所在的树)
			int d = x.degree;						// 获取最小树的度数
			// cons[d] != null，意味着有两棵树(x和y)的"度数"相同。
			while (cons[d] != null) {
				FibNode y = cons[d];				// y是"与x的度数相同的树" 
				if (x.key > y.key) {	// 保证x的键值比y小
					FibNode tmp = x;
					x = y;
					y = tmp;
				}

				link(y, x);	// 将y链接到x中
				cons[d] = null;
				d++;
			}
			cons[d] = x;
		}
		min = null;
	 
		// 将cons中的结点重新加到根表中
		for (int i=0; i<D; i++) {

			if (cons[i] != null) {
				if (min == null)
					min = cons[i];
				else {
					addNode(cons[i], min);
					if ((cons[i]).key < min.key)
						min = cons[i];
				}
			}
		}
	}
	 
	/*
	 * 移除最小节点
	 */
	public void removeMin() {
		if (min==null)
			return ;

		FibNode m = min;
	    // 将min每一个儿子(儿子和儿子的兄弟)都添加到"斐波那契堆的根链表"中
		while (m.child != null) {
			FibNode child = m.child;

			removeNode(child);
			if (child.right == child)
				m.child = null;
			else
				m.child = child.right;

			addNode(child, min);
			child.parent = null;
		}

		// 将m从根链表中移除
		removeNode(m);
		// 若m是堆中唯一节点，则设置堆的最小节点为null；
		// 否则，设置堆的最小节点为一个非空节点(m.right)，然后再进行调节。
		if (m.right == m)
			min = null;
		else {
			min = m.right;
			consolidate();
		}
		keyNum--;

		m = null;
	}

	/*
	 * 获取斐波那契堆中最小键值；失败返回-1
	 */
	public int minimum() {
		if (min==null)
			return -1;

		return min.key;
	}
	  
	/* 
	 * 修改度数
	 */
	private void renewDegree(FibNode parent, int degree) {
		parent.degree -= degree;
		if (parent. parent != null)
			renewDegree(parent.parent, degree);
	}
	 
	/* 
	 * 将node从父节点parent的子链接中剥离出来，
	 * 并使node成为"堆的根链表"中的一员。
	 */
	private void cut(FibNode node, FibNode parent) {
		removeNode(node);
		renewDegree(parent, node.degree);
		// node没有兄弟
		if (node == node.right) 
			parent.child = null;
		else 
			parent.child = node.right;

		node.parent = null;
		node.left = node.right = node;
		node.marked = false;
		// 将"node所在树"添加到"根链表"中
		addNode(node, min);
	}

	/* 
	 * 对节点node进行"级联剪切"
	 *
	 * 级联剪切：如果减小后的结点破坏了最小堆性质，
	 *     则把它切下来(即从所在双向链表中删除，并将
	 *     其插入到由最小树根节点形成的双向链表中)，
	 *     然后再从"被切节点的父节点"到所在树根节点递归执行级联剪枝
	 */
	private void cascadingCut(FibNode node) {
		FibNode parent = node.parent;

		if (parent != null) {
			if (node.marked == false) 
				node.marked = true;
			else {
				cut(node, parent);
				cascadingCut(parent);
			}
		}
	}

	/* 
	 * 将斐波那契堆中节点node的值减少为key
	 */
	private void decrease(FibNode node, int key) {
		if (min==null ||node==null) 
			return ;

		if (key > node.key) {
        	System.out.printf("decrease failed: the new key(%d) is no smaller than current key(%d)\n", key, node.key);
			return ;
		}

		FibNode parent = node.parent;
		node.key = key;
		if (parent!=null && (node.key < parent.key)) {
			// 将node从父节点parent中剥离出来，并将node添加到根链表中
			cut(node, parent);
			cascadingCut(parent);
		}

		// 更新最小节点
		if (node.key < min.key)
			min = node;
	}

	/* 
	 * 将斐波那契堆中节点node的值增加为key
	 */
	private void increase(FibNode node, int key) {
		if (min==null ||node==null) 
			return ;

		if ( key <= node.key) {
        	System.out.printf("increase failed: the new key(%d) is no greater than current key(%d)\n", key, node.key);
			return ;
		}

		// 将node每一个儿子(不包括孙子,重孙,...)都添加到"斐波那契堆的根链表"中
		while (node.child != null) {
			FibNode child = node.child;
			removeNode(child);               // 将child从node的子链表中删除
			if (child.right == child)
				node.child = null;
			else
				node.child = child.right;

			addNode(child, min);       // 将child添加到根链表中
			child.parent = null;
		}
		node.degree = 0;
		node.key = key;

		// 如果node不在根链表中，
		//     则将node从父节点parent的子链接中剥离出来，
		//     并使node成为"堆的根链表"中的一员，
		//     然后进行"级联剪切"
		// 否则，则判断是否需要更新堆的最小节点
		FibNode parent = node.parent;
		if(parent != null) {
			cut(node, parent);
			cascadingCut(parent);
		} else if(min == node) {
			FibNode right = node.right;
			while(right != node) {
				if(node.key > right.key)
					min = right;
				right = right.right;
			}
		}
	}

	/* 
	 * 更新斐波那契堆的节点node的键值为key
	 */
	private void update(FibNode node, int key) {
		if(key < node.key)
			decrease(node, key);
		else if(key > node.key)
			increase(node, key);
		else
			System.out.printf("No need to update!!!\n");
	}
	  
	public void update(int oldkey, int newkey) {
		FibNode node;

		node = search(oldkey);
		if (node!=null)
			update(node, newkey);
	}

	/*
	 * 在最小堆root中查找键值为key的节点
	 */
	private FibNode search(FibNode root, int key) {
		FibNode t = root;	// 临时节点
		FibNode p = null;	// 要查找的节点

		if (root==null)
			return root;

		do {
			if (t.key == key) {
				p = t;
				break;
			} else {
				if ((p = search(t.child, key)) != null) 
					break;
			}
			t = t.right;
		} while (t != root);

		return p;
	}
	 
	/*
	 * 在斐波那契堆中查找键值为key的节点
	 */
	private FibNode search(int key) {
		if (min==null)
			return null;

		return search(min, key);
	}

	/*
	 * 在斐波那契堆中是否存在键值为key的节点。
	 * 存在返回true，否则返回false。
	 */
	public boolean contains(int key) {
		return search(key)!=null ? true: false;
	}

	/*
	 * 删除结点node
	 */
	private void remove(FibNode node) {
		int m = min.key;
		decrease(node, m-1);
		removeMin();
	}

	public void remove(int key) {
		if (min==null)
			return ;

		FibNode node = search(key);
		if (node==null)
			return ;

		remove(node);
	}
	 
	/* 
	 * 销毁斐波那契堆
	 */
	private void destroyNode(FibNode node) {
		if(node == null)
			return;

		FibNode start = node;
		do {
			destroyNode(node.child);
			// 销毁node，并将node指向下一个
			node = node.right;
			node.left = null;
		} while(node != start);
	}
	 
	public void destroy() {
		destroyNode(min);
	}

	/*
	 * 打印"斐波那契堆"
	 *
	 * 参数说明：
	 *     node       -- 当前节点
	 *     prev       -- 当前节点的前一个节点(父节点or兄弟节点)
	 *     direction  --  1，表示当前节点是一个左孩子;
	 *                    2，表示当前节点是一个兄弟节点。
	 */
	private void print(FibNode node, FibNode prev, int direction) {
		FibNode start=node;

		if (node==null)
			return ;
		do {
			if (direction == 1)
				System.out.printf("%8d(%d) is %2d's child\n", node.key, node.degree, prev.key);
			else
				System.out.printf("%8d(%d) is %2d's next\n", node.key, node.degree, prev.key);

			if (node.child != null)
				print(node.child, node, 1);

			// 兄弟节点
			prev = node;
			node = node.right;
			direction = 2;
		} while(node != start);
	}

	public void print() {
		if (min==null)
			return ;

		int i=0;
		FibNode p = min;
		System.out.printf("== 斐波那契堆的详细信息: ==\n");
		do {
			i++;
			System.out.printf("%2d. %4d(%d) is root\n", i, p.key, p.degree);

			print(p.child, p, 1);
			p = p.right;
		} while (p != min);
		System.out.printf("\n");
	}
}
