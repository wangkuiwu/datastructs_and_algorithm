/**
 * Java 语言: 二项堆
 *
 * @author skywang
 * @date 2014/04/03
 */

public class BinomialHeap<T extends Comparable<T>> {

	private BinomialNode<T> mRoot;	// 根结点

	private class BinomialNode<T extends Comparable<T>> {
		T key;			    // 关键字(键值)
    	int degree;			// 度数
		BinomialNode<T> child;	// 左孩子
		BinomialNode<T> parent;	// 父节点
		BinomialNode<T> next;	// 兄弟节点

		public BinomialNode(T key) {
			this.key = key;
			this.degree = 0;
			this.child = null;
			this.parent = null;
			this.next = null;
		}

		public String toString() {
			return "key:"+key;
		}
	}

	public BinomialHeap() {
		mRoot = null;
	}

	/*
	 * 获取二项堆中的最小节点的键值
	 */
	public T minimum() {
		if (mRoot==null)
			return null;

		BinomialNode<T> x, prev_x;	// x是用来遍历的当前节点
		BinomialNode<T> y, prev_y;	// y是最小节点

		prev_x  = mRoot;
		x       = mRoot.next;
		prev_y  = null;
		y       = mRoot;
		// 找到最小节点
		while (x != null) {
			if (x.key.compareTo(y.key) < 0) {
				y = x;
				prev_y = prev_x;
			}
			prev_x = x;
			x = x.next;
		}

		return y.key;
	}

	 
	/*
	 * 合并两个二项堆：将child合并到root中
	 */
	private void link(BinomialNode<T> child, BinomialNode<T> root) {
		child.parent = root;
		child.next   = root.child;
		root.child = child;
		root.degree++;
	}

	/*
	 * 将h1, h2中的根表合并成一个按度数递增的链表，返回合并后的根节点
	 */
	private BinomialNode<T> merge(BinomialNode<T> h1, BinomialNode<T> h2) {
		if (h1 == null) return h2;
		if (h2 == null) return h1;

		// root是新堆的根，h3用来遍历h1和h3的。
		BinomialNode<T> pre_h3, h3, root=null;
	 
		pre_h3 = null;
		//整个while，h1, h2, pre_h3, h3都在往后顺移
		while ((h1!=null) && (h2!=null)) {

			if (h1.degree <= h2.degree) {
				h3 = h1;
				h1 = h1.next;
			} else {
				h3 = h2;
				h2 = h2.next;
			}
 
			if (pre_h3 == null) {
				pre_h3 = h3;
				root = h3;
			} else {
				pre_h3.next = h3;
				pre_h3 = h3;
			}

			if (h1 != null) {
				h3.next = h1;
			} else {
				h3.next = h2;
			}
		}
		return root;
	}

	/*
	 * 合并二项堆：将h1, h2合并成一个堆，并返回合并后的堆
	 */
	private BinomialNode<T> union(BinomialNode<T> h1, BinomialNode<T> h2) {
		BinomialNode<T> root;

		// 将h1, h2中的根表合并成一个按度数递增的链表root
		root = merge(h1, h2);
		if (root == null)
			return null;
	 
		BinomialNode<T> prev_x = null;
		BinomialNode<T> x      = root;
		BinomialNode<T> next_x = x.next;
		while (next_x != null) {

			if (   (x.degree != next_x.degree) 
				|| ((next_x.next != null) && (next_x.degree == next_x.next.degree))) {
				// Case 1: x.degree != next_x.degree
				// Case 2: x.degree == next_x.degree == next_x.next.degree
				prev_x = x;
				x = next_x;
			} else if (x.key.compareTo(next_x.key) <= 0) {
				// Case 3: x.degree == next_x.degree != next_x.next.degree
				//      && x.key    <= next_x.key
				x.next = next_x.next;
				link(next_x, x);
			} else {
				// Case 4: x.degree == next_x.degree != next_x.next.degree
				//      && x.key    >  next_x.key
				if (prev_x == null) {
					root = next_x;
				} else {
					prev_x.next = next_x;
				}
				link(x, next_x);
				x = next_x;
			}
			next_x = x.next;
		}

		return root;
	}

	/*
	 * 将二项堆other合并到当前堆中
	 */
	public void union(BinomialHeap<T> other) {
		if (other!=null && other.mRoot!=null)
			mRoot = union(mRoot, other.mRoot);
	}

	/*
	 * 新建key对应的节点，并将其插入到二项堆中。
	 */
	public void insert(T key) {
		BinomialNode<T> node;

		// 禁止插入相同的键值
		if (contains(key)==true) {
			System.out.printf("insert failed: the key(%s) is existed already!\n", key);
			return ;
		}

		node = new BinomialNode<T>(key);
		if (node==null)
			return ;

		mRoot = union(mRoot, node);
	}

	/*
	 * 反转二项堆root，并返回反转后的根节点
	 */
	private BinomialNode<T> reverse(BinomialNode<T> root) {
		BinomialNode<T> next;
		BinomialNode<T> tail = null;

		if (root==null)
			return root;

		root.parent = null;
		while (root.next!=null) {
			next         = root.next;
			root.next    = tail;
			tail         = root;
			root         = next;
			root.parent  = null;
		}
		root.next = tail;

		return root;
	}

	/*
	 * 移除二项堆root中的最小节点，并返回删除节点后的二项树
	 */
	private BinomialNode<T> extractMinimum(BinomialNode<T> root) {
		if (root==null)
			return root;
	 
		BinomialNode<T> x, prev_x;	// x是用来遍历的当前节点
		BinomialNode<T> y, prev_y;	// y是最小节点
	 
		prev_x  = root;
		x       = root.next;
		prev_y = null;
		y      = root;
		// 找到最小节点
		while (x != null) {
			if (x.key.compareTo(y.key) < 0) {
				y = x;
				prev_y = prev_x;
			}
			prev_x = x;
			x = x.next;
		}

		if (prev_y == null)	// root的根节点就是最小根节点
			root = root.next;
		else				// root的根节点不是最小根节点
			prev_y.next = y.next;
	 
		// 反转最小节点的左孩子，得到最小堆child；
		// 这样，就使得最小节点所在二项树的孩子们都脱离出来成为一棵独立的二项树(不包括最小节点)
		BinomialNode<T> child = reverse(y.child);
		// 将"删除最小节点的二项堆child"和"root"进行合并。
		root = union(root, child);

		// help GC
		y = null;

		return root;
	}

	public void extractMinimum() {
		mRoot = extractMinimum(mRoot);
	}

	/* 
	 * 减少关键字的值：将二项堆中的节点node的键值减小为key。
	 */
	private void decreaseKey(BinomialNode<T> node, T key) {
		if(key.compareTo(node.key)>=0 || contains(key)==true) {
        	System.out.println("decrease failed: the new key("+key+") is existed already, or is no smaller than current key("+node.key+")");
			return ;
		}
		node.key = key;
	 
		BinomialNode<T> child, parent;
		child = node;
		parent = node.parent;
		while(parent != null && child.key.compareTo(parent.key)<0) {
			// 交换parent和child的数据
			T tmp = parent.key;
			parent.key = child.key;
			child.key = tmp;

			child = parent;
			parent = child.parent;
		}
	}

	/* 
	 * 增加关键字的值：将二项堆中的节点node的键值增加为key。
	 */
	private void increaseKey(BinomialNode<T> node, T key) {
		if(key.compareTo(node.key)<=0 || contains(key)==true) {
        	System.out.println("increase failed: the new key("+key+") is existed already, or is no greater than current key("+node.key+")");
			return ;
		}
		node.key = key;

		BinomialNode<T> cur = node;
		BinomialNode<T> child = cur.child;
		while (child != null) {

			if(cur.key.compareTo(child.key) > 0) {
				// 如果"当前节点" < "它的左孩子"，
				// 则在"它的孩子中(左孩子 和 左孩子的兄弟)"中，找出最小的节点；
				// 然后将"最小节点的值" 和 "当前节点的值"进行互换
				BinomialNode<T> least = child;	// least是child和它的兄弟中的最小节点
				while(child.next != null) {
					if (least.key.compareTo(child.next.key) > 0)
						least = child.next;
					child = child.next;
				}
				// 交换最小节点和当前节点的值
				T tmp = least.key;
				least.key = cur.key;
				cur.key = tmp;

				// 交换数据之后，再对"原最小节点"进行调整，使它满足最小堆的性质：父节点 <= 子节点
				cur = least;
				child = cur.child;
			} else {
				child = child.next;
			}
		}
	}

	/* 
	 * 更新二项堆的节点node的键值为key
	 */
	private void updateKey(BinomialNode<T> node, T key) {
		if (node == null)
			return ;

		int cmp = key.compareTo(node.key);
		if(cmp < 0)							// key < node.key
			decreaseKey(node, key);
		else if(cmp > 0)					// key > node.key
			increaseKey(node, key);
		else
			System.out.println("No need to update!!!");
	}

	/* 
	 * 将二项堆中键值oldkey更新为newkey
	 */
	public void update(T oldkey, T newkey) {
		BinomialNode<T> node;

		node = search(mRoot, oldkey);
		if (node != null)
			updateKey(node, newkey);
	}

	/*
	 * 查找：在二项堆中查找键值为key的节点
	 */
	private BinomialNode<T> search(BinomialNode<T> root, T key) {
		BinomialNode<T> child;
		BinomialNode<T> parent = root;

		parent = root;
		while (parent != null) {
			if (parent.key.compareTo(key) == 0)
				return parent;
			else {
				if((child = search(parent.child, key)) != null)
					return child;
				parent = parent.next;
			}
		}

		return null;
	}
	 
	/*
	 * 二项堆中是否包含键值key
	 */
	public boolean contains(T key) {
		return search(mRoot, key)!=null ? true : false;
	}

	/* 
	 * 删除节点：删除键值为key的节点
	 */
	private BinomialNode<T> remove(BinomialNode<T> root, T key) {
		if (root==null)
			return root;

		BinomialNode<T> node;

		// 查找键值为key的节点
		if ((node = search(root, key)) == null)
			return root;

		// 将被删除的节点的数据数据上移到它所在的二项树的根节点
		BinomialNode<T> parent = node.parent;
		while (parent != null) {
			// 交换数据
			T tmp = node.key;
			node.key = parent.key;
			parent.key = tmp;

			// 下一个父节点
			node   = parent;
			parent = node.parent;
		}

		// 找到node的前一个根节点(prev)
		BinomialNode<T> prev = null;
		BinomialNode<T> pos  = root;
		while (pos != node) {
			prev = pos;
			pos  = pos.next;
		}
		// 移除node节点
		if (prev!=null)
			prev.next = node.next;
		else
			root = node.next;

		root = union(root, reverse(node.child)); 

		// help GC
		node = null;

		return root;
	}

	public void remove(T key) {
		mRoot = remove(mRoot, key);
	}

	/*
	 * 打印"二项堆"
	 *
	 * 参数说明：
	 *     node       -- 当前节点
	 *     prev       -- 当前节点的前一个节点(父节点or兄弟节点)
	 *     direction  --  1，表示当前节点是一个左孩子;
	 *                    2，表示当前节点是一个兄弟节点。
	 */
	private void print(BinomialNode<T> node, BinomialNode<T> prev, int direction) {
		while(node != null)
		{
			if(direction==1)	// node是根节点
				System.out.printf("\t%2d(%d) is %2d's child\n", node.key, node.degree, prev.key);
			else				// node是分支节点
				System.out.printf("\t%2d(%d) is %2d's next\n", node.key, node.degree, prev.key);

			if (node.child != null)
				print(node.child, node, 1);

			// 兄弟节点
			prev = node;
			node = node.next;
			direction = 2;
		}
	}

	public void print() {
		if (mRoot == null)
			return ;

		BinomialNode<T> p = mRoot;
		System.out.printf("== 二项堆( ");
		while (p != null) {
			System.out.printf("B%d ", p.degree);
			p = p.next;
		}
		System.out.printf(")的详细信息：\n");

		int i=0;
		p = mRoot;
		while (p != null) {
			i++;
			System.out.printf("%d. 二项树B%d: \n", i, p.degree);
			System.out.printf("\t%2d(%d) is root\n", p.key, p.degree);

			print(p.child, p, 1);
			p = p.next;
		}
		System.out.printf("\n");
	}
}
