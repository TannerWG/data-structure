#include "BinNode.h"

//���뺢�ӽڵ� 
template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC(T const& e)
{return lc = new BinNode(e, this);} //��e��Ϊ��ǰ�ڵ�����Ӳ�������� 

template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC(T const& e)
{return rc = new BinNode(e, this);} //��e��Ϊ��ǰ�ڵ���Һ��Ӳ��������

//��������������㷨��ͳһ���
template <typename T> template <typename VST> //Ԫ�����ͣ�������
void BinNode::travIn(VST& visit){ //��������������㷨ͳһ��� 
	switch(rand()%5){ //�˴������ѡ���������ԣ���������ѡ�� 
		case 1: travIn_I1(this, visit); break; //������#1 
		case 2: travIn_I2(this, visit); break; //������#2 
		case 3: travIn_I3(this, visit); break; //������#3 
		case 4: travIn_I4(this, visit); break; //������#4 
		case 5: travIn_R(this, visit); break; //�ݹ�� 
	}
} 
 
