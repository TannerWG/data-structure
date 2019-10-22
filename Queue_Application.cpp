#include "Queue.h"

//���з���ģ��
//�˿Ͷ��� 
struct Customer{int window; unsigned int time;}; //�˿��ࣺ�������ڣ����У�������ʱ��

//���з���ģ��
void simulate(int nWin, int servTime){ //��ָ����������������ʱ��ģ������ҵ�� 
	Queue<Customer>* windows = new Queue<Customer>[nWin]; //Ϊÿ�����ڴ���һ������ 
	for(int now = 0; now < servTime; now++){ //���°�֮ǰ��ÿ��һ��ʱ�䵥λ 
		if(rand() % (1 + nWin)){ //�¹˿���nWin/(nWin+1)�ĸ��ʵ��� 
			Customer c; c.time = 1 + rand() % 98; //�¹˿͵������ʱ�����ȷ��
			c.window = bestWindow(windows, nWin); //�ҳ���ѣ���̣��ķ��񴰿�
			windows[c.window].enqueue(c); //�¹˿ͼ����Ӧ���� 
		}
		for(int i = 0; i < nWin; i++){ //�ֱ��� 
			if(!Windows[i].empty()){ //���ǿն��� 
				if(--windows[i].front().time <= 0){ //���׹˿͵ķ���ʱ������һ����λ 
					windows[i].dequeue(); //������Ϲ˿ͳ��У��ɺ����˿ͽӴ� 
				}
			} 
		}
	} //for
	delete[] windows; //�ͷ����ж��У���ǰ��~List()���Զ���ն��У� 
} 

//������̶���
int bestWindow(Queue<Customer> windows[], int nWin){ //Ϊ�µ��˿�ȷ����Ѷ��� 
	int minSize = windows[0].size(); optiWin = 0; //���Ŷ��У����ڣ�
	for(int i = 1; i < nWin; i++){
		if(minSize > windows[i].size()) //��ѡ�� 
		{minSize = windows[i].size(); optiWin = i;} //��������� 
	} 
	return optiWin; //���� 
} 
