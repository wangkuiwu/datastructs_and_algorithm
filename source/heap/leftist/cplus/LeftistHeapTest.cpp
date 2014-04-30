/**
 * C 语言: 左倾堆
 *
 * @author skywang
 * @date 2013/11/07
 */

#include <iostream>
#include "LeftistHeap.h"
using namespace std;

int main()
{
	int i;
	int a[]= {10,40,24,30,36,20,12,16};
	int b[]= {17,13,11,15,19,21,23};
    int alen=sizeof(a)/sizeof(a[0]);
    int blen=sizeof(b)/sizeof(b[0]);
	LeftistHeap<int>* ha=new LeftistHeap<int>();
	LeftistHeap<int>* hb=new LeftistHeap<int>();

	cout << "== 左倾堆(ha)中依次添加: ";
	for(i=0; i<alen; i++)
	{
		cout << a[i] <<" ";
		ha->insert(a[i]);
	}
	cout << "\n== 左倾堆(ha)的详细信息: " << endl;
	ha->print();


	cout << "\n== 左倾堆(hb)中依次添加: ";
	for(i=0; i<blen; i++)
	{
		cout << b[i] <<" ";
		hb->insert(b[i]);
	}
	cout << "\n== 左倾堆(hb)的详细信息: " << endl;
	hb->print();


	// 将"左倾堆hb"合并到"左倾堆ha"中。
	ha->merge(hb);
	cout << "\n== 合并ha和hb后的详细信息: " << endl;
	ha->print();


	// 销毁
	ha->destroy();

	return 0;
}
