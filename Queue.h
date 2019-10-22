#include"List.h" //以List为模板类 
template <typename T> class Queue: public List<T>{ //队列模板类i（继承List原有接口） 
	void enqueue(T const& e){insertAsLast(e);} //入队：尾部插入
	T dequeue(){return remove(first());} //出队:首部删除
	T& front(){return first()->data;} //队首 
}; 
