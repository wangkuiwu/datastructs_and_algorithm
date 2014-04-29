
import java.util.Stack;

/**
 * Java : java集合包中的Stack的演示程序
 *
 * @author skywang
 * @date 2013/11/07
 */
public class StackTest {

	public static void main(String[] args) {
		int tmp=0;
		Stack<Integer> astack = new Stack<Integer>();

		// 将10, 20, 30 依次推入栈中
		astack.push(10);
		astack.push(20);
		astack.push(30);

		// 将“栈顶元素”赋值给tmp，并删除“栈顶元素”
		tmp = astack.pop();
		//System.out.printf("tmp=%d\n", tmp);

		// 只将“栈顶”赋值给tmp，不删除该元素.
		tmp = (int)astack.peek();
		//System.out.printf("tmp=%d\n", tmp);

		astack.push(40);
		while(!astack.empty()) {
			tmp = (int)astack.pop();
			System.out.printf("tmp=%d\n", tmp);
		}
	}
}

