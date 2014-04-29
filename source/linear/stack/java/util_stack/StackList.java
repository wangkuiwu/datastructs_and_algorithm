
import java.util.Stack;

/**
 * Java : 用2个“栈”实现队列
 *
 * @author skywang
 * @date 2013/11/07
 */
public class StackList<T> {

	// 向队列添加数据时：(01) 将“已有的全部数据”都移到mIn中。 (02) 将“新添加的数据”添加到mIn中。
	private Stack<T> mIn  = null;
	// 从队列获取元素时：(01) 将“已有的全部数据”都移到mOut中。(02) 返回并删除mOut栈顶元素。
	private Stack<T> mOut = null;
	// 统计计数
	private int mCount = 0;

	public StackList() {
		mIn = new Stack<T>();
		mOut = new Stack<T>();
		mCount = 0;
	}

// 将t添加到队列中
	public void add(T t) {
		// 将“已有的全部数据”都移到mIn中
		while (!mOut.empty())
			mIn.push(mOut.pop());

		// 将“新添加的数据”添加到mIn中
		mIn.push(t);
		// 统计数+1
		mCount++;
	}

// 返回队列开头的元素
	public T front() {
		// 将“已有的全部数据”都移到mOut中
		while (!mIn.empty())
			mOut.push(mIn.pop());

		// 返回mOut栈顶元素
		return mOut.peek();
	}

// 删除并返回队列开头的元素
	public T pop() {
		// 将“已有的全部数据”都移到mOut中
		while (!mIn.empty())
			mOut.push(mIn.pop());
		// 统计数-1
		mCount--;

		// 返回并删除mOut栈顶元素
		return mOut.pop();
	}

	public int size() {
		return mCount;
	}
	public boolean isEmpty() {
		return mCount==0;
	}

	public static void main(String[] args) {
		int tmp;
		StackList<Integer> slist = new StackList<Integer>();

		// 将10, 20, 30 依次推入栈中
		slist.add(10);
		slist.add(20);
		slist.add(30);

		// 将“队列开头的元素”赋值给tmp，并删除“该元素”
		tmp = slist.pop();
		System.out.printf("tmp()=%d\n", tmp);

		// 只将“队列开头的元素”赋值给tmp，不删除该元素.
		tmp = slist.front();
		System.out.printf("tmp()=%d\n", tmp);

		slist.add(40);

		System.out.printf("isEmpty()=%b\n", slist.isEmpty());
		System.out.printf("size()=%d\n", slist.size());
		while(!slist.isEmpty()) {
			System.out.printf("%d\n", slist.pop());
		}
	}
}
