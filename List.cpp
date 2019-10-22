#include "List.h"
#define ListNodePosi(T) ListNode<T>*
typedef int Rank;


//�б����ڲ�����init() 
template<typename T> void List<T>::init(){ //�б�ʼ�����ڴ����б����ʱͳһ����
    header = new ListNode<T>; //����ͷ�ڱ��ڵ�
	trailer = new ListNode<T>; //����β�ڱ��ڵ�
	header->succ = trailer; header->pred = NULL;
	trailer->pred = header; trailer->succ = NULL;
	_size = 0; 
}

//�����б����±������
template<typename T>  //�����±����������ͨ����ֱ�ӷ����б�ڵ㣨�䷽�㣬Ч�ʵͣ����ã� 
T& List<T>::operator[](Rank r) const{
	ListNodePosi(T) p = first(); //���׽ڵ����
	while(0<r--){
		p = p->succ; //˳����r���ڵ㼴�� 
	} 
	return p->data;
} 

//�����б�Ԫ�ز��ҽӿ�
template<typename T>  //�������б��ڽڵ�p��������trailer����n�����棩ǰ���У��ҵ�����e�������
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const{
	while(0<n--){ //
		if(e == (p = p->pred)->data) return p; //����ȶԣ�ֱ�����л�ΧԽ�� 
	}
	return NULL; 
} 

//�б�ڵ�������
template<typename T> ListNodePosi(T) List<T>::insertAsFirst(T const& e){
	_size++; return header->insertAsSucc(e);
} 

template<typename T> ListNodePosi(T) List<T>::insertAsLast(T const& e){
	_size++; return trailer->insertAsPred(e);
}

template<typename T> ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, T const& e){
	_size++; return p->insertAsSucc(e);
}

template<typename T> ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, T const& e){
	_size++; return p->insertAsPred(e);
}

//�ڵ�ǰ���� 
template<typename T> //��e������ǰ�ڵ�֮ǰ���뵱ǰ�ڵ��������б�����ͷ�ڱ��ڵ�header) 
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e){
	ListNodePosi(T) x = new ListNode(e, pred, this); //�����½ڵ�
	pred->succ = x; pred = x; //������������
	return x; 
} 

//�ڵ�����
template<typename T> // ��e���浱ǰ�ڵ�֮����뵱ǰ�ڵ��������б�����β�ڱ��ڵ�trailer) 
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e){
	ListNodePosi(T) x = new ListNode(e, this, succ);
	succ->pred = x; succ = x;
	return x;
}

template<typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n){ //p�Ϸ�����������n-1��������ڵ� 
	init(); //����ͷβ�ڱ��ڵ㲢����ʼ�� 
	while(n--){
		insertAsLast(p->data); 
		p=p->succ;
	}
} 

template<typename T> //�����б�����λ��p���n�assert:pΪ�Ϸ�λ�ã���������n-1����̽ڵ㣩
List<T>::List(ListNodePosi(T) p, int n) {copyNodes(p, n);}

template<typename T> //���帴���б�
List<T>::List(List<T> const& L) {copyNodes(L.first(), L._size);}

template<typename T> //����L���Ե�r�����n�assert: r+n <= L._size)
List<T>::List(List<T> const& L, int r, int n){copyNodes(L[r], n);}

template<typename T> //ɾ���Ϸ��ڵ�p����������ֵ
T List<T>::remove(ListNodePosi(T) p){
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p; _size--;
	return e;
} 

template<typename T> List<T>::~List(){ //�б������� 
	clear(); delete header; delete trailer; //����б��ͷ�ͷβ�ڱ��ڵ� 
} 

template<typename T> int List<T>::clear(){ //����ɾ���׽ڵ㣬ֱ���б��� 
	int oldSize = _size;
	while(0 < _size) remove(header->succ); //����ɾ���׽ڵ㣬ֱ���б���
	return oldSize; 
} 

template<typename T> int List<T>::duplicate(){ //�޳������б��е��ظ��ڵ� 
	if(_size < 2) return 0; //ƽ���б���Ȼ���ظ� 
	int oldSize = _size; //��¼ԭ��ģ 
	ListNodePosi(T) p = header; Rank r = 0; //p���׽ڵ㿪ʼ 
	while(trailer != (p = p->succ)){ //����ֱ��ĩ�ڵ� 
		ListNodePosi(T) q = find(p->data, r, p); //��p��r�����棩ǰ���в�����ͬ�� 
		q ? remove(q) : r++;  //�����ڣ���ɾ��֮�������ȼ�1 
	} //������ʱ�̣�p��ǰ��������ͬ 
	return oldSize-_size();
}

//�б����
template<typename T> template<typename VST> //Ԫ�����ͣ�������
void List<T>::traverse(VST& visit) { //������������������Ʊ���
	for(ListNodePosi(T) p = header->succ; p!=trailer; p=p->succ) visit(p->data);
} 

//�����б������ 
template<typename T> int List<T>::uniquify(){ //�����޳��ظ�Ԫ�أ�Ч�ʸ��� 
	if(_size < 2) return 0; //ƽ���б���Ȼ���ظ� 
	int oldSize = _size;
	ListNodePosi(T) p = first(); ListNodePosi(T) q; //pΪ��������㣬qΪ����
	while(trailer != (q=q->succ)){ //����������ڵĽڵ�ԣ�p, q)
		if(p->data != q->data) p = q;
		else remove(q);
	} 
	return oldSize - _size;
}
 
//�����б�Ĳ��� 
template<typename T> //�������б��ڽڵ�p(������trailer)��n�����棩ǰ���У��ҵ�������e�ĵ������
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const{
//assert: 0 <= n <= rank(p) < _size
    while(0 < n--){ //����p�������n��ǰ�������ҵ�������Ƚ� 
    	if(((p = p->pred)->data) <= e) break; //ֱ�����У���ֵԽ����߷�ΧԽ�� 
	} 
//assert: ����λ��p�ط����������Լ�������������һ�ιؼ���ȽϿ���û�����壨��Ч����-inf���Ƚϣ� 
	return p; //������ֹλ�� 
} 

//������ͳһ���
template<typename T> void List<T>::sort(ListNodePosi(T) p, int n){ //�б��������� 
	switch(rand() % 3){
		case 1: insertionSort(p, n); break; //�������� 
		case 2: selectionSort(p, n); break; //ѡ������ 
		default: mergeSort(p, n); break; //�鲢���� 
	}
} 

//��������
template<typename T> //�б�Ĳ��������㷨������ʼλ��p��n��Ԫ������
void List<T>::insertionSort(ListNodePosi(T) p, int n){
	for(int r=0; r<n; r++){
		insertA(search(p->data, r, p), p->data); //�����ʵ�λ�ò�����
		p = p->succ; remove(p->pred); //ת����һ�ڵ� 
	}
} 

//ѡ������
template<typename T> //�б��ѡ�������㷨������ʼ��λ��p��n��Ԫ������
void List<T>::selectionSort(ListNodePosi(T) p, int n){ //valid(p) && rank(p)+n<=size 
	ListNodePosi(T) head = p->pred; ListNodePosi(T) tail=p;
	for(int i=0; i<n; i++) tail = tail->succ; //����������Ϊ(head, tail)
	while(1<n){ // ���ٻ�ʣ�����ڵ�֮ǰ���ڴ����������� 
		ListNodePosi(T) max = selectMax(head->succ, n); //�ҳ������
		insertB(tail, remove(max)); //�����ƶ�����������ĩβ
		tail = tail->pred; n--; 
	} 
} 

//�ҳ������
template<typename T> //����ʼλ��p��n�������ѡ�������
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n){
	ListNodePosi(T) max = p; //������ݶ�Ϊ�׽ڵ�p
	for(ListNodePosi(T) cur = p; 1 < n; n--){
		if(!lt((cur=cur->succ)->data, max->data)) //����ǰԪ�ز�С��max
		    max = cur; 
	} 
	return max;
} 

//�鲢
template<typename T> //�����б�Ĺ鲢����ǰ�б�����p���n��Ԫ�أ����б�L����q���m��Ԫ�ع鲢
void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m){
	ListNodePosi(T) pp = p->pred; //����ǰ����������header)���Ա㷵��ǰ...
	while(0<m){
		if((0<n)&&(p->data <= q->data)) //��p������������v(p) <= v(q), ��
		{if(q==(p=p->succ)) break; n--;}
		else //���ѳ����ҽ��v(q) < v(p)����
		{insertB(p, L.remove((q=q->succ)->pred)); m++;} //��qת����p֮ǰ 
	} 
	p = pp->succ; //ȷ���鲢�����䣨�£���� 
} 

//�鲢����
template<typename T> //�б�Ĺ鲢�����㷨������ʼ��λ��p��n��Ԫ������
void List<T>::mergeSort(ListNodePosi(T)& p, int n){ //valid(p) && rank(p) + n <= size 
	if(n<2) return;
	int m = n>>1; //���е�Ϊ��
	ListNodePosi(T) q = p;
	for(int i=0; i<m; i++) q = q->succ; //�����б�
	mergeSort(p, m);
	mergeSort(q, n-m); // ��ǰ�������б�ֱ�����
	merge(p, m, *this, q, n-m); //�鲢                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
} //ע�⣺�����p��Ȼָ��鲢������ģ��£���� 

