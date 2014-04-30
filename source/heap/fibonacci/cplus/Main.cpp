/**
 * C 语言: 斐波那契堆
 *
 * @author skywang
 * @date 2014/04/06
 */

#include <iostream>
#include "FibHeap.h"
using namespace std;

#define DEBUG 0

// 共8个
int a[] = {12,  7, 25, 15, 28, 
		   33, 41,  1};
// 共14个
int b[] = {18, 35, 20, 42,  9, 
		   31, 23,  6, 48, 11, 
		   24, 52, 13,  2};

// 验证"基本信息(斐波那契堆的结构)"
void testBasic()
{
	int i;
    int blen=sizeof(b)/sizeof(b[0]);
	FibHeap<int>* hb=new FibHeap<int>();

	// 斐波那契堆hb
	cout << "== 斐波那契堆(hb)中依次添加: ";
	for(i=0; i<blen; i++)
	{
		cout << b[i] <<" ";
		hb->insert(b[i]);
	}
	cout << endl;
	cout << "== 斐波那契堆(hb)删除最小节点" << endl;
	hb->removeMin();
	hb->print();
}

// 验证"插入操作"
void testInsert()
{
	int i;
    int alen=sizeof(a)/sizeof(a[0]);
	FibHeap<int>* ha=new FibHeap<int>();

	cout << "== 斐波那契堆(ha)中依次添加: ";
	for(i=0; i<alen; i++)
	{
		cout << a[i] <<" ";
		ha->insert(a[i]);
	}
	cout << endl;
	cout << "== 斐波那契堆(ha)删除最小节点" << endl;
	ha->removeMin();
	ha->print();

	// 斐波那契堆hb
	cout << "== 插入50" << endl;
	ha->insert(50);
	ha->print();
}

// 验证"合并操作"
void testUnion()
{
	int i;
    int alen=sizeof(a)/sizeof(a[0]);
    int blen=sizeof(b)/sizeof(b[0]);
	FibHeap<int>* ha=new FibHeap<int>();
	FibHeap<int>* hb=new FibHeap<int>();

	cout << "== 斐波那契堆(ha)中依次添加: ";
	for(i=0; i<alen; i++)
	{
		cout << a[i] <<" ";
		ha->insert(a[i]);
	}
	cout << endl;
	cout << "== 斐波那契堆(ha)删除最小节点" << endl;
	ha->removeMin();
	ha->print();

	// 斐波那契堆hb
	cout << "== 斐波那契堆(hb)中依次添加: ";
	for(i=0; i<blen; i++)
	{
		cout << b[i] <<" ";
		hb->insert(b[i]);
	}
	cout << endl;
	cout << "== 斐波那契堆(hb)删除最小节点" << endl;
	hb->removeMin();
	hb->print();

	// 将"斐波那契堆hb"合并到"斐波那契堆ha"中。
	cout << "== 合并ha和hb" << endl;
	ha->combine(hb);
	ha->print();
}

// 验证"删除最小节点"
void testRemoveMin()
{
	int i;
    int alen=sizeof(a)/sizeof(a[0]);
    int blen=sizeof(b)/sizeof(b[0]);
	FibHeap<int>* ha=new FibHeap<int>();
	FibHeap<int>* hb=new FibHeap<int>();

	cout << "== 斐波那契堆(ha)中依次添加: ";
	for(i=0; i<alen; i++)
	{
		cout << a[i] <<" ";
		ha->insert(a[i]);
	}
	cout << endl;
	cout << "== 斐波那契堆(ha)删除最小节点" << endl;
	ha->removeMin();
	//ha->print();

	// 斐波那契堆hb
	cout << "== 斐波那契堆(hb)中依次添加: ";
	for(i=0; i<blen; i++)
	{
		cout << b[i] <<" ";
		hb->insert(b[i]);
	}
	cout << endl;
	cout << "== 斐波那契堆(hb)删除最小节点" << endl;
	hb->removeMin();
	//hb->print();

	// 将"斐波那契堆hb"合并到"斐波那契堆ha"中。
	cout << "== 合并ha和hb" << endl;
	ha->combine(hb);
	ha->print();


	cout << "== 删除最小节点" << endl;
    ha->removeMin();
	ha->print();
}

// 验证"减小节点"
void testDecrease()
{
	int i;
    int blen=sizeof(b)/sizeof(b[0]);
	FibHeap<int>* hb=new FibHeap<int>();

	// 斐波那契堆hb
	cout << "== 斐波那契堆(hb)中依次添加: ";
	for(i=0; i<blen; i++)
	{
		cout << b[i] <<" ";
		hb->insert(b[i]);
	}
	cout << endl;
	cout << "== 斐波那契堆(hb)删除最小节点" << endl;
	hb->removeMin();
	hb->print();

	cout << "== 将20减小为2" << endl;
	hb->update(20, 2);
	hb->print();
}

// 验证"增大节点"
void testIncrease()
{
	int i;
    int blen=sizeof(b)/sizeof(b[0]);
	FibHeap<int>* hb=new FibHeap<int>();

	// 斐波那契堆hb
	cout << "== 斐波那契堆(hb)中依次添加: ";
	for(i=0; i<blen; i++)
	{
		cout << b[i] <<" ";
		hb->insert(b[i]);
	}
	cout << endl;
	cout << "== 斐波那契堆(hb)删除最小节点" << endl;
	hb->removeMin();
	hb->print();

	cout << "== 将20增加为60" << endl;
	hb->update(20, 60);
	hb->print();
}

// 验证"删除节点"
void testDelete()
{
	int i;
    int blen=sizeof(b)/sizeof(b[0]);
	FibHeap<int>* hb=new FibHeap<int>();

	// 斐波那契堆hb
	cout << "== 斐波那契堆(hb)中依次添加: ";
	for(i=0; i<blen; i++)
	{
		cout << b[i] <<" ";
		hb->insert(b[i]);
	}
	cout << endl;
	cout << "== 斐波那契堆(hb)删除最小节点" << endl;
	hb->removeMin();
	hb->print();

	cout << "== 删除节点20" << endl;
	hb->remove(20);
	hb->print();
}

int main()
{
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

	return 0;
}

