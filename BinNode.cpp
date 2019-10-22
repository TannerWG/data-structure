#include "BinNode.h"

//插入孩子节点 
template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC(T const& e)
{return lc = new BinNode(e, this);} //将e作为当前节点的左孩子插入二叉树 

template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC(T const& e)
{return rc = new BinNode(e, this);} //将e作为当前节点的右孩子插入二叉树

//二叉树中序遍历算法的统一入口
template <typename T> template <typename VST> //元素类型，操作器
void BinNode::travIn(VST& visit){ //二叉树中序遍历算法统一入口 
	switch(rand()%5){ //此处暂随机选择以作测试，共有五种选择 
		case 1: travIn_I1(this, visit); break; //迭代版#1 
		case 2: travIn_I2(this, visit); break; //迭代版#2 
		case 3: travIn_I3(this, visit); break; //迭代版#3 
		case 4: travIn_I4(this, visit); break; //迭代版#4 
		case 5: travIn_R(this, visit); break; //递归版 
	}
} 
 
