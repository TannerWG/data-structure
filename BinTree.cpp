#include "BinTree.h"

//�������ڵ�ĸ߶ȸ��� 
template <typename T> int BinTree<T>::updateHeight(BinNodePosi(T) x)//���½ڵ�x�߶�
{return x->height = 1 + max(stature(x->lc), stature(x->rc));} //��������������� 

template <typename T> void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) //���¸߶�
{while(x){updateHeight(x); x = x->parent;}} //��x�����������������ȡ����Ż�

//�ڵ����
template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e)
{_size = 1; return _root = new BinNode<T>(e);} //��e�������ڵ����յĶ�����

template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e)
{_size++; x->insertAsLC(e); updateHeightAbove(x); return x->lc;} //e����Ϊx������

template<typename T> BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)
{_size++; x->insertAsRC(e); updateHeightAbove(x); return x->rc;} //e����Ϊx��y�Һ���

//��������
template <typename T> //���������������㷨����S�����ڵ�x�����������룬S�����ÿ�
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &S){
	if(x->lc = S->_root) x->lc->parent = x; //���� 
	_size += S->_size; updateHeightAbove(x); //����ȫ����ģ��x�������ȵĸ߶�
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ�� 
} 

//��������
template <typename T> //���������������㷨����S�����ڵ�x�����������룬S�����ÿ�
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &S){
	if(x->rc = S->_root) x->rc->parent = x; //���� 
	_size += S->_size; updateHeightAbove(x); //����ȫ����ģ��x�������ȵĸ߶�
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ�� 
} 

//����������ɾ��
template <typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
int BinTree<T>::remove(BinNodePosi(T) x){ //assert:xΪ�������еĺϷ�λ�� 
	FromParentTo(*x) = NULL; //�ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent); //�������ȸ߶�
	int n = removeAt(x); _size -= n; return n; //ɾ������x�����¹�ģ������ɾ���ڵ����� 
} 
template <typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ�����
static int removeAt(BinNodePosi(T) x){ //assert: xΪ�������еĺϷ�λ�� 
	if(!x) return 0; //�ݹ�������� 
	int n = 1 + removeAt(x->lc) + removeAt(x->rc); //�ݹ��ͷ���������
	release(x->data); release(x); return n; //�ͷű�ժ���ڵ㣬������ɾ���ڵ����� 
} 

//��������
template <typename T> //���������������㷨��������x�ӵ�ǰ����ժ���������װΪһ�ö�����������
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x){ //assert: xΪ�������еĺϷ�λ�� 
	FromParentTo(*x) = NULL; //�ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent); //����ԭ�����������ȵĸ߶�
	BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = NULL; //������xΪ��
	S->_size = x->size(); _size -= S->_size; return S; //���¹�ģ�����ط������������ 
} 

//����������ݹ�棩 
template <typename T, typename VST> //Ԫ�����ͣ�������
void travPre_R(BinNodePosi(T) x, VST& visit){ //��������������㷨���ݹ�棩 
	if(!x) return;
	visit(x->data);
	travPre_R(x->lc);
	travPre_R(x->rc);
} 

//����������ݹ�棩 
template <typename T, typename VST> //Ԫ�����ͣ�������
void travPost_R(BinNodePosi(T) x, VST& visit){ //��������������㷨���ݹ�棩 
	if(!x) return;
	travPost_R(x->lc, visit);
	travPost_R(x->rc, visit);
	visit(x->data);
} 

//����������ݹ�棩
template <typename T, typename VST> //Ԫ�����͡�������
void travIn_P(BinNodePosi(T) x, VST& visit){ //��������������㷨���ݹ�棩 
	if(!x) return;
	travIn_R(x->lc, visit);
	visit(x->data);
	travIn_R(x->rc, visit);
} 

//�ӵ�ǰ�ڵ�����������ҷ�֧�������룬ֱ��û�����ҷ�֧�Ľڵ㣻��;�ڵ��������������� 
template <typename T, typename VST> //Ԫ�����ͣ�������
static void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& S){
	while(x){
		visit(x->data); //���ʵ�ǰ���ӽڵ�
		S.push(x->rc); //�Һ�����ջ�ݴ棨���Ż���ͨ���жϣ�����յ��Һ�����ջ��
		x = x->rc; //�����֧����һ�� 
	}
} 

template<typename T, typename VST> //Ԫ�����͡�������
void travPre_I2(BinNodePosi(T) x, VST& visit){ //��������������㷨��������#2�� 
	Stack<BinNodePosi(T)> S; //����ջ 
	while(true){
		visitAlongLeftBranch(x, visit, S); //�ӵ�ǰ�ڵ��������������
		if(S.empty()) break; //ֱ��ջ��
		x = S.pop(); //������һ������� 
	}
} 

template <typename T> //�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ�
static void goAlongLeftBranch(BinNodePosi(T) x, Stack<BinNodePosi(T)>& S){
	while(x){S.push(x); x=x->lc;} //��ǰ�ڵ���ջ�����������֧���룬����ֱ�������� 
} 

template <typename T, typename VST> //Ԫ�����ͣ�������
void travIn_I1(BinNodePosi(T) x, VST& visit){ //��������������㷨��������#1) 
	Stack<BinNodePosi(T)> S; //��ֵջ  
	while(true){
		goAlongLeftBranch(x, S); //�ӵ�ǰ�ڵ������������ջ
		if(S.empty()) break; //ֱ�����нڵ㴦�����
		x = S.pop(); visit(x->data); //����ջ���ڵ㲢����֮
		x = x->rc; //ת�������� 
	}
} 

//�������ڵ�ֱ�Ӻ�̶�λ
template <typename T> BinNodePosi(T) BinNode<T>::succ(){ //��λ�ڵ�v��ֱ�Ӻ�� 
	BinNodePosi(T) s = this; //��¼��̵���ʱ����
	if(rc){ //�����Һ��ӣ���ֱ�Ӻ�̱����������У�����ؾ��� 
		s = rc; //�������� 
		while(HasLChild(*s)) s = s->lc; //�����С���ؽڵ� 
	} else{ //����ֱ�Ӻ��Ӧ�ǡ�����ǰ�ڵ���������������е�������ȡ�������ؾ��� 
		while(IsRChild(*s)) s = s->parent; //������������֧�����ϳ����Ϸ��ƶ�
		s = s->parent; //����ٳ����Ϸ��ƶ�һ�������ִ�ֱ�Ӻ�̣�������ڣ� 
	}
	return s; 
} 

//��������������㷨��������#2) 
template<typename T, typename VST> //Ԫ�����ͣ�������
void travIn_I2(BinNodePosi(T), VST& visit){ //��������������㷨��������#2) 
	Stack<BinNodePosi(T)> S; //��ֵջ 
	while(true){
		if(x){
			S.push(x); //���ڵ��ջ
			x = x->lc; //������������� 
		}else if{
			x = S.pop(); //��δ���ʵ�������Ƚڵ���ջ
			visit(x->data); //�������Ƚڵ�
			x = x->rc; //�������ȵ������� 
		}else break; //������� 
	}
}  

//����������������������汾#3�����踨��ջ�� 
template<typename T, typename VST> //Ԫ�����ͣ�������
void travIn_I3(BinNodePosi(T) x, VST& visit){ //����������������������汾#3�����踨��ջ�� 
	bool backtrack = false; //ǰһ���Ƿ�մ����������ݡ���ʡȥջ����o(1)�����ռ�
	while(true){
		if(!backtrack && HasLChild(*x)) //�����������Ҳ��Ǹոջ��ݣ���
			x = x->lc; //�������������
		else{ //���򡪡�����������ոջ��ݣ��൱������������ 
			visit(x->data); //���ʸýڵ�
			if(HasRChild(*x)){ //��������Ϊ�ǿգ��� 
				x = x->rc; //������������������ 
				backtrack = false; //���رջ��ݱ�־ 
			}else{ //���������գ��� 
				if(!(x = x->succ())) break; //���ݣ����ִ�ĩ�ڵ�ʱ���˳����أ�
				backtrack = true; //�����û��ݱ�־ 
			}
		} 
	} 
} 

template<typename T> //����Sջ���ڵ�Ϊ���������У��ҵ�������ɼ�Ҷ�ڵ�
static void gotoHLVFL(Stack<BinNodePosi(T)>& S){ //��;�����ڵ�������ջ 
	while(BinNodePosi(T) x = S.top()) //�Զ����£�������鵱ǰ�ڵ㣨��ջ����
		if(HasLChild(*x)){ //�����ܵ����� 
			if(HasRChild(*x)) S.push(x->rc); //�����Һ��ӣ�������ջ
			S.push(x->lc); //Ȼ��ת������ 
		}else //ʵ������ 
			S.push(x->rc); //������ 
	S.pop(); //����֮ǰ������ջ���ؿսڵ� 
} 

//�����ĺ��������������棩
template<typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST& visit){ //�������ĺ��������������棩 
	Stack<BinNodePosi(T)> S; //����ջ
	if(x) S.push(x); //���ڵ���ջ 
	while(!S.empty()){
		if(S.top() != x->parent) //��ջ���ǵ�ǰ�ڵ�֮�������Ϊ�����ֵܣ�����ʱ��
			gotoHLVFL(S); //����������Ϊ��֮�����У��ҵ�HLVFL���൱�ڵݹ��������У� 
		x = S.top(); visit(x->data); //����ջ������ǰһ�ڵ�֮��̣���������֮ 
	}
} 

//��������α����㷨
template <typename T> template <typename VST> //Ԫ�����ͣ�������
void BinNode<T>::travLevel(VST& visit){ //��������α����㷨 
	Queue<BinNodePosi(T)> Q; //��������
	Q.enqueue(this); //���ڵ����
	while(!Q.empty()){ //�ڶ����ٴα��֮ǰ���������� 
		BinNodePosi(T) x = Q.dequeue(); visit(x->data); //ȡ�����׽ڵ㲢����֮
		if(HasLChild(*x)) Q.enqueue(x->lc); //�������
		if(HasRChild(*x)) Q.enqueue(x->rc); //�Һ������ 
	} 
} 










 
