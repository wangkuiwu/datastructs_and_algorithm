/**
 * 二叉堆(最小堆)
 *
 * @author skywang
 * @date 2014/03/07
 */

import java.util.ArrayList;
import java.util.List;

public class MinHeap<T extends Comparable<T>> {

	private List<T> mHeap;		// 存放堆的数组

	public MinHeap() {
		this.mHeap = new ArrayList<T>();
	}

	/* 
	 * 最小堆的向下调整算法
	 *
	 * 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
	 *
	 * 参数说明：
	 *     start -- 被下调节点的起始位置(一般为0，表示从第1个开始)
	 *     end   -- 截至范围(一般为数组中最后一个元素的索引)
	 */
	protected void filterdown(int start, int end) {
		int c = start; 	 	// 当前(current)节点的位置
		int l = 2*c + 1; 	// 左(left)孩子的位置
		T tmp = mHeap.get(c);	// 当前(current)节点的大小

		while(l <= end) {
			int cmp = mHeap.get(l).compareTo(mHeap.get(l+1));
			// "l"是左孩子，"l+1"是右孩子
			if(l < end && cmp>0)
				l++;		// 左右两孩子中选择较小者，即mHeap[l+1]

			cmp = tmp.compareTo(mHeap.get(l));
			if(cmp <= 0)
				break;		//调整结束
			else {
				mHeap.set(c, mHeap.get(l));
				c = l;
				l = 2*l + 1;   
			}       
		}   
		mHeap.set(c, tmp);
	}
	 
	/*
	 * 最小堆的删除
	 *
	 * 返回值：
	 *     成功，返回被删除的值
	 *     失败，返回null
	 */
	public int remove(T data) {
		// 如果"堆"已空，则返回-1
		if(mHeap.isEmpty() == true)
			return -1;

		// 获取data在数组中的索引
		int index = mHeap.indexOf(data);
		if (index==-1)
			return -1;

		int size = mHeap.size();
		mHeap.set(index, mHeap.get(size-1));// 用最后元素填补
		mHeap.remove(size - 1);				// 删除最后的元素

		if (mHeap.size() > 1)
			filterdown(index, mHeap.size()-1);	// 从index号位置开始自上向下调整为最小堆

		return 0;
	}

	/*
	 * 最小堆的向上调整算法(从start开始向上直到0，调整堆)
	 *
	 * 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
	 *
	 * 参数说明：
	 *     start -- 被上调节点的起始位置(一般为数组中最后一个元素的索引)
	 */
	protected void filterup(int start) {
		int c = start;			// 当前节点(current)的位置
		int p = (c-1)/2;		// 父(parent)结点的位置 
		T tmp = mHeap.get(c);		// 当前节点(current)的大小

		while(c > 0) {
			int cmp = mHeap.get(p).compareTo(tmp);
			if(cmp <= 0)
				break;
			else {
				mHeap.set(c, mHeap.get(p));
				c = p;
				p = (p-1)/2;   
			}       
		}
		mHeap.set(c, tmp);
	}
 
	/* 
	 * 将data插入到二叉堆中
	 */
	public void insert(T data) {
		int size = mHeap.size();

		mHeap.add(data);	// 将"数组"插在表尾
		filterup(size);		// 向上调整堆
	}
	   
	public String toString() {
		StringBuilder sb = new StringBuilder();
		for (int i=0; i<mHeap.size(); i++)
			sb.append(mHeap.get(i) +" ");

		return sb.toString();
	}

	public static void main(String[] args) {
		int i;
    	//int a[] = {80, 40, 30, 60, 90, 70, 10, 50, 20};
		int a[]= {5,6,8,7,15};
		MinHeap<Integer> tree=new MinHeap<Integer>();

		System.out.printf("== 依次添加: ");
		for(i=0; i<a.length; i++) {
			System.out.printf("%d ", a[i]);
			tree.insert(a[i]);
		}

		System.out.printf("\n== 最 小 堆: %s", tree);

		i=15;
		tree.insert(i);
		System.out.printf("\n== 添加元素: %d", i);
		System.out.printf("\n== 最 小 堆: %s", tree);

		i=10;
		tree.remove(i);
		System.out.printf("\n== 删除元素: %d", i);
		System.out.printf("\n== 最 小 堆: %s", tree);
		System.out.printf("\n");
	}
}
