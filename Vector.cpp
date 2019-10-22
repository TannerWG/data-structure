#include"Vector.h"
#include<stdlib.h>
//#include "..\fibonacci\Fib.h"
typedef int Rank;

//���ڸ��Ƶ����������� 
template<typename T> //Ԫ������
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi){ //����������A[lo, hi)Ϊ������������
    _elem = new T[_capacity=2*(hi-lo)]; _size = 0; //����ռ䣬��ģ����
	 while(lo<hi){ //A[lo, hi)��Ԫ����һ 
	 	_elem[_size++] = A[lo++]; //������_elem[0, hi-lo) 
	 } 
} 

//�������������� 
template <typename T> Vector<T>& Vector<T>::operator=(Vector<T> const& V){
	if(_elem) delete[] _elem; //�ͷ�ԭ������
	copyFrom(V._elem, 0, V.size()); //���帴��
	return *this; //���ص�ǰ��������ã��Ա���ʽ���� 
}

//�����ڲ����鶯̬�����㷨
template<typename T> void Vector<T>::expand(){ //�����ռ䲻��ʱ���� 
	if(_size<_capacity) return;
	if(_capacity<DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY; //��������С����
	T* oldElem = _elem; _elem = new T[_capacity <<= 1]; //�����ӱ�
	for(int i=0; i<_size; i++){
		_elem[i] = oldElem[i]; //����ԭ�������ݣ�TΪ�������ͣ��������ظ��Ʋ�����'='�� 
	} 
	delete[] oldElem; //�ͷ�ԭ�ռ� 
} 

//��������
template<typename T> void Vector<T>::shrink(){ //װ�����ӹ�Сʱѹ��������ռ�ռ� 
	if(_capacity<DEFAULT_CAPACITY<<1) return; //������������DEFAULT_CAPACITY���� 
	if(_size<<2 > _capacity) return; //��25%Ϊ��
	T* oldElem = _elem; _elem = new T[_capacity>>=1]; //��������
	for(int i=0; i<_size; i++) _elem[i] = oldElem[i]; //����ԭ��������
	delete[] oldElem; //�ͷſռ� 
} 

//�������������㷨
template<typename T> void permute(Vector<T>& V){
	for(int i=V.size(); i>0; i--){
		swap(V[i-1], V[rand()%i]); //V[i-1]��V[0,i)��ĳһ���Ԫ�ؽ��� 
	}
} 

//����������
template<typename T> void Vector<T>::unsort(Rank lo, Rank hi){ //�ȸ��������������[lo, hi) 
	T* V = _elem + lo; //��������_elem[lo, hi)������һ����V[0, hi-lo) 
	for(Rank i=hi-lo; i>0; i--){ //�Ժ���ǰ 
		swap(V[i-1], V[rand()%i]); //��V[i-1]��V[0, i)��ĳһԪ��������� 
	}
} 

//�е�����Ƚ���
template<typename T> static bool lt(T* a, T& b) {return lt(*a, *b);} //less than
template<typename T> static bool lt(T& a, T& b) {return a < b;} //less than
template<typename T> static bool eq(T* a, T* b) {return eq(*a, *b);} //equal
template<typename T> static bool eq(T& a, T& b) {return a==b;} //equal

//��������Ԫ�ز���
template<typename T> //����������˳����ң��������һ��Ԫ��e��λ�ã�ʧ��ʱ������lo-1 
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const { //assert: 0<=lo<hi<=_size;
    while((lo<hi--) && (e!=_elem[hi])); //�Ӻ���ǰ��˳�����
	return hi; //��hi<lo=������ζ��ʧ�ܣ�����hi������Ԫ�ص��� 
}

//����
template<typename T> //��e��Ϊ��ΪrԪ�ز���
Rank Vector<T>::insert(Rank r, T const& e){
	expand(); //���б�Ҫ������
	for(int i=_size; i>r; i--) _elem[i] = _elem[i-1]; //�Ժ���ǰ�����Ԫ�����κ���һ����Ԫ
	_elem[r] = e; _size++; //������Ԫ�ز���������
	return r; //������ 
} 

//����ɾ����remove(lo, hi)
template<typename T> int Vector<T>::remove(Rank lo, Rank hi){ //ɾ������[lo, hi) 
	if(lo == hi) return 0; //����Ч�ʿ��ǣ����������˻����������remove(0,0)
	while(hi<_size) _elem[lo++] = _elem[hi++]; //[hi,_size)˳���ƶ�hi-lo����Ԫ
	_size = lo; //���¹�ģ��ֱ�Ӷ���β��[lo,_size)����
	shrink(); //���б�Ҫ������
	return hi-lo; //���ر�ɾ��Ԫ�ص���Ŀ 
} 


//������Ԫɾ���ӿ�
template<typename T> T Vector<T>::remove(Rank r){ //ɾ����������Ϊr��Ԫ��,0<=r<size
    T e = _elem[r]; //���ݱ�ɾ��Ԫ��
	remove(r, r+1); //��������ɾ���㷨����Ч�ڶ�����[�ˣ� r+1����ɾ��
	return e; //���ر�ɾ��Ԫ�� 
} 

//������������ظ�Ԫ�� 
template<typename T> int Vector<T>::deduplicate(){ //ɾ�������������ظ�Ԫ�أ��߼��棩 
	int oldSize = _size; //��¼ԭʼ��ģ
	Rank i = 1;
	while(i<_size){
		(find(_elem[i], 0, i)<0) ? //����ǰ׺��Ѱ��������ͬ�ߣ�����һ���� 
		i++ : remove(i); //������ͬ������������̣�����ɾ����ͬ�� 
	} 
	return oldSize - _size; //������ģ�仯��������ɾ��Ԫ������ 
}

//��������
template<typename T> void Vector<T>::traverse(void(*visit)(T&)) //��������ָ�����
{for(int i=0; i<_size; i++) visit(_elem[i]);} //��������

template<typename T> template<typename VST> //Ԫ�����͡�������
void Vector<T>::traverse(VST& visit) //���������������
{for(int i=0; i<_size; i++) visit(_elem[i]);} //��������

//������������㷨
template<typename T> int Vector<T>::disordered() const { //������������������Ԫ�ضԵ�����
    int n = 0; //������
	for(int i=1; i<_size; i++){
		if(_elem[i-1] > _elem[i]) n++; //��������� 
	} 
	return n; //�����������ҽ���n=0 
} 

//��������uniquify()�ӿڵ�ƽ��ʵ��
template<typename T> int Vector<T>::uniquify_1(){ //���������ظ�Ԫ���޳��㷨����Ч�棩 
	int oldSize = _size; int i=1; //��ǰ�Ա�Ԫ�ص��ȣ���ʼ����Ԫ��
	while(i<_size){ //��ǰ�����һ�Աȸ�������Ԫ�� 
		_elem[i-1] == _elem[i] ? remove(i) : i++; //����ͬ����ɾ�����ߣ�����ת������Ԫ�� 
	} 
	return oldSize-_size; //������ģ�仯��������ɾ��Ԫ������ 
} 

//��������uniquify()�ӿڵĸ�Чʵ��
template<typename T> int Vector<T>::uniquify(){ //�������ظ�Ԫ���޳��㷨����Ч�棩
	Rank i = 0, j = 0; //���Ի��조���ڡ� Ԫ�ص���
	while(++j<_size){ //��һɨ�裬ֱ��ĩԪ�� 
		if(_elem[i] != _elem[j]) //������ͬ��
		    _elem[++i] = _elem[j];  //���ֲ�ͬԪ��ʱ����ǰ����������ǰ���Ҳ�
	} 
	_size = ++i; shrink(); //ֱ�ӽس�β������Ԫ��
	return j - i; //������ģ�仯��������ɾ��Ԫ������
}

//�����������ֲ����㷨��ͳһsearch()�ӿ�
template<typename T> //����������������[lo, hi)�ڣ�ȷ��������e�����һ���ڵ����
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const { //assert: 0<=lo<hi<=_size
    return (rand() % 2) ? //����50%�ĸ���ʹ�ö��ֲ��һ�Fibonacci���� 
	    binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi); 
} 

//���ֲ����㷨���汾A��:����������������[lo, hi)�ڲ���Ԫ��e��0<=lo<=hi<=_size
template<typename T> static Rank binSearch_1(T* A, T const& e, Rank lo, Rank hi){
	while(lo < hi){ //ÿһ����������Ҫ�����αȽ��жϣ���������֧
	    Rank mi = (lo + hi) >> 1; //���е�Ϊ���
		if(e<A[mi]) hi = mi; //����ǰ���[lo, mi)��������
		else if(A[mi]<e) lo = mi + 1; //�������(mi, hi)��������
		else return mi; //��mi������ 
	} //�ɹ����ҿ�����ǰ��ֹ
	return -1; 
} //�ж������Ԫ��ʱ�����ܱ�֤����������ߣ�����ʧ��ʱ���򵥷���-1��������ָʾ��ʧ�ܵ�λ��

/*
//Fibonacci�����㷨
template<typename T> static Rank fibSearch(T* A, T const& e, Rank lo, Rank hi){
	Fib fib(hi-lo); //��O(log_phi(n = hi - lo))ʱ�䴴��Fib����
	while(lo < hi){
		while(hi-lo<fib.get()) fib.prev(); //ͨ����ǰ˳����ң���̯O(1) 
		Rank mi = lo + fib.get()-1; //ȷ������Fib(k)-1�����
		if(e<A[mi]) hi = mi; //����ǰ���[lo,mi)��������
		else if(A[mi]<e) lo = mi+1; //�������(mi,hi)�������� 
		else return mi; //��mi������ 
	} //�ɹ����ҿ�����ǰ��ֹ
	return -1; //����ʧ�� 
} //�ж������Ԫ��ʱ�����ܱ�֤����������ߣ�ʧ��ʱ���򵥷���-1��������ָʾʧ�ܵ�λ�� 
*/

//���ֲ����㷨���汾B��������������������[lo,hi)�ڲ���Ԫ��e,0 <= lo <= hi <= _size 
template<typename T> static Rank binSearch_2(T* A, T const& e, Rank lo, Rank hi){
	while(1<hi-lo){ //ÿ������������һ�αȽ��жϣ���������֧���ɹ����Ҳ�����ǰ��ֹ
	    Rank mi = (lo+hi)>>1; //���е�Ϊ���
		(e<A[mi]) ? hi = mi : lo = mi; //�����ȽϺ�����[lo,mi)��[mi,hi) 
	}//����ʱhi=lo+1,�������������һ��Ԫ��A[lo]
	return (e==A[lo]) ? lo : -1; //���ҳɹ�ʱ���ض�Ӧ���ȣ�����ͳһ����-1 
} //�ж������Ԫ��ʱ�����ܱ�֤����������ߣ�ʧ��ʱ���򵥷���-1��������ָʾʧ�ܵ�λ�� 

//���ֲ����㷨���汾C)������������������[lo,hi)�ڲ���Ԫ��e, 0 <= lo <= hi <= _size
template<typename T> static Rank binSearch(T* A, T const& e, Rank lo, Rank hi){
	while(lo < hi){ //ÿ������������һ�αȽ��жϣ���������֧ 
		Rank mi = (lo+hi) >> 1; //���е�Ϊ���
		(e<A[mi]) ? hi = mi : lo = mi + 1; //�����ȽϺ�ȷ������[lo, mi)��(mi, hi) 
	} //�ɹ����Ҳ�����ǰ��ֹ
	return --lo; //ѭ������ʱ��loΪ����e��Ԫ�ص���С�ȣ���lo-1��������e��Ԫ�ص������ 
} //�ж������Ԫ��ʱ�����ܱ�֤����������ߣ�����ʧ��ʱ���ܹ�ָʾʧ�ܵ�λ��

//�����������ӿ�
template<typename T> void Vector<T>::sort(Rank lo, Rank hi){ //��������[lo, hi)���� 
	switch(rand()%5){ //���ѡȡ�����㷨���ɸ��ݾ���������ص����ѡȡ������ 
		case 1: bubbleSort(lo, hi); break; //��������
		case 2: selectionSort(lo, hi); break; //ѡ������
		case 3: mergeSort(lo, hi); break; //�鲢����
		case 4: heapSort(lo, hi); break; //������
		default: quickSort(lo, hi); break; //�������� 
	}
} 

//��������
template<typename T> //��������������
void Vector<T>::bubbleSort(Rank lo, Rank hi) //assert��0 <= lo < hi <= _size
{while(!bubble(lo, hi--));} //������ɨ�轻����ֱ��ȫ��

//����ɨ�轻��
template<typename T> bool Vector<T>::bubble(Rank lo, Rank hi){ //һ��ɨ�轻��
    bool sorted = true; //���������־
	while(++lo < hi){ //�������ң���һ����������Ԫ�� 
		if(_elem[lo-1] > _elem[lo]){ //�������� 
			sorted = false; //��ζ����δ�������򣬲���Ҫ 
			swap(_elem[lo-1], _elem[lo]); //ͨ������ʹ�ֲ����� 
		}
	}
	return sorted; //���������־ 
} 

//�����Ĺ鲢����
template<typename T> //�����鲢����
void Vector<T>::mergeSort(Rank lo, Rank hi){ //0 <= lo < hi <= size 
	if(hi-lo<2) return; //��Ԫ��������Ȼ���򣬷���
	int mi = (lo + hi) / 2; //���е�Ϊ��
	mergeSort(lo, mi); mergeSort(mi, hi); //�ֱ����� 
	merge(lo, mi, hi); //�鲢 
} 

//���������Ķ�·�鲢�㷨
template<typename T> //���������Ĺ鲢
void Vector<T>::merge(Rank lo, Rank mi, Rank hi){ //���������������[lo, hi)��[mi, hi) 
	T* A = _elem + lo; //�ϲ��������A[0, hi-lo) = _elem[lo, hi) 
	int lb = mi - lo; T* B = new T[lb]; //ǰ������B[0, lb) = _elem[lo, mi) 
	for(Rank i=0; i<lb; B[i]=A[i++]); //����ǰ������
	int lc = hi - mi; T* C = _elem + mi; //��������C[0, lc) = _elem[mi, hi)
	for(Rank i=0, j=0, k=0; (j<lb)||(k<lc);){ //B[j]��C[j]�е�С������Aĩβ 
		if((j<lb) && (!(k<lc) || (B[j]<=C[k]))) A[i++] = B[j++]; 
		if((k<lc) && (!(j<lb) || (C[k]<B[j]))) A[i++] = C[k++];
	} 
	delete[] B; //�ͷ���ʱ�ռ� 
} //�鲢��õ���������������[lo,hi) 

//ѡ������
template<typename T> //����ѡ������
void Vector<T>::selectionSort(Rank lo, Rank hi){ //0 <= lo < hi <= size
	for(Rank i=lo; i<hi; i++){ //[lo, i)������õĲ��֣�[i, hi)��δ���򲿷� 
		for(Rank j=i+1; j<hi; j++){ //ɨ��δ���򲿷֣�ѡ����СԪ�ص���ê��Ԫ�ؽ��� 
			if(_elem[j] < _elem[i]) swap(_elem[i], _elem[j]);
		}
	}
} 

//������
template<typename T> //����ѡ������
void Vector<T>::heapSort(Rank lo, Rank hi){ //0 <= lo < hi <= size
    
}



 














