/**
 * C 语言: 斜堆
 *
 * @author skywang
 * @date 2014/03/31
 */

#include <iostream>
#include "SkewHeap.h"
using namespace std;

int main()
{
	int i;
	int a[]= {10,40,24,30,36,20,12,16};
	int b[]= {17,13,11,15,19,21,23};
    int alen=sizeof(a)/sizeof(a[0]);
    int blen=sizeof(b)/sizeof(b[0]);
	SkewHeap<int>* ha=new SkewHeap<int>();
	SkewHeap<int>* hb=new SkewHeap<int>();

	cout << "== 斜堆(ha)中依次添加: ";
	for(i=0; i<alen; i++)
	{
		cout << a[i] <<" ";
		ha->insert(a[i]);
	}
	cout << "\n== 斜堆(ha)的详细信息: " << endl;
	ha->print();


	cout << "\n== 斜堆(hb)中依次添加: ";
	for(i=0; i<blen; i++)
	{
		cout << b[i] <<" ";
		hb->insert(b[i]);
	}
	cout << "\n== 斜堆(hb)的详细信息: " << endl;
	hb->print();


	// 将"斜堆hb"合并到"斜堆ha"中。
	ha->merge(hb);
	cout << "\n== 合并ha和hb后的详细信息: " << endl;
	ha->print();


	// 销毁
	ha->destroy();

	return 0;
}
