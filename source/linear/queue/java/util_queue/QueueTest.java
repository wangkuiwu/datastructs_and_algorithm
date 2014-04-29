
import java.util.Queue;
import java.util.LinkedList;

/**
 * Java : 集合包自带的队列(Queue)的演示程序。
 *
 * @author skywang
 * @date 2013/11/07
 */
public class QueueTest {

	public static void main(String[] args) {
		Integer tmp;
		Queue<Integer> que = new LinkedList<Integer>();

		// 将10, 20, 30 依次推入队列中
		que.add(10);
		que.add(20);
		que.add(30);

		// 将“队列开头的元素”赋值给tmp，并删除“该元素”
		tmp = que.poll();
		System.out.printf("tmp=%d\n", tmp);

		// 将“队列开头的元素”赋值给tmp，不删除该元素.
		tmp = que.peek();
		System.out.printf("tmp=%d\n", tmp);

		que.add(40);

		System.out.printf("isEmpty()=%b\n", que.isEmpty());
		System.out.printf("size()=%d\n", que.size());
		while(!que.isEmpty()) {
			tmp = que.poll();
			System.out.printf("tmp=%d\n", tmp);
		}
	}
}

