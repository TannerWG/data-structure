#include"List.h" //��ListΪģ���� 
template <typename T> class Queue: public List<T>{ //����ģ����i���̳�Listԭ�нӿڣ� 
	void enqueue(T const& e){insertAsLast(e);} //��ӣ�β������
	T dequeue(){return remove(first());} //����:�ײ�ɾ��
	T& front(){return first()->data;} //���� 
}; 
