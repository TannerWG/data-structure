#include "BinNode.h"
#define BinNodePosi(T) BinNode<T>* //节点位置
#define stature(p) ((p)?(p)->height : -1) //节点高度
#define enum{RB_RED, RB_BLACK} RBColor; //节点颜色

//二叉树模板类BinTree 
template <typename T> class BinTree{ //二叉树模板类
protected:
	int _size; BinNodePosi(T) _root; //规模、根节点
	virtual int updateHeight(BinNodePosi(T) x); //更新节点x的高度
	void updateHeightAbove(BinNodePosi(T) x); //更新节点x及其祖先的高度
public:
	BinTree() : _size(0), _root(NULL){} //构造函数
	~BinTree() {if(0 < _size) remove(_root);} //析构函数
	int size() const {return _size;} //规模
	bool empty() const {return !_root;} //判空
	BinNodePosi(T) root() const {return _root;} //树根
	BinNodePosi(T) insertAsRoot(T const& e); //插入根节点
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e); //e作为x的左孩子（原无）插入
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e); //e作为x的右孩子（原无）插入
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &T); //T作为x的左子树接入
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &T); //T作为x的右子树接入
	int remove(BinNodePosi(T) x); //删除以位置x处节点为根的子树，返回该子树原先的规模
	BinTree<T>* secede(BinNodePosi(T) x); //将子树x从当前树中摘除，并将其转换为一颗独立子树
	template<typename VST> //操作器
	void travLevel(VST& visit){if(_root) _root->travLevel(visit);} //层次遍历
	template <typename VST> //操作器
	void travPre(VST& visit){if(_root) _root->travPre(visit);} //先序遍历
	template <typename VST> //操作器
	void travIn(VST& visit){if(_root) _root->travIn(visit);} //中序遍历
	template <typename VST> //操作器
	void travPost(VST& visit){if(_root) _root->travPost(visit);} //后序遍历
	bool operator < (BinTree<T> const& t) //比较器
	{return _root && t._root && lt(_root, t._root);}
	bool operator > (BinTree<T> const& t) //比较器
	{return _root && t._root && lt(t._root, _root);}  
	bool operator == (BinTree<T> const& t) //判等器
	{return _root && t._root && (_root == t._root);} 
};
