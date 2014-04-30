/**
 * Java 语言: 左倾堆
 *
 * @author skywang
 * @date 2014/03/31
 */

public class LeftistHeapTest {

	public static void main(String[] args) {
	    int a[]= {10,40,24,30,36,20,12,16};
	    int b[]= {17,13,11,15,19,21,23};
		LeftistHeap<Integer> ha=new LeftistHeap<Integer>();
		LeftistHeap<Integer> hb=new LeftistHeap<Integer>();

	    System.out.printf("== 左倾堆(ha)中依次添加: ");
		for(int i=0; i<a.length; i++) {
			System.out.printf("%d ", a[i]);
			ha.insert(a[i]);
		}
	    System.out.printf("\n== 左倾堆(ha)的详细信息: \n");
		ha.print();


        System.out.printf("\n== 左倾堆(hb)中依次添加: ");
        for(int i=0; i<b.length; i++) {
            System.out.printf("%d ", b[i]);
            hb.insert(b[i]);
        }
        System.out.printf("\n== 左倾堆(hb)的详细信息: \n");
		hb.print();

        // 将"左倾堆hb"合并到"左倾堆ha"中。
        ha.merge(hb);
        System.out.printf("\n== 合并ha和hb后的详细信息: \n");
		ha.print();
    }
}

