/**
 * Java 语言: 斐波那契堆
 *
 * @author skywang
 * @date 2014/04/07
 */

public class Main {

	private static final boolean DEBUG = false;

	// 共8个
	private static int a[] = {12,  7, 25, 15, 28, 33, 41, 1};
	// 共14个
	private static int b[] = {18, 35, 20, 42,  9, 
			   				  31, 23,  6, 48, 11,
							  24, 52, 13,  2 };

    // 验证"基本信息(斐波那契堆的结构)"
	public static void testBasic() {
		FibHeap hb=new FibHeap();

		// 斐波那契堆hb
	    System.out.printf("== 斐波那契堆(hb)中依次添加: ");
		for(int i=0; i<b.length; i++) {
			System.out.printf("%d ", b[i]);
			hb.insert(b[i]);
		}
	    System.out.printf("\n");
		System.out.printf("== 斐波那契堆(hb)删除最小节点\n");
		hb.removeMin();
        hb.print(); // 打印斐波那契堆hb
    }

    // 验证"插入操作"
	public static void testInsert() {
		FibHeap ha=new FibHeap();

		// 斐波那契堆ha
	    System.out.printf("== 斐波那契堆(ha)中依次添加: ");
		for(int i=0; i<a.length; i++) {
			System.out.printf("%d ", a[i]);
			ha.insert(a[i]);
		}
	    System.out.printf("\n");
		System.out.printf("== 斐波那契堆(ha)删除最小节点\n");
		ha.removeMin();
        ha.print(); // 打印斐波那契堆ha

	    System.out.printf("== 插入50\n");
		ha.insert(50);
		ha.print();
    }

    // 验证"合并操作"
    public static void testUnion() {
		FibHeap ha=new FibHeap();
		FibHeap hb=new FibHeap();

		// 斐波那契堆ha
	    System.out.printf("== 斐波那契堆(ha)中依次添加: ");
		for(int i=0; i<a.length; i++) {
			System.out.printf("%d ", a[i]);
			ha.insert(a[i]);
		}
	    System.out.printf("\n");
		System.out.printf("== 斐波那契堆(ha)删除最小节点\n");
		ha.removeMin();
        ha.print(); // 打印斐波那契堆ha

		// 斐波那契堆hb
	    System.out.printf("== 斐波那契堆(hb)中依次添加: ");
		for(int i=0; i<b.length; i++) {
			System.out.printf("%d ", b[i]);
			hb.insert(b[i]);
		}
	    System.out.printf("\n");
		System.out.printf("== 斐波那契堆(hb)删除最小节点\n");
		hb.removeMin();
        hb.print(); // 打印斐波那契堆hb

		// 将"斐波那契堆hb"合并到"斐波那契堆ha"中。
	    System.out.printf("== 合并ha和hb\n");
		ha.union(hb);
		ha.print();
    }

    // 验证"删除最小节点"
    public static void testRemoveMin() {
		FibHeap ha=new FibHeap();
		FibHeap hb=new FibHeap();

		// 斐波那契堆ha
	    System.out.printf("== 斐波那契堆(ha)中依次添加: ");
		for(int i=0; i<a.length; i++) {
			System.out.printf("%d ", a[i]);
			ha.insert(a[i]);
		}
	    System.out.printf("\n");
		System.out.printf("== 斐波那契堆(ha)删除最小节点\n");
		ha.removeMin();
        //ha.print(); // 打印斐波那契堆ha

		// 斐波那契堆hb
	    System.out.printf("== 斐波那契堆(hb)中依次添加: ");
		for(int i=0; i<b.length; i++) {
			System.out.printf("%d ", b[i]);
			hb.insert(b[i]);
		}
	    System.out.printf("\n");
		System.out.printf("== 斐波那契堆(hb)删除最小节点\n");
		hb.removeMin();
        //hb.print(); // 打印斐波那契堆hb

		// 将"斐波那契堆hb"合并到"斐波那契堆ha"中。
	    System.out.printf("== 合并ha和hb\n");
		ha.union(hb);
		ha.print();

	    System.out.printf("== 删除最小节点\n");
		ha.removeMin();
		ha.print();
    }

    // 验证"减小节点"
	public static void testDecrease() {
		FibHeap hb=new FibHeap();

		// 斐波那契堆hb
	    System.out.printf("== 斐波那契堆(hb)中依次添加: ");
		for(int i=0; i<b.length; i++) {
			System.out.printf("%d ", b[i]);
			hb.insert(b[i]);
		}
	    System.out.printf("\n");
		System.out.printf("== 斐波那契堆(hb)删除最小节点\n");
		hb.removeMin();
        hb.print(); // 打印斐波那契堆hb

	    System.out.printf("== 将20减小为2\n");
		hb.update(20, 2);
		hb.print();
    }

    // 验证"增大节点"
	public static void testIncrease() {
		FibHeap hb=new FibHeap();

		// 斐波那契堆hb
	    System.out.printf("== 斐波那契堆(hb)中依次添加: ");
		for(int i=0; i<b.length; i++) {
			System.out.printf("%d ", b[i]);
			hb.insert(b[i]);
		}
	    System.out.printf("\n");
		System.out.printf("== 斐波那契堆(hb)删除最小节点\n");
		hb.removeMin();
        hb.print(); // 打印斐波那契堆hb

	    System.out.printf("== 将20增加为60\n");
		hb.update(20, 60);
		hb.print();
    }

    // 验证"删除节点"
	public static void testDelete() {
		FibHeap hb=new FibHeap();

		// 斐波那契堆hb
	    System.out.printf("== 斐波那契堆(hb)中依次添加: ");
		for(int i=0; i<b.length; i++) {
			System.out.printf("%d ", b[i]);
			hb.insert(b[i]);
		}
	    System.out.printf("\n");
		System.out.printf("== 斐波那契堆(hb)删除最小节点\n");
		hb.removeMin();
        hb.print(); // 打印斐波那契堆hb

	    System.out.printf("== 删除节点20\n");
		hb.remove(20);
		hb.print();
    }

	public static void main(String[] args) {
        // 验证"基本信息(斐波那契堆的结构)"
        testBasic();
        // 验证"插入操作"
        //testInsert();
        // 验证"合并操作"
        //testUnion();
        // 验证"删除最小节点"
        //testRemoveMin();
        // 验证"减小节点"
        //testDecrease();
        // 验证"增大节点"
        //testIncrease();
        // 验证"删除节点"
        //testDelete();
    }
}
