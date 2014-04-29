
/**
 * Java 实现的双向链表。 
 * 注：java自带的集合包中有实现双向链表，路径是:java.util.LinkedList
 *
 * @author skywang
 * @date 2013/11/07
 */
public class DoubleLink<T> {

	// 表头
	private DNode<T> mHead;
	// 节点个数
	private int mCount;

	// 双向链表“节点”对应的结构体
	private class DNode<T> {
		public DNode prev;
		public DNode next;
		public T value;

		public DNode(T value, DNode prev, DNode next) {
			this.value = value;
			this.prev = prev;
			this.next = next;
		}
	}

	// 构造函数
	public DoubleLink() {
		// 创建“表头”。注意：表头没有存储数据！
		mHead = new DNode<T>(null, null, null);
		mHead.prev = mHead.next = mHead;
		// 初始化“节点个数”为0
		mCount = 0;
	}

	// 返回节点数目
	public int size() {
		return mCount;
	}

	// 返回链表是否为空
	public boolean isEmpty() {
		return mCount==0;
	}

	// 获取第index位置的节点
	private DNode<T> getNode(int index) {
		if (index<0 || index>=mCount)
			throw new IndexOutOfBoundsException();

		// 正向查找
		if (index <= mCount/2) {
			DNode<T> node = mHead.next;
			for (int i=0; i<index; i++)
				node = node.next;

			return node;
		}

		// 反向查找
		DNode<T> rnode = mHead.prev;
		int rindex = mCount - index -1;
		for (int j=0; j<rindex; j++)
			rnode = rnode.prev;

		return rnode;
	}

	// 获取第index位置的节点的值
	public T get(int index) {
		return getNode(index).value;
	}

	// 获取第1个节点的值
	public T getFirst() {
		return getNode(0).value;
	}

	// 获取最后一个节点的值
	public T getLast() {
		return getNode(mCount-1).value;
	}

	// 将节点插入到第index位置之前
	public void insert(int index, T t) {
		if (index==0) {
			DNode<T> node = new DNode<T>(t, mHead, mHead.next);
			mHead.next.prev = node;
			mHead.next = node;
			mCount++;
			return ;
		}

		DNode<T> inode = getNode(index);
		DNode<T> tnode = new DNode<T>(t, inode.prev, inode);
		inode.prev.next = tnode;
		inode.next = tnode;
		mCount++;
		return ;
	}

	// 将节点插入第一个节点处。
	public void insertFirst(T t) {
		insert(0, t);
	}

	// 将节点追加到链表的末尾
	public void appendLast(T t) {
		DNode<T> node = new DNode<T>(t, mHead.prev, mHead);
		mHead.prev.next = node;
		mHead.prev = node;
		mCount++;
	}

	// 删除index位置的节点
	public void del(int index) {
		DNode<T> inode = getNode(index);
		inode.prev.next = inode.next;
		inode.next.prev = inode.prev;
		inode = null;
		mCount--;
	}

	// 删除第一个节点
	public void deleteFirst() {
		del(0);
	}

	// 删除最后一个节点
	public void deleteLast() {
		del(mCount-1);
	}
}

