#include "Queue.h"

//银行服务模拟
//顾客对象 
struct Customer{int window; unsigned int time;}; //顾客类：所属窗口（队列）、服务时长

//银行服务模拟
void simulate(int nWin, int servTime){ //按指定窗口数、服务总时间模拟银行业务 
	Queue<Customer>* windows = new Queue<Customer>[nWin]; //为每个窗口创建一个队列 
	for(int now = 0; now < servTime; now++){ //在下班之前，每隔一个时间单位 
		if(rand() % (1 + nWin)){ //新顾客以nWin/(nWin+1)的概率到达 
			Customer c; c.time = 1 + rand() % 98; //新顾客到达，服务时长随机确定
			c.window = bestWindow(windows, nWin); //找出最佳（最短）的服务窗口
			windows[c.window].enqueue(c); //新顾客加入对应队列 
		}
		for(int i = 0; i < nWin; i++){ //分别检查 
			if(!Windows[i].empty()){ //各非空队列 
				if(--windows[i].front().time <= 0){ //队首顾客的服务时长减少一个单位 
					windows[i].dequeue(); //服务完毕顾客出列，由后续顾客接待 
				}
			} 
		}
	} //for
	delete[] windows; //释放所有队列（此前，~List()会自动清空队列） 
} 

//查找最短队列
int bestWindow(Queue<Customer> windows[], int nWin){ //为新到顾客确定最佳队列 
	int minSize = windows[0].size(); optiWin = 0; //最优队列（窗口）
	for(int i = 1; i < nWin; i++){
		if(minSize > windows[i].size()) //挑选出 
		{minSize = windows[i].size(); optiWin = i;} //队列最短者 
	} 
	return optiWin; //返回 
} 
