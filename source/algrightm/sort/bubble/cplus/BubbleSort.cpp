/**
 * 冒泡排序：C++
 *
 * @author skywang
 * @date 2014/03/11
 */

#include <iostream>
using namespace std;

/*
 * 冒泡排序
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     n -- 数组的长度
 */
void bubbleSort1(int* a, int n)
{
	int i,j,tmp;

	for (i=n-1; i>0; i--)
	{
        // 将a[0...i]中最大的数据放在末尾
		for (j=0; j<i; j++)
		{
			if (a[j] > a[j+1])
			{	
				// 交换a[j]和a[j+1]
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}
	}
}

/*
 * 冒泡排序(改进版)
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     n -- 数组的长度
 */
void bubbleSort2(int* a, int n)
{
	int i,j,tmp;
	int flag; 				// 标记

	for (i=n-1; i>0; i--)
	{
		flag = 0;			// 初始化标记为0

        // 将a[0...i]中最大的数据放在末尾
		for (j=0; j<i; j++)
		{
			if (a[j] > a[j+1])
			{
				// 交换a[j]和a[j+1]
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;

				flag = 1;	// 若发生交换，则设标记为1
			}
		}

		if (flag==0)
			break;			// 若没发生交换，则说明数列已有序。
	}
}

int main()
{
	int i;
	int a[] = {20,40,30,10,60,50};
	int ilen = (sizeof(a)) / (sizeof(a[0]));

	cout << "before sort:";
	for (i=0; i<ilen; i++)
		cout << a[i] << " ";
	cout << endl;

	bubbleSort1(a, ilen);
	//bubbleSort2(a, ilen);

	cout << "after  sort:";
	for (i=0; i<ilen; i++)
		cout << a[i] << " ";
	cout << endl;

	return 0;
}
