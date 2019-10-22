#include "BinNode.h"
#define BinNodePosi(T) BinNode<T>* //�ڵ�λ��
#define stature(p) ((p)?(p)->height : -1) //�ڵ�߶�
#define enum{RB_RED, RB_BLACK} RBColor; //�ڵ���ɫ

//������ģ����BinTree 
template <typename T> class BinTree{ //������ģ����
protected:
	int _size; BinNodePosi(T) _root; //��ģ�����ڵ�
	virtual int updateHeight(BinNodePosi(T) x); //���½ڵ�x�ĸ߶�
	void updateHeightAbove(BinNodePosi(T) x); //���½ڵ�x�������ȵĸ߶�
public:
	BinTree() : _size(0), _root(NULL){} //���캯��
	~BinTree() {if(0 < _size) remove(_root);} //��������
	int size() const {return _size;} //��ģ
	bool empty() const {return !_root;} //�п�
	BinNodePosi(T) root() const {return _root;} //����
	BinNodePosi(T) insertAsRoot(T const& e); //������ڵ�
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e); //e��Ϊx�����ӣ�ԭ�ޣ�����
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e); //e��Ϊx���Һ��ӣ�ԭ�ޣ�����
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &T); //T��Ϊx������������
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &T); //T��Ϊx������������
	int remove(BinNodePosi(T) x); //ɾ����λ��x���ڵ�Ϊ�������������ظ�����ԭ�ȵĹ�ģ
	BinTree<T>* secede(BinNodePosi(T) x); //������x�ӵ�ǰ����ժ����������ת��Ϊһ�Ŷ�������
	template<typename VST> //������
	void travLevel(VST& visit){if(_root) _root->travLevel(visit);} //��α���
	template <typename VST> //������
	void travPre(VST& visit){if(_root) _root->travPre(visit);} //�������
	template <typename VST> //������
	void travIn(VST& visit){if(_root) _root->travIn(visit);} //�������
	template <typename VST> //������
	void travPost(VST& visit){if(_root) _root->travPost(visit);} //�������
	bool operator < (BinTree<T> const& t) //�Ƚ���
	{return _root && t._root && lt(_root, t._root);}
	bool operator > (BinTree<T> const& t) //�Ƚ���
	{return _root && t._root && lt(t._root, _root);}  
	bool operator == (BinTree<T> const& t) //�е���
	{return _root && t._root && (_root == t._root);} 
};