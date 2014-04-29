
/**
 * Java : 数组实现“队列”，只能存储int数据。
 *
 * @author skywang
 * @date 2013/11/07
 */
public class ArrayQueue {

	private int[] mArray;
	private int mCount;

	public ArrayQueue(int sz) {
		mArray = new int[sz];
		mCount = 0;
	}

	// 将val添加到队列的末尾
	public void add(int val) {
		mArray[mCount++] = val;
	}

	// 返回“队列开头元素”
	public int front() {
		return mArray[0];
	}

	// 返回“栈顶元素值”，并删除“栈顶元素”
	public int pop() {
		int ret = mArray[0];
		mCount--;
		for (int i=1; i<=mCount; i++)
			mArray[i-1] = mArray[i];
		return ret;
	}

	// 返回“栈”的大小
	public int size() {
		return mCount;
	}

	// 返回“栈”是否为空
	public boolean isEmpty() {
		return size()==0;
	}

	public static void main(String[] args) {
		int tmp=0;
		ArrayQueue astack = new ArrayQueue(12);

		// 将10, 20, 30 依次推入栈中
		astack.add(10);
		astack.add(20);
		astack.add(30);

		// 将“栈顶元素”赋值给tmp，并删除“栈顶元素”
		tmp = astack.pop();
		System.out.printf("tmp=%d\n", tmp);

		// 只将“栈顶”赋值给tmp，不删除该元素.
		tmp = astack.front();
		System.out.printf("tmp=%d\n", tmp);

		astack.add(40);

		System.out.printf("isEmpty()=%b\n", astack.isEmpty());
		System.out.printf("size()=%d\n", astack.size());
		while (!astack.isEmpty()) {
			System.out.printf("size()=%d\n", astack.pop());
		}
	}
}

