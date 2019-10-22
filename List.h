#include <stddef.h>
#include <stdlib.h>
#define ListNodePosi(T) ListNode<T>*
typedef int Rank;
using namespace std;

template<typename T> struct ListNode{
	//��Ա 
	T data; ListNodePosi(T) pred; ListNodePosi(T) succ;
	//������ 
	ListNode(){}
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
	:data(e), pred(p), succ(s) {}
	//�����ӿ�
	ListNodePosi(T) insertAsPred(T const& e); //������ǰ�ڵ�֮ǰ�����½ڵ� 
	ListNodePosi(T) insertAsSucc(T const& e); //������ǰ�ڵ�֮������½ڵ� 
};

template<typename T> class List{
	private:
		int _size; ListNodePosi(T) header; ListNodePosi(T) trailer; //��ģ��ͷ�ڱ���β�ڱ�
		
	protected:
        void init(); //�б���ʱ�ĳ�ʼ�� 
        int clear(); //������нڵ�
		void copyNodes(ListNodePosi(T), int); //�����б�����λ��p���n��
		void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int); //�鲢
		void mergeSort(ListNodePosi(T)&, int); //��p��ʼ������n���ڵ�鲢����
		void selectionSort(ListNodePosi(T), int);  //��p��ʼ������n���ڵ�ѡ������
		void insertionSort(ListNodePosi(T), int); //��p��ʼ������n���ڵ��������
	
	public:
        List() {init();} //Ĭ��
	    List(List<T> const& L); //���帴���б�L
	    List(List<T> const& L, Rank r, int n); //�����б�L���ӵ�r�����n��
	    List(ListNodePosi(T) p, int n); //�����б�����λ��p���n��
	    //��������
		~List(); //�ͷţ�����ͷ��β�ڱ��������нڵ�
		//ֻ�����ʽӿ�
		Rank size() const {return _size;} //��ģ
		bool empty() const {return _size <= 0;} //�п�
		T& operator[] (Rank r) const; //���أ�֧��Ѱ�ȷ��ʣ�Ч�ʵͣ�
		ListNodePosi(T) first() const {return header->succ;} //�׽ڵ�λ�� 
		ListNodePosi(T) last() const {return trailer->pred;} //β�ڵ�λ��
		bool valid(ListNodePosi(T) p) //�ж�p�Ƿ����Ϸ�
		{return p && (trailer != p) && (header != p);} //��ͷβ�ڵ��ͬ��NULL
		int disordered() const; //�ж��б��Ƿ��Ѿ�����
		ListNodePosi(T) find(T const& e) const //�����б���� 
		{return find(e, _size, trailer);}  
		ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const; //�����������
		ListNodePosi(T) search(T const& e) const // �����б����
		{return search(e, _size, trailer);}
		ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const; //�����������
		ListNodePosi(T) selectMax(ListNodePosi(T) p, int n); //��p����n-1�������ѡ�������
		ListNodePosi(T) selectMax() {return selecMax(header->succ, _size);} //���������
		//��д���ʽӿ�
		ListNodePosi(T) insertAsFirst(T const& e); //��e�����׽ڵ����
		ListNodePosi(T) insertAsLast(T const& e); //��e����ĩ�ڵ����
 		ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e); //��e����p�ĺ�̲���
 		ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e); //��e����p��ǰ������
	  	T remove(ListNodePosi(T) p); //ɾ���Ϸ�λ��p���Ľڵ㣬���ر�ɾ���ڵ�
	  	void merge(List<T>& L){merge(first(), size, L, L.first(), L._size);} //ȫ�б�鲢 
		void sort(ListNodePosi(T) p, int n); //�б���������
		void sort(){sort(first(), _size);} //�б��������� 
	 	int duplicate(); //����ȥ�� 
		int uniquify(); //����ȥ�� 
  		void reverse(); //ǰ����
		//����
		void traverse(void(*)(T&)); //����������ʵʩvisit����������ָ�룬ֻ����ֲ����޸ģ�
		template<typename VST> //������
		void traverse(VST&); //����������ʵʩvisit�������������󣬿ɾֲ����޸ģ� 
};
