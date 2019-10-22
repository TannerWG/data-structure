#define BinNodePosi(T) BinNode<T>* //�ڵ�λ��
#define stature(p) ((p)?(p)->height : -1) //�ڵ�߶�
#define enum{RB_RED, RB_BLACK} RBColor; //�ڵ���ɫ

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
} 
