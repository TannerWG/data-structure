#define BinNodePosi(T) BinNode<T>* //�ڵ�λ��
#define stature(p) ((p)?(p)->height : -1) //�ڵ�߶�
#define enum{RB_RED, RB_BLACK} RBColor; //�ڵ���ɫ

//�������ڵ�ģ���� 
template <typename T> struct BinNode{ //�������ڵ�ģ���� 
//��Ա��Ϊ���������ͳһ���ţ����߿ɸ�����Ҫ��һ����װ
	T data; //��ֵ
	BinPosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc; //���ڵ㼰���Һ���
	int height; //�߶ȣ�ͨ�ã�
	int npl; //Null Path Length����ʽ�ѣ�Ҳ����ֱ����height���棩 
	RBColor color; //��ɫ���������
//���캯��
	BinNode():
		parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED){}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED):
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}
//�����ӿ� 
	int size(); //ͳ�Ƶ�ǰ�ڵ����������Լ�����Ϊ���������Ĺ�ģ 
	BinNodePosi(T) insertAsLC(T const&); //��Ϊ��ǰ�ڵ�����ӽڵ�����½ڵ�
	BinNodePosi(T) insertAsRC(T const&); //��Ϊ��ǰ�ڵ���Һ��ӽڵ�����½ڵ�
	BinNodePosi(T) succ(); //ȡ��ǰ�ڵ��ֱ�Ӻ��
	template <typename VST> void travLevel(VST&); //������α���
	template <typename VST> void travPre(VST&); //�����������
	template <typename VST> void travIn(VST&); //�����������
	template <typename VST> void travPost(VST&); //�����������
//�Ƚ������е�����������һ���������в��䣩 
	bool operator < (BinNode const& bn) {return data < bn.data;} //С��
	bool operator > (BinNode const& bn) {return data > bn.data;} //����
	bool operator <= (BinNode const& bn) {return data <= bn.data;} //С�ڵ��� 
	bool operator >= (BinNode const& bn) {return data >= bn.data;} //���ڵ��� 
	bool operator == (BinNode const& bn) {return data == bn.data;} //���� 
	bool operator != (BinNode const& bn) {return data != bn.data;} //������ 
}; 

//�Ժ����ʽ�Ի���BinNode�Ĳ�����һ�������� 
/**********************************************************************************************************************************
* BinNode״̬�����ʵ��ж�
***********************************************************************************************************************************/
#define IsRoot(x) (!(x).parent)
#define IsLChild(x) (!IsRoot(x)&&(&(x)==(x).parent->lc))
#define IsRChild(x) (!IsRoot(x)&&(&(x)==(x).parent->rc)) 
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x)) //����ӵ��һ������
#define HasBothChild(x) (HasLChild(x) && HasRChild(x)) //ͬʱӵ����������
#define IsLeaf(x) (!HasChild(x))

/**********************************************************************************************************************************
* ��BinNode�����ض���ϵ�Ľڵ㼰ָ�� 
***********************************************************************************************************************************/
#define sibling(p) /*�ֵ�*/ \
	(IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc) 

#define uncle(x) /*����*/\
	(IsLChild(*((x)->parent)) ? (x)->parent->parent->rc : (x).parent->parent->lc) 

#define FromParentTo(x) /*���Ը��׵�����*/ \
	(IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc)) 
 


