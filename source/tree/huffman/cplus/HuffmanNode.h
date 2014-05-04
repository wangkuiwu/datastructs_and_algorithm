/**
 * Huffman树节点类
 *
 * @author skywang
 * @date 2014/03/25
 */

#ifndef _HUFFMAN_NODE_HPP_
#define _HUFFMAN_NODE_HPP_

template <class T>
class HuffmanNode{
	public:
		T key;				// 权值
		HuffmanNode *left;	// 左孩子
		HuffmanNode *right;	// 右孩子
		HuffmanNode *parent;// 父结点


		HuffmanNode(){}
		HuffmanNode(T value, HuffmanNode *l, HuffmanNode *r, HuffmanNode *p):
			key(value),left(l),right(r),parent(p) {}
};

#endif
