/**
 * 直接插入排序：Java
 *
 * @author skywang
 * @date 2014/03/11
 */

public class InsertSort {

	/*
	 * 直接插入排序
	 *
	 * 参数说明：
	 *     a -- 待排序的数组
	 *     n -- 数组的长度
	 */
	public static void insertSort(int[] a, int n) {
		int i, j, k;

		for (i = 1; i < n; i++) {

			//为a[i]在前面的a[0...i-1]有序区间中找一个合适的位置
			for (j = i - 1; j >= 0; j--)
				if (a[j] < a[i])
					break;

			//如找到了一个合适的位置
			if (j != i - 1) {
				//将比a[i]大的数据向后移
				int temp = a[i];
				for (k = i - 1; k > j; k--)
					a[k + 1] = a[k];
				//将a[i]放到正确位置上
				a[k + 1] = temp;
			}
		}
	}

	public static void main(String[] args) {
		int i;
		int[] a = {20,40,30,10,60,50};

		System.out.printf("before sort:");
		for (i=0; i<a.length; i++)
			System.out.printf("%d ", a[i]);
		System.out.printf("\n");

		insertSort(a, a.length);

		System.out.printf("after  sort:");
		for (i=0; i<a.length; i++)
			System.out.printf("%d ", a[i]);
		System.out.printf("\n");
	}
}
