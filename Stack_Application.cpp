#define _int64 long long
#include "Stack.h"
#include<cctype>

//进制转换算法（递归版） 
void convert_recursive(Stack<char>& S, _int64 n, int base){ //十进制正整数n到base进制的转换（递归版）
    static char digit[] //n < n, 1 < base <= 16，新进制下的数位符号，可视base取值范围适当扩充
	= {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	if(0<n){ //在尚有余数之前，反复地 
	    S.push(digit[n % base]); //逆向记录当前最低位
        convert_recursive(S, n/base, base); //通过递归得到所有高位 
	} 
} //新进制下由高位到低位的各数位，由顶向下保存于栈S中

//进制转换算法（迭代版）
void convert_iteration(Stack<char>& S, _int64 n, int base){ //十进制正整数n到base进制的转换（迭代版）
	static char digit[] //n < n, 1 < base <= 16，新进制下的数位符号，可视base取值范围适当扩充
	= {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	while(n>0){ //由低到高，逐一计算出新进制下的各数位 
		int remainder = (int)(n%base); S.push(digit[remainder]); //余数（当前位）入栈
		n/=base; //n更新为其对base的除商 
	} 
} //新进制下由高位到低位的各数位，由顶向下保存于栈S中

//括号匹配算法
void trim(const char exp[], int& lo, int& hi){ //删除exp[lo, hi]不包含括号的最长前缀、后缀 
	while((lo <= hi) && (exp[lo] != '(') && (exp[lo] != ')')) lo++; //查找第一个和 
	while((lo <= hi) && (exp[hi] != '(') && (exp[hi] != ')')) hi--; //最后一个括号 
} 

int divide(const char exp[], int lo, int hi){ //切分exp[lo, hi]，使exp匹配仅当子表达式匹配 
	int mi = lo; int crc = 1; //crc未[lo, mi]范围左右括号数目之差
	while((0<crc) && (++mi<hi)){
		if(exp[mi]==')') crc--; if(exp[mi]=='(') crc++; //左右括号分别计数 
	} 
	return mi;
} //若mi<=hi，则为合法切分点；否则，意味着局部不可能匹配 

bool paren(const char exp[], int lo, int hi){ //检查表达式exp[lo, hi]是否括号匹配（递归版） 
	trim(exp, lo, hi); if(lo > hi) return true; //清除不包含括号的前缀、后缀 
	if(exp[lo] != '(') return false; //首字符非左括号，则不匹配 
	if(exp[hi] != ')') return false; //末字符非右括号，则不匹配
	int mi = divide(exp, lo, hi); //确定适当的切分点 
	if(mi>hi) return false; //切分点不合法，意味着局部以至整体不匹配
	return paren(exp, lo+1, hi-1) && paren(exp, mi+1, hi); //分别检查左右表达式 
}

//括号匹配算法（迭代版）
bool paren_iteration(const char exp[],int lo, int hi){ //表达式括号匹配检查，可兼顾三种括号 
	Stack<char> S; //使用栈记录已发现但尚未匹配的左括号
	for(int i=lo; i<hi; i++){
		switch(exp[i]){ //左括号直接进栈；右括号若与栈顶失配，则表达式不匹配 
			case '(': case '[': case '{': S.push(exp[i]); break;
			case ')': if((S.empty()) || ('(' != S.pop())) return false; break;
			case ']': if((S.empty()) || ('[' != S.pop())) return false; break;
			case '}': if((S.empty()) || ('{' != S.pop())) return false; break;
			default: break; //非括号字符一律忽略 
		}
	} 
	return S.empty(); //整个表达式扫描过后，栈中若仍残留（左）括号，则不匹配；否则（栈空）匹配 
} 

//运算符优先级关系定义 
#define N_OPTR 9
typedef enum{ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE} Operator; //运算符集合(+ - * / ^ ! ( ) \0 )
//加，减，乘，除，乘，阶乘，左括号，右括号，起始符与终止符 
const char pri[N_OPTR][N_OPTR] = { //运算符优先等级[栈顶][当前] 
/*              |--------------------当前运算符-------------------|    */
/*              +    -    *    /    ^    !    (    )    \0             */
/* --  + */    '>', '>', '<', '<', '<', '<', '<', '>', '>', 
/*  |  - */    '>', '>', '<', '<', '<', '<', '<', '>', '>',
/* 栈  * */    '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* 顶  / */    '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* 运  ^ */    '>', '>', '>', '>', '>', '<', '<', '>', '>',
/* 算  ! */    '>', '>', '>', '>', '>', '>', ' ', '>', '>',
/* 符  ( */    '<', '<', '<', '<', '<', '<', '<', '=', ' ',
/*  |  ) */    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
/* -- \0 */    '<', '<', '<', '<', '<', '<', '<', ' ', '='
};

//表达式的求值及RPN转换
float evaluate(char* S, char*& RPN){ //对（已剔除空白格的）表达式S求值，并转换为逆波兰式RPN 
	Stack<float> opnd; Stack<char> optr; //运算数栈，运算符栈
	optr.push('\0'); //尾哨兵'\0'也作为头哨兵首先入栈
	while(!optr.empty()){ //在运算符非空之前，逐个处理表达式中各字符 
		if(isdigit(*S)){  //若当前字符为操作数，则
			readNumber(S, opnd); append(RPN, opnd.top()); //读入操作，并将其接至RPN末尾 
		} 
		else{ //若当前字符为运算符，则 
			switch(orderBetween(optr.top(), *S)){ //视其与栈顶运算符之间优先级高低分别处理 
				case '<': //栈顶运算符优先级更低时
				    optr.push(*S); S++; //计算推迟，当前运算符进栈
					break;
				case '=': //优先级相等（当前运算符为右括号或者尾部哨兵'\0'时）
				    optr.pop(); S++; //脱括号并进行下一个字符
					break;
				case '>':{ //栈顶运算符优先级更高时，可实施相应计算，并将结果重新入栈
				    char op = optr.pop(); append(RPN, op); //栈顶运算符出栈并接至RPN末尾
					if('!'==op){ //若属于一元运算符 
						float pOpnd = opnd.pop(); //只需取出一个操作数，并
						opnd.push(calcu(op, pOpnd)); //实施二元计算，结果入栈 
					}else{ //对于其它（二元）运算符 
						float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop(); //取出后/前操作数
						opnd.push(calcu(pOpnd1, op, pOpnd2)); //实施二元计算，结果入栈 
					}
					break;
				} 
				default: exit(-1); //逢语法错误，不做处理直接退出 
			}//switch
		}//while 
	} 
	return opnd.pop(); //弹出并返回最后计算结果 
} 

//数字解析 
void readNumber(char* S, stack<float>& opnd){ //从一个数字字符开始解析出一个完整的数字（比如'2.33'，从字符'2'开始解析出2.33) 
    float num = 0; //解析出来的数值
    int c = 0; //记录位数(整数，小数）
    bool bDecimal = false; //小数指示器 
	while(*S){ //数字的ASCII码介于47-58之间，'.'的ASCII码为46
		if(int(*S) == 46){ //遇到小数点，则 
			bDecimal = true; //更新小数指示器
			c = 1; //小数位数
			S++; //逐字符 
		}
		else if(isdigit(*S)){ //非小数点 
			if(!bDecimal){ //处理整数部分 
	    	    num = num * pow(10, c) + (int(*S)-int('0'));
		        c++;
		    }
			else{ //处理小数部分  
				num = num + pow(10, -c) * (int(*S)-int('0'));
		    	c++;
			}
			S++; //逐字符 
		}
		else break;
	}
	opnd.push(num);
}


//皇后共存问题
struct Queen{ //皇后类 
	int x, y; //皇后在棋盘上的位置坐标
	Queen(int xx=0, int yy=0): x(xx), y(yy){}; //构造函数
	bool operator== (Queen const& q) const{ //重载判等操作符，以检测不同皇后之间可能的冲突
	    return(x==q.x) //行冲突（这一情况其实并不会发生，可省略
		||(y == q.y) //列冲突
		||(x + y == q.x + q.y) //沿正对角线冲突
		||(x - y == q.x - q.y); //沿副对角线冲突 
	} 
	bool operator!=(Queen const& q){return !(*this == q);} //重载不等操作符 
};

void placeQueens(int N){ //N皇后算法（迭代版）：采用试探/回溯的策略，借助栈记录查找结果 
	Stack<Queen> solu; //存放（部分）解的栈
	Queen q(0, 0); //从原点出发 
	do{ //反复试探，回溯 
		if(N <= solu.size() || N <= q.y){ //若已出界，则 
			q = solu.pop(); q.y++; //回溯一行，并继续试探下一列 
		}else{ //否则，试探下一行 
			while((q.y < N) && (0 <= solu.find(q))) //通过与已有皇后的对比
			{q.y++; nCheck++;} //尝试找到可摆放下一皇后的列
			if(N > q.y){ //若存在可拜访的列，则 
				solu.push(q); //摆上当前皇后，并
				if(N <= solu.size()) nSolu++; //若部分解已成为全局解，则通过全局变量nSolu计数
				q.x++; q.y = 0; //转入下一行，从第0列开始，试探下一皇后 
			} 
		}
	}while((0 < q.x) || (q.y < N)); //所有分支均已或穷举或剪枝之后，算法结束 
}


//迷宫寻址
typedef enum{AVAILABLE, ROUTE, BACKTRACKED, WALL} Status; //迷宫单元状态 
//原始可用的，在当前路径上的，所有方向均尝试失败后回溯过的，不可使用的（墙）

typedef enum{UNKNOWN, EAST, SOUTH, WEST, NORTH, NO_WAY} ESWN; //单元的相对邻接方向
//未定、东、南、西、北、无路可通

inline ESWN nextESWN(ESWN eswn){return ESWN(eswn + 1);} //依次转至下一邻接方向

struct Cell{ //迷宫格点 
	int x, y; Status status; //x坐标，y坐标，类型
	ESWN incoming, outgoing; //进入、走出方向 
}; 

#define LABY_MAX 24; //最大迷宫尺寸 
Cell laby[LABY_MAX][LABY_MAX]; //迷宫 

//邻格查询
inline Cell* neighbor(Cell* cell){ //查询当前位置的相邻格点 
	switch(cell->outgoing){
		case EAST: return cell + LABY_MAX; //向东
		case SOUTH: return cell + 1; //向南
		case WEST: return cell - LABY_MAX; //向西
		case NORTH: return cell - 1; //向北 
		default: exit(-1);
	}
} 

//格点转入
inline Cell* advance(Cell* cell){
	Cell* next;
	switch(cell->outgoing){
		case EAST:  next = cell + LABY_MAX;  next->incoming = WEST; break; //向东
		case SOUTH: next = cell + 1;         next->incoming = NORTH; break; //向南
		case WEST:  next = cell - LABY_MAX;  next->incoming = EAST; break; //向西
		case NORTH: next = cell - 1;         next->incoming = SOUTH; break; //向北
		default: exit(-1); 
	}
	return next;
} 

//迷宫寻径算法：在格单元s至t之间规划一条通路（如果的确存在）
bool labyrith(Cell Laby[LABY_MAX][LABY_MAX], Cell* s, Cell* t){
	if((AVAILABLE != s->status) || (AVAILABLE != t->status)) return false; //退化情况
	Stack<Cell*> path; //用栈记录通路（Theseus的线绳）
	s->incoming = UNKNOWN; s->status = ROUTE; path.push(s); //起点
	do{ //从起点出发不断试探、回溯，直到抵达终点，或者穷尽所有可能 
		Cell* c = path.top(); //检查当前位置（栈顶）
		if(c==t) return true; //若已抵达终点，则找到一条通路；否则，沿尚未探测的方向继续试探
		while(NO_WAY > (c->outgoing = nextESWN(c->outgoing))) //逐一检查所有方向
		    if(AVAILABLE == neighbor(c)->status) break; //试图找到尚未探测的方向
		if(NO_WAY <= c->outgoing) //若所有方向都已尝试过
		{c->status = BACKTRACKED; c = path.pop();} //则向后回溯一步
		else //否则，向前试探一步
		{path.push(c=advance(c)); c->outgoing = UNKNOWN; c->status = ROUTE;} 
	}while(!path.empty());
	return false;
} 

 

