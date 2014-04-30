/**
 * Java 语言: 二项堆
 *
 * @author skywang
 * @date 2014/03/31
 */

public class Main {

	private static final boolean DEBUG = false;

	// 共7个 = 1+2+4
	private static int a[] = {12,  7, 25, 15, 28, 33, 41};
	// 共13个 = 1+4+8
	private static int b[] = {18, 35, 20, 42,  9, 
			   31, 23,  6, 48, 11, 
			   24, 52, 13 };


	// 验证"二项堆的插入操作"
	public static void testInsert() {
		BinomialHeap<Integer> ha=new BinomialHeap<Integer>();

		// 二项堆ha
	    System.out.printf("== 二项堆(ha)中依次添加: ");
		for(int i=0; i<a.length; i++) {
			System.out.printf("%d ", a[i]);
			ha.insert(a[i]);
		}
	    System.out.printf("\n");
		System.out.printf("== 二项堆(ha)的详细信息: \n");
		ha.print();
    }

	// 验证"二项堆的合并操作"
	public static void testUnion() {
		BinomialHeap<Integer> ha=new BinomialHeap<Integer>();
		BinomialHeap<Integer> hb=new BinomialHeap<Integer>();

		// 二项堆ha
	    System.out.printf("== 二项堆(ha)中依次添加: ");
		for(int i=0; i<a.length; i++) {
			System.out.printf("%d ", a[i]);
			ha.insert(a[i]);
		}
	    System.out.printf("\n");
		System.out.printf("== 二项堆(ha)的详细信息: \n");
		ha.print();

		// 二项堆hb
	    System.out.printf("== 二项堆(hb)中依次添加: ");
		for(int i=0; i<b.length; i++) {
			System.out.printf("%d ", b[i]);
			hb.insert(b[i]);
		}
	    System.out.printf("\n");
		// 打印二项堆hb
		System.out.printf("== 二项堆(hb)的详细信息: \n");
		hb.print();

		// 将"二项堆hb"合并到"二项堆ha"中。
		ha.union(hb);
		// 打印二项堆ha的详细信息
		System.out.printf("== 合并ha和hb后的详细信息:\n");
		ha.print();
    }

	// 验证"二项堆的删除操作"
	public static void testDelete() {
		BinomialHeap<Integer> hb=new BinomialHeap<Integer>();

		// 二项堆hb
	    System.out.printf("== 二项堆(hb)中依次添加: ");
		for(int i=0; i<b.length; i++) {
			System.out.printf("%d ", b[i]);
			hb.insert(b[i]);
		}
	    System.out.printf("\n");
		// 打印二项堆hb
		System.out.printf("== 二项堆(hb)的详细信息: \n");
		hb.print();

		// 将"二项堆hb"合并到"二项堆ha"中。
		hb.remove(20);
		System.out.printf("== 删除节点20后的详细信息: \n");
		hb.print();
    }

	// 验证"二项堆的更新(减少)操作"
	public static void testDecrease() {
		BinomialHeap<Integer> hb=new BinomialHeap<Integer>();

		// 二项堆hb
	    System.out.printf("== 二项堆(hb)中依次添加: ");
		for(int i=0; i<b.length; i++) {
			System.out.printf("%d ", b[i]);
			hb.insert(b[i]);
		}
	    System.out.printf("\n");
		// 打印二项堆hb
		System.out.printf("== 二项堆(hb)的详细信息: \n");
		hb.print();

		// 将节点20更新为2
		hb.update(20, 2);
		System.out.printf("== 更新节点20->2后的详细信息: \n");
		hb.print();
    }

	// 验证"二项堆的更新(减少)操作"
	public static void testIncrease() {
		BinomialHeap<Integer> hb=new BinomialHeap<Integer>();

		// 二项堆hb
	    System.out.printf("== 二项堆(hb)中依次添加: ");
		for(int i=0; i<b.length; i++) {
			System.out.printf("%d ", b[i]);
			hb.insert(b[i]);
		}
	    System.out.printf("\n");
		// 打印二项堆hb
		System.out.printf("== 二项堆(hb)的详细信息: \n");
		hb.print();

		// 将节点6更新为60
		hb.update(6, 60);
		System.out.printf("== 更新节点6->60后的详细信息: \n");
		hb.print();
    }

	public static void main(String[] args) {
		// 1. 验证"二项堆的插入操作"
		testInsert();
		// 2. 验证"二项堆的合并操作"
		//testUnion();
		// 3. 验证"二项堆的删除操作"
		//testDelete();
		// 4. 验证"二项堆的更新(减少)操作"
		//testDecrease();
		// 5. 验证"二项堆的更新(增加)操作"
		//testIncrease();
    }
}

