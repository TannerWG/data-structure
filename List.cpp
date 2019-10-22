#include "List.h"
#define ListNodePosi(T) ListNode<T>*
typedef int Rank;


//列表类内部方法init() 
template<typename T> void List<T>::init(){ //列表始化，在创建列表对象时统一调用
    header = new ListNode<T>; //创建头哨兵节点
	trailer = new ListNode<T>; //创建尾哨兵节点
	header->succ = trailer; header->pred = NULL;
	trailer->pred = header; trailer->succ = NULL;
	_size = 0; 
}

//重载列表类下标操作符
template<typename T>  //重载下标操作符，以通过秩直接访问列表节点（虽方便，效率低，慎用） 
T& List<T>::operator[](Rank r) const{
	ListNodePosi(T) p = first(); //从首节点出发
	while(0<r--){
		p = p->succ; //顺数第r个节点即是 
	} 
	return p->data;
} 

//无序列表元素查找接口
template<typename T>  //在无序列表内节点p（可能是trailer）的n个（真）前驱中，找到等于e的最后者
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const{
	while(0<n--){ //
		if(e == (p = p->pred)->data) return p; //逐个比对，直至命中或范围越界 
	}
	return NULL; 
} 

//列表节点插入入口
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

//节点前插入 
template<typename T> //将e紧靠当前节点之前插入当前节点所属的列表（设有头哨兵节点header) 
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e){
	ListNodePosi(T) x = new ListNode(e, pred, this); //创建新节点
	pred->succ = x; pred = x; //设置正向链接
	return x; 
} 

//节点后插入
template<typename T> // 将e紧随当前节点之后插入当前节点所属的列表（设有尾哨兵节点trailer) 
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e){
	ListNodePosi(T) x = new ListNode(e, this, succ);
	succ->pred = x; succ = x;
	return x;
}

template<typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n){ //p合法，且至少有n-1个真后续节点 
	init(); //创建头尾哨兵节点并做初始化 
	while(n--){
		insertAsLast(p->data); 
		p=p->succ;
	}
} 

template<typename T> //复制列表中自位置p起的n项（assert:p为合法位置，且至少有n-1个后继节点）
List<T>::List(ListNodePosi(T) p, int n) {copyNodes(p, n);}

template<typename T> //整体复制列表
List<T>::List(List<T> const& L) {copyNodes(L.first(), L._size);}

template<typename T> //复制L中自第r项起的n项（assert: r+n <= L._size)
List<T>::List(List<T> const& L, int r, int n){copyNodes(L[r], n);}

template<typename T> //删除合法节点p，返回其数值
T List<T>::remove(ListNodePosi(T) p){
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p; _size--;
	return e;
} 

template<typename T> List<T>::~List(){ //列表析构器 
	clear(); delete header; delete trailer; //清空列表，释放头尾哨兵节点 
} 

template<typename T> int List<T>::clear(){ //反复删除首节点，直至列表变空 
	int oldSize = _size;
	while(0 < _size) remove(header->succ); //反复删除首节点，直至列表变空
	return oldSize; 
} 

template<typename T> int List<T>::duplicate(){ //剔除无序列表中的重复节点 
	if(_size < 2) return 0; //平凡列表自然无重复 
	int oldSize = _size; //记录原规模 
	ListNodePosi(T) p = header; Rank r = 0; //p从首节点开始 
	while(trailer != (p = p->succ)){ //依次直到末节点 
		ListNodePosi(T) q = find(p->data, r, p); //在p的r个（真）前驱中查找雷同者 
		q ? remove(q) : r++;  //若存在，则删除之；否则秩加1 
	} //在任意时刻，p的前驱互不相同 
	return oldSize-_size();
}

//列表遍历
template<typename T> template<typename VST> //元素类型，操作器
void List<T>::traverse(VST& visit) { //借助函数对象遍历机制遍历
	for(ListNodePosi(T) p = header->succ; p!=trailer; p=p->succ) visit(p->data);
} 

//有序列表的排重 
template<typename T> int List<T>::uniquify(){ //成批剔除重复元素，效率更高 
	if(_size < 2) return 0; //平凡列表自然无重复 
	int oldSize = _size;
	ListNodePosi(T) p = first(); ListNodePosi(T) q; //p为各区段起点，q为其后继
	while(trailer != (q=q->succ)){ //反复考察紧邻的节点对（p, q)
		if(p->data != q->data) p = q;
		else remove(q);
	} 
	return oldSize - _size;
}
 
//有序列表的查找 
template<typename T> //在有序列表内节点p(可能是trailer)的n个（真）前驱中，找到不大于e的的最后者
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const{
//assert: 0 <= n <= rank(p) < _size
    while(0 < n--){ //对于p的最近的n个前驱，从右到左逐个比较 
    	if(((p = p->pred)->data) <= e) break; //直至命中，数值越界或者范围越界 
	} 
//assert: 至此位置p必符合输出语义约定——尽管最后一次关键码比较可能没有意义（等效于与-inf作比较） 
	return p; //查找终止位置 
} 

//排序器统一入口
template<typename T> void List<T>::sort(ListNodePosi(T) p, int n){ //列表区间排序 
	switch(rand() % 3){
		case 1: insertionSort(p, n); break; //插入排序 
		case 2: selectionSort(p, n); break; //选择排序 
		default: mergeSort(p, n); break; //归并排序 
	}
} 

//插入排序
template<typename T> //列表的插入排序算法：对起始位置p的n个元素排序
void List<T>::insertionSort(ListNodePosi(T) p, int n){
	for(int r=0; r<n; r++){
		insertA(search(p->data, r, p), p->data); //查找适当位置并插入
		p = p->succ; remove(p->pred); //转向下一节点 
	}
} 

//选择排序
template<typename T> //列表的选择排序算法：对起始于位置p的n个元素排序
void List<T>::selectionSort(ListNodePosi(T) p, int n){ //valid(p) && rank(p)+n<=size 
	ListNodePosi(T) head = p->pred; ListNodePosi(T) tail=p;
	for(int i=0; i<n; i++) tail = tail->succ; //待排序区间为(head, tail)
	while(1<n){ // 至少还剩两个节点之前，在待排序区间内 
		ListNodePosi(T) max = selectMax(head->succ, n); //找出最大者
		insertB(tail, remove(max)); //将其移动到无序区间末尾
		tail = tail->pred; n--; 
	} 
} 

//找出最大者
template<typename T> //从起始位置p的n个后继中选出最大者
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n){
	ListNodePosi(T) max = p; //最大者暂定为首节点p
	for(ListNodePosi(T) cur = p; 1 < n; n--){
		if(!lt((cur=cur->succ)->data, max->data)) //若当前元素不小于max
		    max = cur; 
	} 
	return max;
} 

//归并
template<typename T> //有序列表的归并：当前列表中自p起的n个元素，与列表L中自q起的m个元素归并
void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m){
	ListNodePosi(T) pp = p->pred; //借助前驱（可能是header)，以便返回前...
	while(0<m){
		if((0<n)&&(p->data <= q->data)) //若p仍在区间内且v(p) <= v(q), 则
		{if(q==(p=p->succ)) break; n--;}
		else //若已超出右界或v(q) < v(p)，则
		{insertB(p, L.remove((q=q->succ)->pred)); m++;} //将q转移至p之前 
	} 
	p = pp->succ; //确定归并后区间（新）起点 
} 

//归并排序
template<typename T> //列表的归并排序算法：对于始于位置p的n个元素排序
void List<T>::mergeSort(ListNodePosi(T)& p, int n){ //valid(p) && rank(p) + n <= size 
	if(n<2) return;
	int m = n>>1; //以中点为界
	ListNodePosi(T) q = p;
	for(int i=0; i<m; i++) q = q->succ; //均分列表
	mergeSort(p, m);
	mergeSort(q, n-m); // 对前、后子列表分别排序
	merge(p, m, *this, q, n-m); //归并                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
} //注意：排序后，p依然指向归并后区间的（新）起点 

