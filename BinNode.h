#define BinNodePosi(T) BinNode<T>* //节点位置
#define stature(p) ((p)?(p)->height : -1) //节点高度
#define enum{RB_RED, RB_BLACK} RBColor; //节点颜色

template <typename T> struct BinNode{ //二叉树节点模板类 
//成员（为简化描述起见统一开放，读者可根据需要进一步封装
	T data; //数值
	BinPosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc; //父节点及左、右孩子
	int height; //高度（通用）
	int npl; //Null Path Length（左式堆，也可以直接用height代替） 
	RBColor color; //颜色（红黑树）
//构造函数
	BinNode():
		parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED){}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED):
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}
//操作接口 
	int size(); //统计当前节点后代总数，以及以其为根的子树的规模 
} 
